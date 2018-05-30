# Boost ASIO Demos
This directory contains the samples shown in the boost.asio talk.

In order to build these demos, the following tools are required (Windows):
* Visual Studio 2005/8//10/12/13/15
* cmake, version 3.7 or greater
* conan, version 1.3 or greater

To build the project in release configuration, open a Visual Studio developer command line, cd into the project directory and run the following commands (assuming all tools are in path):
```
mkdir build
cd build
conan install ..
cmake ..  -G "Visual Studio 15 2017 Win64"
cmake --build . --config Release
```

The Visual Studio version mentioned in the first cmake invocation must match the one installed on the computer. Consult `cmake --help` for more details.

To build the Debug configuration, use these commands:
```
mkdir build_debug
cd build_debug
conan install .. -s build_type=Debug
cmake ..  -G "Visual Studio 15 2017 Win64"
cmake --build . --config Debug
```

The project was not tested on Linux, but should probably work.
