cmake_minimum_required(VERSION 3.7)
project(boost-asio-demo)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(simple_timer simple_timer/simple_timer.cpp)
target_link_libraries(simple_timer ${CONAN_LIBS})

add_executable(single_thread single_thread/single_thread.cpp)
target_link_libraries(single_thread ${CONAN_LIBS})

add_executable(multiple_threads multiple_threads/multiple_threads.cpp)
target_link_libraries(multiple_threads ${CONAN_LIBS})

add_executable(strand strand/strand.cpp)
target_link_libraries(strand ${CONAN_LIBS})

add_executable(http_get http_get/http_get.cpp)
target_link_libraries(http_get ${CONAN_LIBS})
