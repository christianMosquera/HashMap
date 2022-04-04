#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <stdexcept>
#include <functional>
#include <iostream>

template <class Key, class Hash=std::hash<Key>>
class HashTable {
public:
    // Member Types - do not modify
    using key_type = Key;
    using value_type = Key;
    using hash = Hash;
    using size_type = size_t;
    // you can write your code below this

private:
    // TODO: student implementation
    std::vector<std::list<value_type>> hashmap;
    size_t bucket;
    size_t count;
    int currentLoad;
    int maxLoad;
    
public:
    HashTable() : hashmap(hashmap(11, std::list<value_type>())), bucket(11), count(0), currentLoad(0), maxLoad(1) {}
    HashTable(const HashTable& other);
    ~HashTable();
    HashTable& operator=(const HashTable& other);
    HashTable(size_type buckets) : hashmap(hashmap(bucket, std::list<value_type>())), bucket(bucket), count(0), currentLoad(0), maxLoad(1) {}
    
    bool is_empty() const;
    size_t size() const;

    void make_empty();
    bool insert(const value_type& value);
    size_t remove(const key_type& key);
    bool contains(const key_type& key);
    
    size_t bucket_count() const;
    size_t bucket_size(size_t n) const;
    
    size_t bucket(const key_type& key) const {
        return Hash{}(key) % hashmap.size();
    }

    float load_factor() const;
    float max_load_factor() const;
    void max_load_factor(float mlf);
    void rehash(size_type count);

    void print_table(std::ostream& os=std::cout) const;

    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};


template <class Key, class Hash>
bool HashTable<Key, Hash>::is_empty() const {
    return count == 0;
}

template <class Key, class Hash>
size_t HashTable<Key, Hash>::size() const {
    return count;
}

template <class Key, class Hash>
size_t HashTable<Key, Hash>::bucket_count() const {
    return bucket;
}

template <class Key, class Hash>


#endif  // HASHTABLE_SEPARATE_CHAINING_H
