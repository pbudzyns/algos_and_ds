#pragma once

#include <cstdint>
#include <functional>
#include <stdexcept>

namespace hashmap_impl
{

/**
 * @brief Linked list node template.
 *
 * @tparam Key Type of keys.
 * @tparam Value Type of values.
 */
template <typename Key, typename Value>
class ListNode
{
  public:
    /**
     * @brief Construct a new ListNode object
     *
     * @param key Key to store.
     * @param value Value to store.
     */
    ListNode(const Key& key, const Value& value)
        : m_Key{key}, m_Value{value}, m_Next{nullptr}
    {
    }

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
    Key& getKey()
    {
        return m_Key;
    }

    /**
     * @brief Get the value.
     *
     * @return `V&` Reference to the value.
     */
    Value& getValue()
    {
        return m_Value;
    }

    /**
     * @brief Get the connected ListNode.
     *
     * @return `ListNode<K, V>*` Pointer to the next node.
     */
    ListNode<Key, Value>* getNext()
    {
        return m_Next;
    }

    /**
     * @brief Set the ListNode value.
     *
     * @param value Value to set.
     */
    void setValue(const Value& value)
    {
        m_Value = value;
    }

    /**
     * @brief Set the pointer to next ListNode.
     *
     * @param next Pointer to next node.
     */
    void setNext(ListNode<Key, Value>* next)
    {
        m_Next = next;
    }

  private:
    ListNode<Key, Value>* m_Next;
    Key m_Key;
    Value m_Value;
};

/**
 * @brief Linked list template.
 *
 * @tparam Key Type of keys.
 * @tparam Value Type of values.
 */
template <typename Key, typename Value>
class LinkedList
{
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
    void insertKeyValue(const Key& key, const Value& value);

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
    bool removeKey(const Key& key);

    /**
     * @brief Find ListNode for the key in the LinkedList.
     *
     * @param key Key to search for.
     * @return `ListNode<K, V>*` Pointer to the node containing the key.
     * `nullptr` if key was not found.
     */
    ListNode<Key, Value>* find(const Key& key);

    /**
     * @brief Get the pointer to root node.
     *
     * @return `ListNode<K, V>*` Pointer to the root node.
     * `nullptr` if list is empty.
     */
    ListNode<Key, Value>* getRoot()
    {
        return m_Root;
    }

  private:
    ListNode<Key, Value>* m_Root;
};

/**
 * @brief Hashing function object template.
 *
 * @tparam Key Type of keys.
 * @tparam SizeType Type of hash value.
 */
template <typename Key, typename SizeType>
class HashFunction
{
  public:
    /**
     * @brief Get hash index for the key.
     *
     * @details Returns value from `[0-capacity)` range of type `SizeType`.
     *
     * @param key Key to hash.
     * @param capacity Capacity of the container.
     * @return `SizeType` Index of type SizeType.
     */
    SizeType operator()(const Key& key, SizeType capacity) const
    {
        auto hash_value{std::hash<Key>{}(key)};
        return static_cast<SizeType>(hash_value) % capacity;
    }
};

} // namespace hashmap_impl

using hashmap_impl::HashFunction;
using hashmap_impl::LinkedList;
using hashmap_impl::ListNode;

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
 * @tparam Key Type of the key variables.
 * @tparam Value Type of the value variables.
 */
template <typename Key, typename Value>
class HashMap
{
  public:
    /**
     * @brief Type used for indexing and size definition.
     *
     */
    using size_type = uint32_t;

    /**
     * @brief Construct a new Hash Map object.
     *
     */
    HashMap()
        : m_Size{0}, m_TableCapacity{2},
          m_Table{new LinkedList<Key, Value>*[m_TableCapacity]}
    {
        initTable();
    }

