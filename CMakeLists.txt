# Copyright (C) 2023 Jacob R. Green
# All Rights Reserved

cmake_minimum_required ( VERSION 3.0 )

project ( "jrg/better_ptr" )

file ( GLOB_RECURSE HEADERS inc/*.hpp )

add_library ( better_ptr INTERFACE ${HEADERS} )
add_library ( jrg::better_ptr ALIAS better_ptr )

target_include_directories ( better_ptr INTERFACE inc/ )

if(MSVC)
    target_compile_options ( better_ptr INTERFACE /Zc:__cplusplus )
endif()

add_subdirectory ( test )