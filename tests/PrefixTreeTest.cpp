#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "DataStructures/PrefixTree.hpp"

TEST(PrefixTreeTest, CreateTree) { PrefixTree tree; }

TEST(PrefixTreeTest, InsertString) {
  PrefixTree tree;
  tree.insert("apple");
  tree.insert("apple pie");
  tree.insert("banana");
}

TEST(PrefixTreeTest, ContainsPrefix) {
  PrefixTree tree;
  ASSERT_TRUE(tree.contains(""));
  tree.insert("apple");
  tree.insert("apple pie");
  tree.insert("banana");
  ASSERT_TRUE(tree.contains(""));
}

TEST(PrefixTreeTest, ContainsEmptyPrefix) {
  PrefixTree tree;
  std::string s1{"apple"};
  std::string s2{"apple pie"};
  std::string s3{"banana"};

  tree.insert(s1);
  tree.insert(s2);
  tree.insert(s3);

  for (int i{1}; i < s1.size(); ++i) {
    ASSERT_TRUE(tree.contains(s1.substr(0, i)));
  }
  for (int i{1}; i < s2.size(); ++i) {
    ASSERT_TRUE(tree.contains(s2.substr(0, i)));
  }
  for (int i{1}; i < s3.size(); ++i) {
    ASSERT_TRUE(tree.contains(s2.substr(0, i)));
  }
  ASSERT_FALSE(tree.contains("api"));
}

TEST(PrefixTreeTest, GetStrings) {
  PrefixTree tree;
  tree.insert("apple");
  tree.insert("apple pie");
  tree.insert("banana");

  std::string prefix{"app"};
  std::vector<std::string> expected{"apple", "apple pie"};
  ASSERT_EQ(tree.getStrings(prefix), expected);
}

TEST(PrefixTreeTest, GetStringsEmptyPrefix) {
  PrefixTree tree;
  std::vector<std::string> expected;
  ASSERT_EQ(tree.getStrings(""), expected);
  tree.insert("apple");
  tree.insert("apple pie");
  tree.insert("banana");
  expected = {"apple", "apple pie", "banana"};
  ASSERT_EQ(tree.getStrings(""), expected);
}
