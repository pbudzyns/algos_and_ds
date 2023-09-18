cmake_minimum_required(VERSION 3.25)

# Set the project name and version
project(Algorithms_and_data_structures VERSION 1.0)

# Define C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create compile commands for intelli sense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)

# Download gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/bb9216085fbbf193408653ced9e73c61e7766e80.zip
  SYSTEM
)

FetchContent_MakeAvailable(googletest)

add_executable(App App.cpp)

target_link_libraries(App PUBLIC Algorithms)

target_include_directories(
  App 
  PUBLIC
  "${PROJECT_BINARY_DIR}"
)

enable_testing()

# Simple run test
add_test(NAME RegularUsage COMMAND App)
set_tests_properties(RegularUsage
  PROPERTIES PASS_REGULAR_EXPRESSION "^Hello world!\n$"
  )
