#pragma once

#include <cstdint>
#include <functional>

namespace _hashmap_impl {

template <typename K, typename V>
class ListNode {
 public:
  ListNode(const K& key, const V& value)
      : m_Key{key}, m_Value{value}, m_Next{nullptr} {}

  ~ListNode() = default;
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
  LinkedList() : m_Root{nullptr} {};
  ~LinkedList();
  void insertKeyValue(const K& key, const V& value);
  bool removeKey(const K& key);
  ListNode<K, V>* find(const K& key);
  ListNode<K, V>* getRoot() { return m_Root; }

 private:
  ListNode<K, V>* m_Root;
};

template <typename K, typename T>
class HashFunction {
 public:
  T operator()(const K& key, T capacity) {
    auto hash_value{std::hash<K>{}(key)};
    return static_cast<T>(hash_value) % capacity;
  }
};

}  // namespace _hashmap_impl

using _hashmap_impl::HashFunction;
using _hashmap_impl::LinkedList;
using _hashmap_impl::ListNode;

template <typename K, typename V>
class HashMap {
 public:
  typedef uint32_t size_type;

  HashMap()
      : m_Size{0},
        m_TableCapacity{2},
        m_Table{new LinkedList<K, V>*[m_TableCapacity]} {
    initTable();
  }
  ~HashMap() {
    for (size_type i{0}; i < m_TableCapacity; ++i) {
      delete m_Table[i];
    }
    delete[] m_Table;
  }
  void insert(const K& key, const V& value);
  void remove(const K& key);
  V& get(const K& key);
  bool includes(const K& key);

 private:
  LinkedList<K, V>** m_Table;
  HashFunction<K, size_type> m_HashFn;
  size_type m_TableCapacity;
  size_type m_Size;
  void initTable();
  void resizeTable(size_type newTableCapacity);
  inline size_type getKeyIndex(const K& key);
};

// ------ HashMap Implementation ----------------------

template <typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value) {
  if (m_Size + 1 >= m_TableCapacity) {
    resizeTable(m_TableCapacity * 2);
  }
  size_type index{getKeyIndex(key)};
  m_Table[index]->insertKeyValue(key, value);
  ++m_Size;
}

template <typename K, typename V>
void HashMap<K, V>::remove(const K& key) {
  size_type index{getKeyIndex(key)};
  LinkedList<K, V>* list{m_Table[index]};
  if (!list->removeKey(key)) {
    throw std::out_of_range("Key not found!");
  }
  --m_Size;
}

template <typename K, typename V>
V& HashMap<K, V>::get(const K& key) {
  size_type index{getKeyIndex(key)};
  LinkedList<K, V>* list{m_Table[index]};
  ListNode<K, V>* node{list->find(key)};
  if (!node) {
    throw std::out_of_range("Key not found!");
  }
  return node->getValue();
}

template <typename K, typename V>
bool HashMap<K, V>::includes(const K& key) {
  size_type index{getKeyIndex(key)};
  LinkedList<K, V>* list{m_Table[index]};
  ListNode<K, V>* node{list->find(key)};
  return node != nullptr;
}

template <typename K, typename V>
void HashMap<K, V>::initTable() {
  for (size_type i{0}; i < m_TableCapacity; ++i) {
    m_Table[i] = new LinkedList<K, V>;
  }
}

template <typename K, typename V>
void HashMap<K, V>::resizeTable(size_type newTableCapacity) {
  LinkedList<K, V>** oldTable = m_Table;
  size_type oldTableCapacity = m_TableCapacity;

  m_Table = new LinkedList<K, V>*[newTableCapacity];
  m_TableCapacity = newTableCapacity;
  m_Size = 0;
  initTable();

  for (size_type i{0}; i < oldTableCapacity; ++i) {
    ListNode<K, V>* node = oldTable[i]->getRoot();
    while (node) {
      insert(node->getKey(), node->getValue());
      node = node->getNext();
    }
  }
  delete[] oldTable;
}

template <typename K, typename V>
inline typename HashMap<K, V>::size_type HashMap<K, V>::getKeyIndex(
    const K& key) {
  return m_HashFn(key, m_TableCapacity);
}

// ------ LinkedList Implementation ----------------------

template <typename K, typename V>
LinkedList<K, V>::~LinkedList() {
  ListNode<K, V>* node = m_Root;
  while (node) {
    ListNode<K, V>* prev = node;
    node = node->getNext();
    delete prev;
  }
}

template <typename K, typename V>
void LinkedList<K, V>::insertKeyValue(const K& key, const V& value) {
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

template <typename K, typename V>
ListNode<K, V>* LinkedList<K, V>::find(const K& key) {
  ListNode<K, V>* node{m_Root};
  while (node && node->getKey() != key) {
    node = node->getNext();
  }
  return node;
}

template <typename K, typename V>
bool LinkedList<K, V>::removeKey(const K& key) {
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
