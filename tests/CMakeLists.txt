enable_testing()

add_executable(SortingTest SortingTest.cpp)
target_link_libraries(SortingTest gtest_main Algorithms)

add_executable(DynamicArrayTest DynamicArrayTest.cpp)
target_link_libraries(DynamicArrayTest gtest_main DataStructures)

include(GoogleTest)
gtest_discover_tests(SortingTest)
gtest_discover_tests(DynamicArrayTest)