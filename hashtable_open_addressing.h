#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <functional>
#include <iostream>
#include <vector>

/*****************************************************
 **
 ** File:    hashtable_open_addressing.h
 ** Project: CSCE 221 Lab 6 Spring 2022
 ** Author:  Christian Mosquera
 ** Date:    04/11/22
 ** Section: 510
 ** Email:   cwbo.1701@tamu.edu
 ** 
 ** This file contains function definitions to the HashTable data
 ** structure that uses open addressing as a collision protocol.
 **
 *****************************************************/

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

    struct Value {
        value_type value;
        int status;
        Value() : value(), status(EMPTY) {}
    };

    std::vector<Value> hashmap;
    int count;
    float currentLoad;
    float maxLoad;

    enum Status {FULL, EMPTY, ACTIVE};


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
            
        for (int i = 5; i * i <= num; i += 6) {

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
            make_empty();
            // this->count = 0;

            // iterate through hashmap and insert into the cleared hashmap
            
            for (Value v : copy) {
                if (v.status == FULL) {
                    insert(v.value);
                }
            }

        }    

    }
    

public:
    

    //---------------------------------------
    // Name: Default constructor
    // PreCondition:  Hashmap is provided
    // PostCondition: Returns hashmap
    //---------------------------------------
    HashTable() : hashmap(11), count (0), currentLoad(0), maxLoad(0.5) {}


    //---------------------------------------
    // Name: Copy constructor
    // PreCondition:  Hashmap is provided
    // PostCondition: Returns deep copied Hashmap
    //---------------------------------------
    HashTable(const HashTable& other) : hashmap(other.hashmap), count(other.count), currentLoad(other.currentLoad), maxLoad(other.maxLoad) {}


    //---------------------------------------
    // Name: destructor
    // PreCondition:  Hashmap is provided
    // PostCondition: Destructs the hashmap
    //---------------------------------------
    ~HashTable() {}


    //---------------------------------------
    // Name: operator=
    // PreCondition:  Hashmap is provided
    // PostCondition: Returns new hashtable
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
    // Name: Parameter constructor
    // PostCondition: Produces hashmap with cells as buckets
    //---------------------------------------
    HashTable(size_type cells) : hashmap(cells), count(0), currentLoad(0), maxLoad(0.5) {}


    //---------------------------------------
    // Name: is_empty
    // PreCondition:  Hashmap is provided
    // PostCondition: Returns boolean indicating whether hashmap is empty
    //---------------------------------------
    bool is_empty() const {
        return count == 0;
    }


    //---------------------------------------
    // Name: size
    // PreCondition:  Hashmap is provided
    // PostCondition: Returns the count of all the values
    //---------------------------------------
    size_t size() const {
        return count;
    }

    
    //---------------------------------------
    // Name: table_size
    // PreCondition:  Hashmap is provided
    // PostCondition: Returns the size of the internal list
    //---------------------------------------
    size_t table_size() const {
        return hashmap.size();
    }


    //---------------------------------------
    // Name: make_empty
    // PreCondition:  hashmap is provided
    // PostCondition: Returns an empty hashmap
    //---------------------------------------
    void make_empty() {
        for (Value& v : hashmap) {
            v.status = EMPTY;
        }
        count = 0;
    }


    //---------------------------------------
    // Name: insert
    // PreCondition:  value is provided
    // PostCondition: Inserts the value into the hashmap
    //---------------------------------------
    bool insert(const value_type& value) {

        // if contains return false
        if (contains(value)) {
            return false;
        }

        // get hash function
        size_t index = position(value);
        
        // update the key
        (hashmap[index]).value = value;
        (hashmap[index]).status = FULL;

        // update count and load factor
        count++;
        currentLoad = static_cast<float>(count) / hashmap.size();

        // check to see if load factor is below .5
        if (currentLoad > maxLoad) {

            // find next prime
            size_t prime_num = nextPrime((hashmap.size() * 2));

            // rehash using new size
            rehash(prime_num);

        }

        return true;

    }


    //---------------------------------------
    // Name: remove
    // PreCondition: key is given 
    // PostCondition: Removes the key from the hashmap
    //---------------------------------------
    size_t remove(const key_type& key) {

        // check if in index
        if (!contains(key)) {
            return 0;
        }

        // find index
        size_t index = position(key);

        // update count and load factor
        count--;
        currentLoad = static_cast<float>(count) / hashmap.size();

        // delete element
        (hashmap[index]).status = ACTIVE;
        return 1;
    }


    //---------------------------------------
    // Name: contains
    // PreCondition:  key is given
    // PostCondition: Returns boolean of if it contains key
    //---------------------------------------
    bool contains(const key_type& key) {
        
        // get hash function
        size_t index = position(key);

        // go to location
        if (key == (hashmap[index]).value && (hashmap[index]).status == FULL) {
            return true;
        }

        // item not found
        return false;

    }


    //---------------------------------------
    // Name: position
    // PreCondition:  key is provided
    // PostCondition: Returns position of the next index or index of found value
    //---------------------------------------
    size_t position(const key_type& key) const {

        // initial index
        size_t index =  Hash{}(key) % hashmap.size();

        // return if empty or found a matching key
        if ((hashmap[index]).status == EMPTY || ((hashmap[index]).value == key && (hashmap[index]).status != EMPTY)) {
            return index;
        }

        // loop to find next available index or to find the key
        int i = 1;
        while ((hashmap[index]).status != EMPTY) {
            index = (index + (i*i)) % hashmap.size();
            if ((hashmap[index]).status == EMPTY || ( (hashmap[index]).value == key && (hashmap[index]).status != EMPTY) ) {
                return index;
            }
            i++;
        }

        return index;

    }


    //---------------------------------------
    // Name: print_table
    // PreCondition:  hashmap is given
    // PostCondition: Returns printed list
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
        for (Value v : hashmap) {
            os << "[" << i << "] ";
            if (v.status == FULL) {
                os << v.value;
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


#endif  // HASHTABLE_OPEN_ADDRESSING_H