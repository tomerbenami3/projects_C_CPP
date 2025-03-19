#ifndef MT_HASH_TABLE_H
#define MT_HASH_TABLE_H

#include <vector>
#include <list>
#include <mutex>

namespace mt {


class Locker {
public:
    explicit Locker(std::mutex& mutex)
    : m_mutex(mutex) {
        m_mutex.lock();
    }

    ~Locker() {
        m_mutex.unlock();
    }

    Locker(const Locker&) = delete;
    Locker& operator=(const Locker&) = delete;

private:
    std::mutex& m_mutex;
};


template <typename K, typename V, typename HashFunc, typename EqualityFunc>
class HashTable {

public:
HashTable(size_t size, HashFunc hashFunc = HashFunc(), EqualityFunc equalFunc = EqualityFunc());

~HashTable() = default;
HashTable(HashTable const& other) = delete;
HashTable& operator=(HashTable const& other) = delete;

void insert(const K& key, const V& value);
bool lookup(K const& key, V& value);
bool remove(K const& key);


private:
    std::vector<std::list<std::pair<K, V>>> m_table;
    std::mutex m_table_mutex;
    size_t m_size;
    HashFunc m_hashFunction;
    EqualityFunc m_equalFunction;
};

}

#include "hash_table.txx"

#endif //MT_HASH_TABLE_H