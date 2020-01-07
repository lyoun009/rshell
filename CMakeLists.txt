CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
src/main.cpp
src/command.cpp
src/executor.cpp
src/parser.cpp
src/rShell.cpp
)

ADD_EXECUTABLE(test
src/test.cpp
unit_tests/unit_tests.cpp
src/command.cpp
src/executor.cpp
src/parser.cpp
src/rShell.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
