# Copyright (C) 2023 Jacob R. Green
# All Rights Reserved

include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

add_executable ( better_ptr_test
        src/pointer.cpp
)

set_target_properties ( better_ptr_test
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_libraries ( better_ptr_test
    PRIVATE
        GTest::gtest_main
        jrg::better_ptr
)

gtest_discover_tests ( better_ptr_test )