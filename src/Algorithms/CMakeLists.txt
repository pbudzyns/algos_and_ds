add_library(Algorithms STATIC Sorting.cpp Sorting.hpp)

target_include_directories(Algorithms INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
