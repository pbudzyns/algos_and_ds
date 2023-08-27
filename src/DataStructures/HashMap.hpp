#pragma once

#include <cstdint>
#include <functional>
#include <iostream>
typedef uint32_t size_type;

namespace impl {

template <typename K, typename V>
class ListNode {
 public:
  ListNode(const K& key, const V& value)
      : m_Key{key}, m_Value{value}, m_Next{nullptr} {}

  // Getters
  inline K& getKey() { return m_Key; }
  inline V& getValue() { return m_Value; }
  inline ListNode<K, V>* getNext() { return m_Next; }

  // Setters
  void setValue(const V& value) { m_Value = value; }
  void setNext(ListNode<K, V>* next) { m_Next = next; }

 private:
  ListNode<K, V>* m_Next;
  K m_Key;
  V m_Value;
};

template <typename K, typename V>
class LinkedList {
 public:
  LinkedList() {}
  ~LinkedList() {
    ListNode<K, V>* node = m_Root;
    while (node) {
      ListNode<K, V>* prev = node;
      node = node->getNext();
      delete prev;
    }
  }
  void insertKeyValue(const K& key, const V& value) {
    ListNode<K, V>* node{m_Root};
    ListNode<K, V>* newNode{new ListNode<K, V>(key, value)};
    if (!node) {
      m_Root = newNode;
      return;
    }

    ListNode<K, V>* prev{nullptr};
    while (node && node->getKey() != key) {
      prev = node;
      node = node->getNext();
    }
    if (node) {
      node->setValue(value);
    } else {
      prev->setNext(newNode);
    }
  }
  ListNode<K, V>* find(const K& key) {
    ListNode<K, V>* node{m_Root};
    while (node && node->getKey() != key) {
      node = node->getNext();
    }
    return node;
  }
  bool removeKey(const K& key) {
    ListNode<K, V>* prev{nullptr};
    ListNode<K, V>* node = m_Root;
    std::cout << node->getKey() << std::endl;
    while (node && node->getKey() != key) {
      prev = node;
      node = node->getNext();
    }
    if (!node) {
      return false;
    }
    if (prev) {
      prev->setNext(node->getNext());
    } else {
      m_Root = node->getNext();
    }
    delete node;
    return true;
  }

 private:
  ListNode<K, V>* m_Root;
};

template <typename K>
class HashFunction {
 public:
  size_type operator()(const K& key, size_type capacity) {
    auto hash_value{std::hash<K>{}(key)};
    return static_cast<size_type>(hash_value) % capacity;
  }
};

}  // namespace impl

using impl::HashFunction;
using impl::LinkedList;
using impl::ListNode;

template <typename K, typename V>
class HashMap {
 public:
  HashMap()
      : m_Size{0}, m_Capacity{2}, m_Table{new LinkedList<K, V>*[m_Capacity]} {
    initTable();
  }
  ~HashMap() { delete[] m_Table; }
  void insert(const K& key, const V& value) {
    size_type index{getKeyIndex(key)};
    m_Table[index]->insertKeyValue(key, value);
  }
  void remove(const K& key) {
    size_type index{getKeyIndex(key)};
    std::cout << "geting list for key " << key << std::endl;
    LinkedList<K, V>* list{m_Table[index]};
    if (!list->removeKey(key)) {
      throw std::out_of_range("Key not found!");
    }
  }
  V& get(const K& key) {
    size_type index{getKeyIndex(key)};
    LinkedList<K, V>* list{m_Table[index]};
    ListNode<K, V>* node{list->find(key)};
    if (!node) {
      throw std::out_of_range("Key not found!");
    }
    return node->getValue();
  }
  bool includes(const K& key) {
    size_type index{getKeyIndex(key)};
    LinkedList<K, V>* list{m_Table[index]};
    ListNode<K, V>* node{list->find(key)};
    return node != nullptr;
  }

 private:
  HashFunction<K> m_HashFn;
  LinkedList<K, V>** m_Table;
  size_type m_Size;
  size_type m_Capacity;
  void initTable() {
    for (size_type i{0}; i < m_Capacity; ++i) {
      m_Table[i] = new LinkedList<K, V>;
    }
  }
  inline size_type getKeyIndex(const K& key) {
    return m_HashFn(key, m_Capacity);
  }
};
