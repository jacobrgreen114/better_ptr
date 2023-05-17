/*
 * Copyright (C) 2023 Jacob R. Green
 * All Rights Reserved
 */

#pragma once

#include "pointer.hpp"

namespace BETTER_PTR_NAMESPACE {

template <POINTABLE_CONCEPT T>
class WeakBlock {
  T* _ptr;
  std::atomic_size_t _ref_count;

  constexpr WeakBlock(T* ptr) noexcept : _ptr(ptr), _ref_count(1) {}
};

#if BETTER_PTR_CONCEPTS

template <typename T>
concept Weakable = Pointable<T> and requires(T t) {
  t._weak()->std::template is_same<WeakBlock*>();
};

#define WEAKABLE_CONCEPT Weakable
#else
#define WEAKABLE_CONCEPT typename
#endif

template <WEAKABLE_CONCEPT T>
class Weak final {};

}  // namespace BETTER_PTR_NAMESPACE