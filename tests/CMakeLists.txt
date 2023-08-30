enable_testing()

add_executable(SortingTest SortingTest.cpp)
target_link_libraries(SortingTest gtest_main Algorithms)

add_executable(DynamicArrayTest DynamicArrayTest.cpp)
target_link_libraries(DynamicArrayTest gtest_main DataStructures)

add_executable(HashMapTest HashMapTest.cpp)
target_link_libraries(HashMapTest gtest_main DataStructures)

add_executable(BinaryTreeTest BinaryTreeTest.cpp)
target_link_libraries(BinaryTreeTest gtest_main DataStructures)

add_executable(HeapTest HeapTest.cpp)
target_link_libraries(HeapTest gtest_main DataStructures)

add_executable(StackTest StackTest.cpp)
target_link_libraries(StackTest gtest_main DataStructures)

add_executable(PrefixTreeTest PrefixTreeTest.cpp)
target_link_libraries(PrefixTreeTest gtest_main DataStructures)

include(GoogleTest)
gtest_discover_tests(SortingTest)
gtest_discover_tests(DynamicArrayTest)
gtest_discover_tests(HashMapTest)
gtest_discover_tests(BinaryTreeTest)
gtest_discover_tests(HeapTest)
gtest_discover_tests(StackTest)
gtest_discover_tests(PrefixTreeTest)
