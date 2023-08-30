#include "DataStructures/PrefixTree.hpp"

// ------- Prefix Tree implementation ---------------

using _prefix_tree_imp::TreeNode;

PrefixTree::PrefixTree() : m_Root{new TreeNode('^')} {}

PrefixTree::~PrefixTree() { deleteNode(m_Root); }

void PrefixTree::insert(const std::string& string) {
  TreeNode* root{m_Root};
  TreeNode* child;
  for (char c : string) {
    if (root->getChild(c)) {
      root = root->getChild(c);
    } else {
      root->addChild(c);
      root = root->getChild(c);
    }
  }
  root->addChild('\0');
}

bool PrefixTree::contains(const std::string& prefix) {
  TreeNode* root{m_Root};
  for (char c : prefix) {
    if (!(root = root->getChild(c))) {
      return false;
    }
  }
  return true;
}

std::vector<std::string> PrefixTree::getStrings(const std::string& prefix) {
  TreeNode* last{m_Root};
  for (char c : prefix) {
    last = last->getChild(c);
    if (!last) {
      return {};
    }
  }

  std::vector<std::string> suffixes;

  getSuffixes(&suffixes, prefix, last);

  return suffixes;
}

void PrefixTree::getSuffixes(std::vector<std::string>* suffixes,
                             std::string prefix, TreeNode* root) {
  for (TreeNode* node : root->children) {
    if (node->c != '\0') {
      getSuffixes(suffixes, prefix + node->c, node);
    } else {
      suffixes->push_back(prefix);
    }
  }
}

void PrefixTree::deleteNode(TreeNode* root) {
  if (!root) {
    return;
  }
  for (TreeNode* node : root->children) {
    deleteNode(node);
  }
  delete root;
}

// ------- Tree Node implementation ---------------

TreeNode* TreeNode::getChild(char c) {
  for (TreeNode* child : children) {
    if (child->c == c) {
      return child;
    }
  }
  return nullptr;
}

void TreeNode::addChild(char c) { children.push_back(new TreeNode(c)); }
