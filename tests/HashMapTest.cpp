#include <gtest/gtest.h>

#include <string>

#include "DataStructures/HashMap.hpp"

TEST(HashMapTest, CreateHashMap) {
  HashMap<std::string, int> map;
  ASSERT_EQ(map.size(), 0);
}

TEST(HashMapTest, InsertKeyValue) {
  HashMap<std::string, int> map;
  map.insert("Tomato", 1);
}

TEST(HashMapTest, InsertGetKeyValue) {
  HashMap<std::string, int> map;
  map.insert("Tomato", 1);
  ASSERT_EQ(map.get("Tomato"), 1);
}

TEST(HashMapTest, IncludesKay) {
  HashMap<std::string, int> map;
  map.insert("Tomato", 1);
  ASSERT_TRUE(map.includes("Tomato"));
  ASSERT_FALSE(map.includes("Potato"));
}

TEST(HashMapTest, InsertRemoveKeyValues) {
  HashMap<std::string, int> map;
  map.insert("Tomato", 1);
  map.insert("Potato", 2);
  map.insert("Onion", 3);
  ASSERT_EQ(map.get("Tomato"), 1);
  ASSERT_EQ(map.get("Potato"), 2);
  ASSERT_EQ(map.get("Onion"), 3);
  map.remove("Potato");
  ASSERT_EQ(map.get("Tomato"), 1);
  ASSERT_EQ(map.get("Onion"), 3);
  EXPECT_THROW(map.get("Potato"), std::out_of_range);
}

TEST(HashMapTest, InsertManyElements) {
  HashMap<std::string, int> map;
  std::string baseKey{"hash map key "};
  int n{1000};
  for (int i{0}; i < n; ++i) {
    map.insert(baseKey + std::to_string(i), i);
  }
  ASSERT_EQ(map.size(), n);
  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(map.get(baseKey + std::to_string(i)), i);
  }
}

TEST(HashMapTest, GetKeyError) {
  HashMap<std::string, int> map;
  map.insert("Tomato", 1);

  EXPECT_THROW(
      {
        try {
          map.get("Potato");
        } catch (const std::out_of_range& e) {
          ASSERT_STREQ("Key not found!", e.what());
          throw;
        }
      },
      std::out_of_range);
}
