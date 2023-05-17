/*
 * Copyright (C) 2023 Jacob R. Green
 * All Rights Reserved
 */

#pragma once

#include "pointer.hpp"

namespace BETTER_PTR_NAMESPACE {

template <typename T>
class Box final : public BasePointable {
  T t;

 public:
  constexpr Box() noexcept : t() {}
  constexpr Box(T&& t) noexcept : t(t) {}
  constexpr Box(const T& t) : t(t) {}

  T&
  value() noexcept {
    return t;
  }

  const T&
  value() const noexcept {
    return t;
  }
};

}  // namespace BETTER_PTR_NAMESPACE