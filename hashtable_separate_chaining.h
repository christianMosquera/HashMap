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
    size_t count;
    float currentLoad;
    float maxLoad;


    //---------------------------------------
    // Name: PrimeTest
    // PreCondition:  num is given
    // PostCondition: Returns true if num is prime
    //---------------------------------------
    bool PrimeTest(size_t num) const {

        if (num == 2 || num == 3) {
            return true;
        }

        if (num <= 1 || num % 2 == 0 || num % 3 == 0) {
            return false;
        }
            
        for (size_t i = 5; i * i <= num; i += 6) {

            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }

        }

        return true;
    }


    //---------------------------------------
    // Name: nextPrime
    // PreCondition:  num is given
    // PostCondition: Returns the next prime number after num
    //---------------------------------------
    size_t nextPrime(size_t num) {

        if (num == 1) {
            return 2;
        }

        size_t primeNum = num;
        bool prime = false;

        while (!prime) {
            primeNum++; 
            prime = PrimeTest(primeNum);
        }

        return primeNum;

    }
    
public:


    //---------------------------------------
    // Name: Default constructor
    //---------------------------------------
    HashTable() : hashmap(11), count(0), currentLoad(0), maxLoad(1) {}


    //---------------------------------------
    // Name: Copy constructor
    //---------------------------------------
    HashTable(const HashTable& other) : hashmap(other.hashmap), count(other.count), currentLoad(other.currentLoad), maxLoad(other.maxLoad) {}


    //---------------------------------------
    // Name: Destructor
    //---------------------------------------
    ~HashTable() {}


    //---------------------------------------
    // Name: Copy assignment
    // PreCondition:  other is given
    // PostCondition: A deep copied hashtable
    //---------------------------------------
    HashTable& operator=(const HashTable& other) {

        if (this == &other) {
            return *this;
        }

        this->hashmap = other.hashmap;
        this->count = other.count;
        this->currentLoad = other.currentLoad;
        this->maxLoad = other.maxLoad;

        return *this;

    }


    //---------------------------------------
    // Name: bucket parameter constructor
    // PreCondition:  buckets is given
    // PostCondition: A hashmap with number of buckets allocated
    //---------------------------------------
    HashTable(size_type buckets) : hashmap(buckets), count(0), currentLoad(0), maxLoad(1) {}
    

    //---------------------------------------
    // Name: is_empty
    // PreCondition:  hashtable exists
    // PostCondition: True if hashtable is empty
    //---------------------------------------
    bool is_empty() const {
        return count == 0;
    }


    //---------------------------------------
    // Name: size
    // PreCondition:  Hashtable exists
    // PostCondition: Number of elements in hashtable
    //---------------------------------------
    size_t size() const {
        return count;
    }


    //---------------------------------------
    // Name: make_empty
    // PreCondition:  Hashmap exists
    // PostCondition: Makes the hashmap empty
    //---------------------------------------
    void make_empty() {

        // clear vector and set count to 0
        for (auto& l : hashmap) {
            l.clear();
        }
        this->count = 0;
        this->currentLoad = 0;

    }


    //---------------------------------------
    // Name: insert
    // PreCondition:  value is given
    // PostCondition: Inserts the value into the hashmap
    //---------------------------------------
    bool insert(const value_type& value) {
        
        // if contains return false
        if (contains(value)) {
            return false;
        }

        // add value to hashmap
        size_t index = bucket(value);
        (hashmap[index]).push_front(value);
        
        // update count and load
        count++;
        currentLoad = static_cast<float>(count) / hashmap.size();

        // check to see if rehash is needed
        if (maxLoad < currentLoad) {
            
            // finds the next prime number, to use for new number of buckets
            size_t prime_num = nextPrime((hashmap.size() * 2));

            // rehash according to new bucket count
            rehash(prime_num);

            return true;
        }
        
        return true;

    }


    //---------------------------------------
    // Name: remove
    // PreCondition:  key is in hashmap
    // PostCondition: Removes the key from hashmap
    //---------------------------------------
    size_t remove(const key_type& key) {

        // check if in hashmap
        if (!contains(key)) {
            return 0;
        }

        // find key
        size_t index = bucket(key);

        // delete element
        (hashmap[index]).remove(key);

        // update load factor
        count--;
        currentLoad = static_cast<float>(count) / hashmap.size();

        return 1;
    }


    //---------------------------------------
    // Name: contains
    // PreCondition:  key is given
    // PostCondition: True if key is in hashmap
    //---------------------------------------
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


    //---------------------------------------
    // Name: bucket_count
    // PreCondition:  hashmap exists
    // PostCondition: Returns the size of the vector (buckets)
    //---------------------------------------
    size_t bucket_count() const {
        return hashmap.size();
    }


    //---------------------------------------
    // Name: bucket_size
    // PreCondition:  n is valid index of the hashmap
    // PostCondition: Returns number of elements inside bucket
    //---------------------------------------
    size_t bucket_size(size_t n) const {

        // throws if invalid index
        if (n >= hashmap.size() || n < 0) {
            throw std::out_of_range("Not in bounds.");
        }

        return (hashmap[n]).size();

    } 

    
    //---------------------------------------
    // Name: bucket
    // PreCondition:  key is given
    // PostCondition: Returns key index for the key value
    //---------------------------------------
    size_t bucket(const key_type& key) const {
        return Hash{}(key) % hashmap.size();
    }


    //---------------------------------------
    // Name: load_factor
    // PreCondition:  hashmap exists
    // PostCondition: Returns the current load of the hashmap
    //---------------------------------------
    float load_factor() const {
        return currentLoad;
    }


    //---------------------------------------
    // Name: max_load_factor
    // PreCondition:  hashmap exists
    // PostCondition: Returns the max load factor of the hashmap
    //---------------------------------------
    float max_load_factor() const {
        return maxLoad;
    }


    //---------------------------------------
    // Name: max_load_factor
    // PreCondition:  mlf is given
    // PostCondition: Sets the max load factorto mlf
    //---------------------------------------
    void max_load_factor(float mlf) {

        if (mlf <= 0) {
            throw std::invalid_argument("Invalid max load factor.");
        }

        maxLoad = mlf;

        // check if new load factor is satisfied
        if (maxLoad < currentLoad) {
            
            // find next prime number
            size_t prime_num = nextPrime((hashmap.size() * 2));

            // rehash
            rehash(prime_num);

        }

    }


    //---------------------------------------
    // Name: rehash
    // PreCondition:  count is given
    // PostCondition: Rehashes the hashmap and makes it bigger
    //---------------------------------------
    void rehash(size_type count) {

        // original size of hashmap
        size_t original = hashmap.size();

        // copy hashmap to rehash
        auto copy = hashmap;

        // resize the hashmap
        hashmap.resize(count);

        // rehash if not original size
        if (hashmap.size() != original) {

            // clear vector and set count to 0
            for (auto& l : hashmap) {
                l.clear();
            }
            this->count = 0;

            // iterate through hashmap and insert into the cleared hashmap
            for (auto l : copy) {

                for(value_type v : l) {

                    insert(v);

                }

            }

        }    

    }


    //---------------------------------------
    // Name: print_table
    // PreCondition:  hashmap exists
    // PostCondition: Prints out a nice representation of hashmap
    //---------------------------------------
    void print_table(std::ostream& os=std::cout) const {

        // empty hashmap
        if (this->count == 0) {
            os << "<empty>\n";
            return;
        }

        // index of vector
        int i = 0;

        // loop over the vector
        for (auto l : hashmap) {

            os << "[" << i << "] ";

            // loop over the lists in the vector
            for (value_type v : l) {

                os << v; 

                // print commas in between except for last element
                if (l.back() != v) {
                    os << ", ";
                }

            }

            os << std::endl;
            i++;
        }
    }

    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};


#endif  // HASHTABLE_SEPARATE_CHAINING_H
