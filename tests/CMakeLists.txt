enable_testing()

add_executable(SortingTest SortingTest.cpp)
target_link_libraries(SortingTest gtest_main Algorithms)

include(GoogleTest)
gtest_discover_tests(SortingTest)