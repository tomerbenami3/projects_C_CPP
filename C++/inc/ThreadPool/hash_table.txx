#include "hash_table.hpp"
#include <cstddef>

namespace mt {

template <typename K, typename V, typename HashFunc, typename EqualityFunc>
HashTable<K, V, HashFunc, EqualityFunc>::HashTable(size_t size, HashFunc hashFunc , EqualityFunc equalFunc)
: m_table(size)
, m_size(size)
, m_hashFunction(hashFunc)
, m_equalFunction(equalFunc)
{}

template <typename K, typename V, typename HashFunc, typename EqualityFunc>
void HashTable<K, V, HashFunc, EqualityFunc>::insert(K const& key, V const& value) 
{
    size_t index = m_hashFunction(key) % m_size;
    Locker lock(m_table_mutex);
    
    for(auto& pair : m_table[index]) {
        if(pair.first == key) {
            pair.second = value;
            m_table_mutex.unlock();
            return;
        }
    }
    m_table[index].emplace_back(key, value);
    m_table_mutex.unlock();
}

template <typename K, typename V, typename HashFunc, typename EqualityFunc>
bool HashTable<K, V, HashFunc, EqualityFunc>::lookup(K const& key, V& value)
{
    size_t index = m_hashFunction(key) % m_size;
    Locker lock(m_table_mutex);

    for (auto& pair : m_table[index]) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    return false;
}

template <typename K, typename V, typename HashFunc, typename EqualityFunc>
bool HashTable<K, V, HashFunc, EqualityFunc>::remove(K const& key)
{
    size_t index = m_hashFunction(key) % m_size;
    Locker lock(m_table_mutex);

    auto& bucket = m_table[index];
    for (auto pair = bucket.begin(); pair != bucket.end(); ++pair) {
        if (pair->first == key) {
            bucket.erase(pair);
            return true;
        }
    }
    m_table_mutex.unlock();
    return false;
}


}