    /**
     * @brief Destroy the Hash Map object.
     *
     * @details Cleans the underlying hash table of LinkedList.
     *
     */
    ~HashMap()
    {
        for (size_type i{0}; i < m_TableCapacity; ++i)
        {
            // Delete linked list at intex i
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
    void insert(const Key& key, const Value& value);

    /**
     * @brief Remove key-value pair from the HashMap.
     *
     * @param key Key to remove.
     */
    void remove(const Key& key);

    /**
     * @brief Get value stored under a key.
     *
     * @param key Key to retrieve value for.
     * @return `V&` Reference to value under the key.
     */
    Value& get(const Key& key);

    /**
     * @brief Check if HashMap includes a key.
     *
     * @param key Key to check.
     * @return `true` If hash map includes the key.
     * @return `false` If hash map does not include the key.
     */
    bool includes(const Key& key) const;

    /**
     * @brief Get number of items in the HashMap.
     *
     * @return `size_type` Number of items in the hash map.
     */
    size_type size() const
    {
        return m_Size;
    }

  private:
    hashmap_impl::LinkedList<Key, Value>** m_Table;
    const hashmap_impl::HashFunction<Key, size_type> m_HashFn{};
    size_type m_TableCapacity;
    size_type m_Size;

    void initTable();
    void resizeTable(size_type newTableCapacity);
    size_type getKeyIndex(const Key& key) const;
};

// ------ HashMap Implementation ----------------------

template <typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key& key, const Value& value)
{
    if (m_Size + 1 >= m_TableCapacity)
    {
        resizeTable(m_TableCapacity * 2);
    }
    size_type index{getKeyIndex(key)};
    m_Table[index]->insertKeyValue(key, value);
    ++m_Size;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::remove(const Key& key)
{
    size_type index{getKeyIndex(key)};
    LinkedList<Key, Value>* list{m_Table[index]};
    if (!list->removeKey(key))
    {
        throw std::out_of_range("Key not found!");
    }
    --m_Size;
}

template <typename Key, typename Value>
Value& HashMap<Key, Value>::get(const Key& key)
{
    size_type index{getKeyIndex(key)};
    LinkedList<Key, Value>* list{m_Table[index]};
    ListNode<Key, Value>* node{list->find(key)};
    if (!node)
    {
        throw std::out_of_range("Key not found!");
    }
    return node->getValue();
}

template <typename Key, typename Value>
bool HashMap<Key, Value>::includes(const Key& key) const
{
    size_type index{getKeyIndex(key)};
    LinkedList<Key, Value>* list{m_Table[index]};
    ListNode<Key, Value>* node{list->find(key)};
    return node != nullptr;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::initTable()
{
    for (size_type i{0}; i < m_TableCapacity; ++i)
    {
        m_Table[i] = new LinkedList<Key, Value>;
    }
}

template <typename Key, typename Value>
void HashMap<Key, Value>::resizeTable(size_type newTableCapacity)
{
    LinkedList<Key, Value>** oldTable = m_Table;
    size_type oldTableCapacity = m_TableCapacity;

    m_Table = new LinkedList<Key, Value>*[newTableCapacity];
    m_TableCapacity = newTableCapacity;
    m_Size = 0;
    initTable();

    for (size_type i{0}; i < oldTableCapacity; ++i)
    {
        ListNode<Key, Value>* node = oldTable[i]->getRoot();
        while (node)
        {
            insert(node->getKey(), node->getValue());
            node = node->getNext();
        }
    }
    delete[] oldTable;
}

template <typename Key, typename Value>
typename HashMap<Key, Value>::size_type HashMap<Key, Value>::getKeyIndex(
    const Key& key) const
{
    return m_HashFn(key, m_TableCapacity);
}

// ------ LinkedList Implementation ----------------------

template <typename Key, typename Value>
LinkedList<Key, Value>::~LinkedList()
{
    ListNode<Key, Value>* node = m_Root;
    while (node)
    {
        ListNode<Key, Value>* prev = node;
        node = node->getNext();
        delete prev;
    }
}

template <typename Key, typename Value>
void LinkedList<Key, Value>::insertKeyValue(const Key& key, const Value& value)
{
    ListNode<Key, Value>* node{m_Root};
    ListNode<Key, Value>* newNode{new ListNode<Key, Value>(key, value)};
    if (!node)
    {
        m_Root = newNode;
        return;
    }

    ListNode<Key, Value>* prev{nullptr};
    while (node && node->getKey() != key)
    {
        prev = node;
        node = node->getNext();
    }
    if (node)
    {
        node->setValue(value);
    }
    else
    {
        prev->setNext(newNode);
    }
}

template <typename Key, typename Value>
ListNode<Key, Value>* LinkedList<Key, Value>::find(const Key& key)
{
    ListNode<Key, Value>* node{m_Root};
    while (node && node->getKey() != key)
    {
        node = node->getNext();
    }
    return node;
}

template <typename Key, typename Value>
bool LinkedList<Key, Value>::removeKey(const Key& key)
{
    ListNode<Key, Value>* prev{nullptr};
    ListNode<Key, Value>* node = m_Root;
    while (node && node->getKey() != key)
    {
        prev = node;
        node = node->getNext();
    }
    if (!node)
    {
        return false;
    }
    if (prev)
    {
        prev->setNext(node->getNext());
    }
    else
    {
        m_Root = node->getNext();
    }
    delete node;
    return true;
}
