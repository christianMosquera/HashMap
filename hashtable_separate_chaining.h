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
    size_t bucket_num;
    size_t count;
    float currentLoad;
    float maxLoad;
    
public:

    HashTable() : hashmap(11), bucket_num(11), count(0), currentLoad(0), maxLoad(1) {}


    HashTable(const HashTable& other) : hashmap(other.hashmap), bucket_num(other.bucket_num), count(other.count), currentLoad(other.currentLoad), maxLoad(other.maxLoad) {}


    ~HashTable() {}


    HashTable& operator=(const HashTable& other) {

        if (this == &other) {
            return *this;
        }

        this->hashmap = other.hashmap;
        this->bucket_num = other.bucket_num;
        this->count = other.count;
        this->currentLoad = other.currentLoad;
        this->maxLoad = other.maxLoad;

        return *this;

    }


    HashTable(size_type buckets) : hashmap(buckets), bucket_num(buckets), count(0), currentLoad(0), maxLoad(1) {}
    

    bool is_empty() const {
        return count == 0;
    }


    size_t size() const {
        return count;
    }


    void make_empty() {
        hashmap.clear();
    }


    bool insert(const value_type& value) {
        
        // if contains return false
        if (contains(value)) {
            return false;
        }


        // if not already in hashmap
        size_t index = bucket(value);
        (hashmap[index]).push_back(value);
        count++;
        currentLoad = static_cast<float>(count) / bucket_num;

        return true;

    }


    size_t remove(const key_type& key);


    bool contains(const key_type& key) {

        // get the index of the list that the value is in
        size_t index = bucket(key);

        // get the linked list that contains the element
        std::list<value_type> list = hashmap[index];

        // Iterate through the linked list to find element
        for (value_type n : list) {
            if (n == key) {
                return true;
            }
        }

        // if it is not in the list
        return false;

    }

    
    size_t bucket_count() const {
        return bucket_num;
    }


    size_t bucket_size(size_t n) const {
        return (hashmap[n]).size();
    }

    
    size_t bucket(const key_type& key) const {
        return Hash{}(key) % hashmap.size();
    }


    float load_factor() const {
        return currentLoad;
    }


    float max_load_factor() const {
        return maxLoad;
    }


    void max_load_factor(float mlf) {
        maxLoad = mlf;
    }


    void rehash(size_type count);


    void print_table(std::ostream& os=std::cout) const;

    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};


#endif  // HASHTABLE_SEPARATE_CHAINING_H
