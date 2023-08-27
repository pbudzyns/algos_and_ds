#include <gtest/gtest.h>

#include "Sorting.h"

TEST(SortingTest, GetMin) { EXPECT_EQ(Sort::Min(2, 3), 2); }
