#include <gtest/gtest.h>

#include "Algorithms/Sorting.hpp"

TEST(SortingTest, GetMin) { EXPECT_EQ(Sort::Min(2, 3), 2); }
