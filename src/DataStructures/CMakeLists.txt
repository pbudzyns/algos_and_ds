add_library(DataStructures STATIC DynamicArray.hpp HashMap.hpp)

set_target_properties(DataStructures PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(DataStructures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
