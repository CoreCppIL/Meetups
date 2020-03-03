cmake_minimum_required (VERSION 3.15)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable (02-vtbl-inheritance "main.cpp")

add_library (02-vtbl-inheritance-lib SHARED "lib.cpp")

target_link_libraries(02-vtbl-inheritance 02-vtbl-inheritance-lib)

