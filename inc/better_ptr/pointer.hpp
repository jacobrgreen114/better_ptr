/*
 * Copyright (C) 2023 Jacob R. Green
 * All Rights Reserved
 */

// todo : thing

#pragma once

#include <atomic>

#include "common.hpp"

namespace BETTER_PTR_NAMESPACE {

#if BETTER_PTR_CONCEPTS

/**
 * @brief A concept that requires the existence of _ref() and _unref() methods.
 * @tparam T
 */
template <typename T>
concept Pointable = requires(T t) {
  t._ref();
  t._unref();
};

#define POINTABLE_CONCEPT Pointable
#else
#define POINTABLE_CONCEPT typename
#endif

/**
 * @brief A nullable pointer type that automatically calls _ref() and _unref()
 * on the pointed object.
 *
 * @note Pointer does not delete the pointed object. Object deletion must be
 * handled by the object itself.
 *
 * @tparam T
 */
template <POINTABLE_CONCEPT T>
class Pointer final {
  T* _ptr;

 public:
  constexpr Pointer() noexcept : _ptr(nullptr) {}

  constexpr Pointer(T* ptr) noexcept : _ptr(ptr) {
    if (_ptr) {
      _ptr->_ref();
    }
  }

  constexpr Pointer(Pointer&& move) noexcept : _ptr(move._ptr) {
    move._ptr = nullptr;
  }

  constexpr Pointer&
  operator=(Pointer&& move) noexcept {
    if (_ptr) {
      _ptr->_unref();
    }

    _ptr = move._ptr;
    move._ptr = nullptr;

    return *this;
  }

  constexpr Pointer(const Pointer& copy) : _ptr(copy._ptr) {
    if (_ptr) {
      _ptr->_ref();
    }
  }

  constexpr Pointer&
  operator=(const Pointer& copy) {
    if (_ptr) {
      _ptr->_unref();
    }

    _ptr = copy._ptr;
    if (_ptr) {
      _ptr->_ref();
    }

    return *this;
  }

  ~Pointer() {
    if (_ptr) {
      _ptr->_unref();
    }
  }

  constexpr T*
  operator->() const noexcept {
    return _ptr;
  }

  constexpr T&
  operator*() const noexcept {
    return *_ptr;
  }

  constexpr T*
  get() const noexcept {
    return _ptr;
  }

  constexpr operator bool() const noexcept {
    return _ptr != nullptr;
  }

  template <typename... Args>
  static constexpr Pointer
  make(Args&&... args) {
    return Pointer(new T(std::forward<Args>(args)...));
  }
};

/**
 * @brief A base class for objects that can be pointed to by a Pointer.
 */
class BasePointable {
  std::atomic_size_t _ref_count;

 protected:
  constexpr BasePointable() noexcept : _ref_count(1) {}

 public:
  constexpr virtual ~BasePointable() noexcept = default;

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
};

#if BETTER_PTR_CONCEPTS
static_assert(Pointable<BasePointable>);
#endif

}  // namespace BETTER_PTR_NAMESPACE