cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(HunterGate)

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.232.tar.gz"
    SHA1 "a412c45fe4c5a72fed386f62dd8d753bd4fd3d11"
)

project(Variants)

set(HUNTER_TLS_VERIFY OFF)

hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

add_subdirectory(Shape)
add_subdirectory(JSON)
add_subdirectory(Connection)

add_executable(Union union.cpp)
add_library(Types types.cpp)
add_library(LVarinat lvariant.cpp)
add_executable(introduction introduction.cpp)

if(MSVC)
  set_source_files_properties(types.cpp PROPERTIES COMPILE_FLAGS /wd4091)
else()
  set_source_files_properties(types.cpp PROPERTIES COMPILE_FLAGS -fpermissive)
endif()