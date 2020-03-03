cmake_minimum_required (VERSION 3.15)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable (01-vtbl "main.cpp")

add_library (01-vtbl-lib SHARED "lib.cpp")

target_link_libraries(01-vtbl 01-vtbl-lib)

