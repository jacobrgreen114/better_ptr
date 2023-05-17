/*
 * Copyright (C) 2023 Jacob R. Green
 * All Rights Reserved
 */

#pragma once

#ifndef __cplusplus
#error
#endif

#if __cplusplus >= 202000L
#define BETTER_PTR_CONCEPTS true
#include <concepts>
#else  // __cplusplus >= 202000L
#define BETTER_PTR_CONCEPTS false
#endif

#define BETTER_PTR_NAMESPACE better_ptr
