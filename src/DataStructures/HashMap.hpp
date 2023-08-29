#pragma once

#include <cstdint>
#include <functional>

namespace _hashmap_impl {

/**
 * @brief Linked list node template.
 *
 * @tparam K Type of keys.
 * @tparam V Type of values.
 */
template <typename K, typename V>
class ListNode {
 public:
  /**
   * @brief Construct a new ListNode object
   *
   * @param key Key to store.
   * @param value Value to store.
   */
  ListNode(const K& key, const V& value)
      : m_Key{key}, m_Value{value}, m_Next{nullptr} {}

  /**
   * @brief Destroy the ListNode object
   *
   */
  ~ListNode() = default;

  /**
   * @brief Get the key value.
   *
   * @return `K&` Reference to the key.
   */
  K& getKey() { return m_Key; }

  /**
   * @brief Get the value.
   *
   * @return `V&` Reference to the value.
   */
  V& getValue() { return m_Value; }

  /**
   * @brief Get the connected ListNode.
   *
   * @return `ListNode<K, V>*` Pointer to the next node.
   */
  ListNode<K, V>* getNext() { return m_Next; }

  /**
   * @brief Set the ListNode value.
   *
   * @param value Value to set.
   */
  void setValue(const V& value) { m_Value = value; }

  /**
   * @brief Set the pointer to next ListNode.
   *
   * @param next Pointer to next node.
   */
  void setNext(ListNode<K, V>* next) { m_Next = next; }

 private:
  ListNode<K, V>* m_Next;
  K m_Key;
  V m_Value;
};

/**
 * @brief Linked list template.
 *
 * @tparam K Type of keys.
 * @tparam V Type of values.
 */
template <typename K, typename V>
class LinkedList {
 public:
  /**
   * @brief Construct a new LinkedList object.
   *
   */
  LinkedList() : m_Root{nullptr} {};

  /**
   * @brief Destroy the LinkedList object
   *
   */
  ~LinkedList();

  /**
   * @brief Insert key-value pair to the LinkedList.
   *
   * @details Creates new ListNode node and connects it to the end of the
   * LinkedList.
   *
   * @param key Key to store.
   * @param value Value to store.
   */
  void insertKeyValue(const K& key, const V& value);

  /**
   * @brief Remove key from the LinkedList.
   *
   * @details Search for ListNode with a diven key.
   * Remove if from the linked list if found.
   *
   * @param key Key to remove.
   * @return `true` If node for the key was found and removed.
   * @return `false` If node for the key was not found.
   */
  bool removeKey(const K& key);

  /**
   * @brief Find ListNode for the key in the LinkedList.
   *
   * @param key Key to search for.
   * @return `ListNode<K, V>*` Pointer to the node containing the key.
   * `nullptr` if key was not found.
   */
  ListNode<K, V>* find(const K& key);

  /**
   * @brief Get the pointer to root node.
   *
   * @return `ListNode<K, V>*` Pointer to the root node.
   * `nullptr` if list is empty.
   */
  ListNode<K, V>* getRoot() { return m_Root; }

 private:
  ListNode<K, V>* m_Root;
};

/**
 * @brief Hashing function object template.
 *
 * @tparam K Type of keys.
 * @tparam T Type of hash value.
 */
template <typename K, typename T>
class HashFunction {
 public:
  /**
   * @brief Get hash index for the key.
   *
   * @details Returns value from `[0-capacity)` range of type `T`.
   *
   * @param key Key to hash.
   * @param capacity Capacity of the container.
   * @return `T` Index of type T.
   */
  T operator()(const K& key, T capacity) const {
    auto hash_value{std::hash<K>{}(key)};
    return static_cast<T>(hash_value) % capacity;
  }
};

}  // namespace _hashmap_impl

using _hashmap_impl::HashFunction;
using _hashmap_impl::LinkedList;
using _hashmap_impl::ListNode;

/**
 * @brief Template for hash map container.
 *
 * @details Hash map implementation using hash table and LinkedList. HashMap
 * allows to store `key : value` pairs and access them in (almost) constant time
 * `O(1)`. This implementation dynamically increases hash table size to reduce
 * number of collisions.
 *
 * Example usage:
 * @code
 * HashMap<std::string, int> map;
 * map.insert("apple", 1);
 * map.insert("banana", 2);
 * map.get("apple"); // == 1
 * @endcode
 *
 * @tparam K Type of the key variables.
 * @tparam V Type of the value variables.
 */
template <typename K, typename V>
class HashMap {
 public:
  /**
   * @brief Type used for indexing and size definition.
   *
   */
  typedef uint32_t size_type;

  /**
   * @brief Construct a new Hash Map object.
   *
   */
  HashMap()
      : m_Size{0},
        m_TableCapacity{2},
        m_Table{new LinkedList<K, V>*[m_TableCapacity]} {
    initTable();
  }

  /**
   * @brief Destroy the Hash Map object.
   *
   * @details Cleans the underlying hash table of LinkedList.
   *
   */
  ~HashMap() {
    for (size_type i{0}; i < m_TableCapacity; ++i) {
      delete m_Table[i];
    }
    delete[] m_Table;
  }

  /**
   * @brief Insert a key-value pair to the HashMap.
   *
   * @param key Key to store the value under.
   * @param value Value to be stored.
   */
  void insert(const K& key, const V& value);

  /**
   * @brief Remove key-value pair from the HashMap.
   *
   * @param key Key to remove.
   */
  void remove(const K& key);

  /**
   * @brief Get value stored under a key.
   *
   * @param key Key to retrieve value for.
   * @return `V&` Reference to value under the key.
   */
  V& get(const K& key);

  /**
   * @brief Check if HashMap includes a key.
   *
   * @param key Key to check.
   * @return `true` If hash map includes the key.
   * @return `false` If hash map does not include the key.
   */
  bool includes(const K& key) const;

  /**
   * @brief Get number of items in the HashMap.
   *
   * @return `size_type` Number of items in the hash map.
   */
  size_type size() const { return m_Size; }

 private:
  _hashmap_impl::LinkedList<K, V>** m_Table;
  const _hashmap_impl::HashFunction<K, size_type> m_HashFn{};
  size_type m_TableCapacity;
  size_type m_Size;

  void initTable();
  void resizeTable(size_type newTableCapacity);
  size_type getKeyIndex(const K& key) const;
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
bool HashMap<K, V>::includes(const K& key) const {
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
typename HashMap<K, V>::size_type HashMap<K, V>::getKeyIndex(
    const K& key) const {
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
