add_executable(JSON JsonMain.cpp JsonStd.h JsonBoost.h JsonStd2.h)

target_link_libraries(JSON Boost::boost)