#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

/**
 * @brief Template for dynamic array container class.
 *
 * @details Dynamic array is a container that dynamically allocates or
 * deallocates memory depending on the number of elements inserted.
 * It allows for access to its elements in constant time `O(1)`. Insert and
 * delete works with `O(n)` complexity.
 *
 *
 * Example usage:
 * @code
 * DynamicArray<int> dynamicArray;
 * dynamicArray.insert(1);
 * int b{dynamicArray[0]};
 * @endcode
 *
 *
 * @tparam T Type of the stored values.
 */
template <typename T>
class DynamicArray
{
  public:
    /**
     * @brief Type used for indexing and size definition.
     *
     */
    using size_type = uint32_t;

    /**
     * @brief Construct a new DynamicArray object.
     *
     */
    DynamicArray() : m_Size{0}, m_Capacity{2}, m_Data{std::make_unique<T[]>(0)}
    {
    }

    /**
     * @brief Construct a new DynamicArray object from initializer list.
     *
     * @param list Initializer list.
     */
    DynamicArray(std::initializer_list<T> list)
        : m_Size{static_cast<size_type>(list.size())},
          m_Capacity{static_cast<size_type>(list.size())},
          m_Data{std::make_unique<T[]>(list.size())}
    {
        std::copy(list.begin(), list.end(), m_Data.get());
    }

    DynamicArray(const DynamicArray<T>& array)
    {
        *this = array;
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& array)
    {
        m_Capacity = array.m_Capacity;
        m_Size = array.m_Size;
        m_Data = std::make_unique<T[]>(m_Size);
        auto* p{array.m_Data.get()};
        std::copy(p, p + array.m_Size, m_Data.get());
        return *this;
    }

    DynamicArray(DynamicArray<T>&& array)
    {
        *this = std::move(array);
    }

    /**
     * @brief Destroy the DynamicArray object.
     *
     */
    ~DynamicArray() = default;

    DynamicArray<T>& operator=(DynamicArray<T>&& array)
    {
        m_Capacity = array.m_Capacity;
        m_Size = array.m_Size;
        m_Data = std::move(array.m_Data);
        array.m_Size = 0;
        array.m_Capacity = 0;
        return *this;
    }

    bool operator==(const DynamicArray<T>& other)
    {
        if (m_Size != other.m_Size)
            return false;
        for (int i{0}; i < m_Size; ++i)
        {
            if (get(i) != other.get(i))
                return false;
        }
        return true;
    }

    bool operator!=(const DynamicArray<T>& other)
    {
        return !(*this == other);
    }

    /**
     * @brief Return pointer to first element, for range loop.
     *
     * @return T* Pointer to the first element.
     */
    T* begin()
    {
        return m_Data.get();
    }

    const T* begin() const
    {
        return m_Data.get();
    }

    /**
     * @brief Return pointer to one past last elemente, for range loop.
     *
     * @return T* Pointer to one past last element.
     */
    T* end()
    {
        return m_Data.get() + m_Size;
    }

    const T* end() const
    {
        return m_Data.get() + m_Size;
    }

    /**
     * @brief Inserts element to the array.
     *
     * @details Allocates additional memory and copy array to new location if
     * size equals capacity.
     *
     * @param element The element to be inserted.
     */
    void insert(T element);

    /**
     * @brief Remove element at an index from the array.
     *
     * @details Reduces container capacity if the container becomes half empty.
     *
     * @param index Index of the element to remove.
     */
    void remove(size_type index);

    /**
     * @brief Access element at given index.
     *
     * @param index Index of the element to access.
     *
     * @return `T&` Reference to stored value.
     */
    T& operator[](size_type index)
    {
        return get(index);
    }

    /**
     * @brief Access element at given index.
     *
     * @param index Index of the element to access.
     *
     * @return `const T&` Const reference to stored value.
     */
    const T& operator[](size_type index) const
    {
        return get(index);
    }

    /**
     * @brief Access element at given index.
     *
     * @param index Index of the element to access.
     *
     * @return `T&` Reference to stored value.
     */
    T& get(size_type index);

    /**
     * @brief Access element at given index.
     *
     * @param index Index of the element to access.
     *
     * @return `const T&` Const reference to stored value.
     */
    const T& get(size_type index) const;

    /**
     * @brief Get number of items in the container.
     *
     * @return `size_type` Number of stored items.
     */
    size_type size() const
    {
        return m_Size;
    }

    /**
     * @brief Get capacity of the container.
     *
     * @return `size_type` Capacity of the container.
     */
    size_type capacity() const
    {
        return m_Capacity;
    }

    /**
     * @brief Check if the array is empty.
     *
     * @return `true` If the array is empty.
     * @return `false` If the array contains any elements.
     */
    bool empty() const
    {
        return m_Size == 0;
    }

  private:
    size_type m_Size;
    size_type m_Capacity;
    std::unique_ptr<T[]> m_Data;
    void resize(size_type newCapacity);
};

template <typename T>
void DynamicArray<T>::insert(T element)
{
    if (m_Size == m_Capacity)
        resize(m_Capacity * 2);
    m_Data[m_Size++] = element;
}

template <typename T>
void DynamicArray<T>::remove(size_type index)
{
    if (index >= m_Size)
        throw std::out_of_range("Index out of range!");

    --m_Size;
    while (index < m_Size)
    {
        m_Data[index] = m_Data[index + 1];
        ++index;
    }
    if (m_Size < (m_Capacity / 2))
    {
        resize(m_Capacity / 2);
    }
}

template <typename T>
T& DynamicArray<T>::get(size_type index)
{
    return const_cast<T&>(const_cast<const DynamicArray*>(this)->get(index));
}

template <typename T>
const T& DynamicArray<T>::get(size_type index) const
{
    if (index >= m_Size)
        throw std::out_of_range("Index out of range!");

    return m_Data[index];
}

template <typename T>
void DynamicArray<T>::resize(size_type newCapacity)
{
    std::unique_ptr<T[]> newData = std::make_unique<T[]>(newCapacity);

    std::copy(begin(), end(), newData.get());

    // Assigning to unique_ptr should free it's previous resource
    m_Data = std::move(newData);
    m_Capacity = newCapacity;
}
