/*
 * Copyright (C) 2023 Jacob R. Green
 * All Rights Reserved
 */

#include <gtest/gtest.h>

#include <atomic>
#include <better_ptr/better_ptr.hpp>

class TestClass {
  static std::atomic_size_t _instance_count;

  std::atomic_size_t _ref_count;

 public:
  static size_t
  instance_count() noexcept {
    return _instance_count.load();
  }

  TestClass() noexcept : _ref_count(0) {
    ++_instance_count;
  }

  ~TestClass() noexcept {
    --_instance_count;
  }

  void
  _ref() noexcept {
    ++_ref_count;
  }

  void
  _unref() noexcept {
    if (--_ref_count == 0) {
      delete this;
    }
  }

  size_t
  ref_count() const noexcept {
    return _ref_count.load();
  }
};

std::atomic_size_t TestClass::_instance_count(0);

static_assert(BETTER_PTR_NAMESPACE::Pointable<TestClass>);

class TestClass2 : public TestClass {};

TEST(PointerTests, DefaultConstructor) {
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>();
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(PointerTests, RawPointerConstructor) {
  auto ptest = new TestClass();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>(ptest);
  EXPECT_EQ(ptr.get(), ptest);
  EXPECT_EQ(ptr->ref_count(), 1);
}

TEST(PointerTests, RawPointerConstructorCast) {
  auto ptest = new TestClass2();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>(ptest);
  EXPECT_EQ(ptr.get(), ptest);
  EXPECT_EQ(ptr->ref_count(), 1);
}

TEST(PointerTests, MoveConstructor) {
  auto ptest = new TestClass();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>(ptest);
  auto ptr2 = std::move(ptr);
  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_EQ(ptr2.get(), ptest);
  EXPECT_EQ(ptr2.get()->ref_count(), 1);
}

TEST(PointerTests, MoveConstructorCast) {
  auto ptest = new TestClass2();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass2>(ptest);
  auto ptr2 = BETTER_PTR_NAMESPACE::Pointer<TestClass>(std::move(ptr));
  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_EQ(ptr2.get(), ptest);
  EXPECT_EQ(ptr2.get()->ref_count(), 1);
}

TEST(PointerTests, MoveAssignment) {
  auto ptest = new TestClass();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>(ptest);
  auto ptr2 = BETTER_PTR_NAMESPACE::Pointer<TestClass>();
  ptr2 = std::move(ptr);
  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_EQ(ptr2.get(), ptest);
  EXPECT_EQ(ptr2.get()->ref_count(), 1);
}

TEST(PointerTests, MoveAssignmentCast) {
  auto ptest = new TestClass2();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass2>(ptest);
  auto ptr2 = BETTER_PTR_NAMESPACE::Pointer<TestClass>();
  ptr2 = std::move(ptr);
  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_EQ(ptr2.get(), ptest);
  EXPECT_EQ(ptr2.get()->ref_count(), 1);
}

TEST(PointerTests, CopyConstructor) {
  auto ptest = new TestClass();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>(ptest);
  auto ptr2 = ptr;
  EXPECT_EQ(ptr.get(), ptest);
  EXPECT_EQ(ptr2.get(), ptest);
  EXPECT_EQ(ptr->ref_count(), 2);
}

TEST(PointerTests, CopyConstructorCast) {
  auto ptest = new TestClass2();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass2>(ptest);
  auto ptr2 = BETTER_PTR_NAMESPACE::Pointer<TestClass>(ptr);
  EXPECT_EQ(ptr.get(), ptest);
  EXPECT_EQ(ptr2.get(), ptest);
  EXPECT_EQ(ptr->ref_count(), 2);
}

TEST(PointerTests, CopyAssignment) {
  auto ptest = new TestClass();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>(ptest);
  auto ptr2 = BETTER_PTR_NAMESPACE::Pointer<TestClass>();
  ptr2 = ptr;
  EXPECT_EQ(ptr.get(), ptest);
  EXPECT_EQ(ptr2.get(), ptest);
  EXPECT_EQ(ptr->ref_count(), 2);
}

TEST(PointerTests, CopyAssignmentCast) {
  auto ptest = new TestClass2();
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass2>(ptest);
  auto ptr2 = BETTER_PTR_NAMESPACE::Pointer<TestClass>();
  ptr2 = ptr;
  EXPECT_EQ(ptr.get(), ptest);
  EXPECT_EQ(ptr2.get(), ptest);
  EXPECT_EQ(ptr->ref_count(), 2);
}

TEST(PointerTests, Destructor) {
  auto ptest = new TestClass();
  {
    auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>(ptest);
    EXPECT_EQ(ptr->ref_count(), 1);
  }
  EXPECT_EQ(TestClass::instance_count(), 0);
}

TEST(PointerTests, Make) {
  EXPECT_EQ(TestClass::instance_count(), 0);
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>::make();
  EXPECT_EQ(TestClass::instance_count(), 1);
  EXPECT_EQ(ptr->ref_count(), 1);
}

TEST(PointerTests, Bool) {
  auto ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>();
  EXPECT_EQ(ptr, false);
  ptr = BETTER_PTR_NAMESPACE::Pointer<TestClass>::make();
  EXPECT_EQ(ptr, true);
}

// todo : implement reference tests