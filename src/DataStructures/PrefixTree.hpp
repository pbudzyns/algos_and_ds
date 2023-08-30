#pragma once

#include <string>
#include <vector>

namespace _prefix_tree_imp {
/**
 * @brief N-ary Tree Node struct to hold char values.
 *
 */
struct TreeNode {
  /**
   * @brief Construct a new TreeNode struct.
   *
   * @param c_ Char value to hold.
   */
  explicit TreeNode(char c_) : c{c_} {};

  /**
   * @brief Node value.
   *
   */
  char c;

  /**
   * @brief Pointers to child nodes.
   *
   */
  std::vector<TreeNode*> children;

  /**
   * @brief Add child node.
   *
   * @param c Char value of the child node.
   */
  void addChild(char c);

  /**
   * @brief Get the child node that holds char value.
   *
   * @details Returns `nullptr` if value not found.
   *
   * @param c Char value to search for.
   * @return `TreeNode*` Pointer to child holding the value.
   */
  TreeNode* getChild(char c);
};
}  // namespace _prefix_tree_imp

/**
 * @brief Prefix tree that stores strings.
 *
 * @details Implementation of prefix tree to store strings as a n-ary tree of
 * nodes with `char` values. Capable of testing for inclusion and retrieving all
 * strings for a given prefix.
 *
 * Example usage:
 * @code
 * PrefixTree tree;
 * tree.insert("apple");
 * tree.insert("application");
 * tree.insert("banana");
 * tree.getStrings("app"); // == {"apple", "application"}
 * @endcode
 *
 */
class PrefixTree {
 public:
  /**
   * @brief Construct a new PrefixTree object.
   *
   */
  PrefixTree();

  /**
   * @brief Destroy the PrefixTree object.
   *
   * @details Deletes TreeNode recursively.
   */
  ~PrefixTree();

  /**
   * @brief Insert string to the PrefixTree.
   *
   * @param string String to insert.
   */
  void insert(const std::string& string);

  /**
   * @brief Check if PrefixTree contains a prefix.
   *
   * @param prefix Prefix to check.
   * @return `true` If prefix is present.
   * @return `false` If prefix is absent.
   */
  bool contains(const std::string& prefix);

  /**
   * @brief Get all strings starting with a given prefix.
   *
   * @param prefix Prefix to retrieve strings for.
   * @return `std::vector<std::string>` Vector of strings.
   */
  std::vector<std::string> getStrings(const std::string& prefix);

 private:
  _prefix_tree_imp::TreeNode* m_Root;

  void getSuffixes(std::vector<std::string>* suffixes, std::string prefix,
                   _prefix_tree_imp::TreeNode* root);
  void deleteNode(_prefix_tree_imp::TreeNode* node);
};
