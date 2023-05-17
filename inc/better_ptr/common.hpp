/*
 * Copyright (C) 2023 Jacob R. Green
 * All Rights Reserved
 */

#pragma once

#ifndef __cplusplus
#error "better_ptr requires a C++ compiler"
#endif

#if __cplusplus >= 202000L
#define BETTER_PTR_CONCEPTS true
#include <concepts>
#else  // __cplusplus < 202000L
#define BETTER_PTR_CONCEPTS false
#endif

#ifndef BETTER_PTR_NAMESPACE
#define BETTER_PTR_NAMESPACE better_ptr
#endif