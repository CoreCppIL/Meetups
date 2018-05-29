add_executable(Connection ConnectionClassic.h ConnectionVariant.h ConnectionMain.cpp)

target_include_directories(Connection PRIVATE ${CMAKE_SOURCE_DIR})