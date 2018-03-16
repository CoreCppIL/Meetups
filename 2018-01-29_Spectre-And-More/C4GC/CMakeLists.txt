cmake_minimum_required(VERSION 3.0)

project(CppCoreGuidelines)

add_library(CppCoreGuidelines Uninitialized1.cpp Uninitialized2.cpp GlobalInit1.cpp GlobalInit2.cpp MemberInit.cpp ComplexInit.cpp)