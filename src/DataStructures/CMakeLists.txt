set(
    HEADER_FILES
    BinaryTree.hpp
    DynamicArray.hpp 
    HashMap.hpp
    Heap.hpp
    Stack.hpp
    PrefixTree.hpp
)

set(
    SOURCE_FILES
    PrefixTree.cpp
)

add_library(DataStructures STATIC ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(DataStructures PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(DataStructures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
