#include "mu_test.h"
#include "hash_table.hpp"
#include <iostream>
#include <thread>
#include <vector>

struct HashFunc {
    size_t operator()(const int& key) const {
        return key % 10;
    }
};

struct EqualFunc {
    bool operator()(const int& a, const int& b) const {
        return a == b;
    }
};


BEGIN_TEST(test_insert_lookup)
{
    mt::HashTable<int, std::string, HashFunc, EqualFunc> testTable(10);

    testTable.insert(1, "one");
    std::string value;
    
    ASSERT_THAT(testTable.lookup(1, value));
    ASSERT_THAT(value == "one");
}
END_TEST

BEGIN_TEST(test_update_key)
{
    mt::HashTable<int, std::string, HashFunc, EqualFunc> testTable(10);

    testTable.insert(1, "updated_one");
    std::string value;
    
    ASSERT_THAT(testTable.lookup(1, value));
    ASSERT_THAT(value == "updated_one");
}
END_TEST

BEGIN_TEST(test_remove_key)
{
    mt::HashTable<int, std::string, HashFunc, EqualFunc> testTable(10);

    testTable.insert(1, "to_be_removed");
    ASSERT_THAT(testTable.remove(1));

    std::string value;
    ASSERT_THAT(!testTable.lookup(1, value));
}
END_TEST

BEGIN_TEST(test_lookup_fail)
{
    mt::HashTable<int, std::string, HashFunc, EqualFunc> testTable(10);

    std::string value;
    ASSERT_THAT(!testTable.lookup(21, value)); // Non-existent key
}
END_TEST

BEGIN_TEST(test_multithreading)
{
    mt::HashTable<int, int, HashFunc, EqualFunc> table(20);

    auto insertFunc = [&table](int start) {
        for (int i = start; i < start + 10; ++i) {
            table.insert(i, i * 10);
        }
    };

    // Launch threads
    std::thread t1(insertFunc, 0);
    std::thread t2(insertFunc, 10);
    std::thread t3(insertFunc, 20);

    t1.join();
    t2.join();
    t3.join();

    int value;
    ASSERT_THAT(table.lookup(5, value) && value == 50);
    ASSERT_THAT(table.lookup(15, value) && value == 150);
    ASSERT_THAT(table.lookup(25, value) && value == 250);
}
END_TEST

BEGIN_TEST(concurrent_insertion)
{
    mt::HashTable<int, std::string, HashFunc, EqualFunc> table(20);

    auto insert_func = [&table](int key, const std::string& value) {
        table.insert(key, value);
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i) {
        threads.emplace_back(insert_func, i, "value_" + std::to_string(i));
    }

    for (auto& t : threads) {
        t.join();
    }
//a
    for (int i = 0; i < 100; ++i) {
        std::string value;
        ASSERT_THAT(table.lookup(i, value));
        ASSERT_THAT(value == "value_" + std::to_string(i));
    }
}
END_TEST


BEGIN_SUITE(Hash Table Thread-Safe Tests)
    TEST(test_insert_lookup)
    TEST(test_update_key)
    TEST(test_remove_key)
    TEST(test_lookup_fail)
    TEST(test_multithreading)
    TEST(concurrent_insertion)
END_SUITE
