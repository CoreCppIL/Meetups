cmake_minimum_required (VERSION 3.15)

project (ABI)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/permissive- /W4)
endif ()

add_subdirectory (00-WiderField)
add_subdirectory (01-vtbl)
add_subdirectory (02-vtbl-inheritance)
