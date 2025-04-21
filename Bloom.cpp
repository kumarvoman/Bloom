#pragma once
// Bloom.cpp
#include <iostream>
#include <vector>
#include <functional> // Ensure this header is included for std::function
#include <bitset>

class BloomFilter {
private:
    // Private members
    std::vector<bool> bitArray; // Bit array
    size_t size; // Size of the bit array
    size_t numElementsAdded = 0; // number of elements added so far
    size_t maxNumElements = 0; // Maximum number of elements that can be added
    double loadFactor = 0.0; // Load factor
    double falsePositiveRate = 0.0; // False positive rate
    size_t numBitsSet = 0; // Number of bits set to true
    std::vector<std::function<size_t(const std::string&)>> hashFunctions; // Hash functions

public:
    // Constructor
    BloomFilter(size_t size, std::vector<std::function<size_t(const std::string&)>> hashFunctions)
        : size(size), hashFunctions(hashFunctions) {
        bitArray.resize(size, false);
    }

    // Add an element to the Bloom Filter
    void add(const std::string& element) {
        for (const auto& hashFunction : hashFunctions) {
            size_t hashValue = hashFunction(element) % size;
            bitArray[hashValue] = true;
        }
    }

    // Check if an element might be in the Bloom Filter
    bool contains(const std::string& element) const {
        for (const auto& hashFunction : hashFunctions) {
            size_t hashValue = hashFunction(element) % size;
            if (!bitArray[hashValue]) {
                return false; // Definitely not in the set
            }
        }
        return true; // Might be in the set
    }

    // Clear the Bloom Filter
    void clear() {
        std::fill(bitArray.begin(), bitArray.end(), false);
    }
    // Get the size of the Bloom Filter
    size_t getSize() const {
        return size;
    }
    // Get the number of hash functions
    size_t getNumHashFunctions() const {
        return hashFunctions.size();
    }
    // Get the bit array
    const std::vector<bool>& getBitArray() const {
        return bitArray;
    }
    // Get the hash functions
    const std::vector<std::function<size_t(const std::string&)>>& getHashFunctions() const {
        return hashFunctions;
    }
    // Get the number of bits set to true
    size_t getNumBitsSet() const {
        return std::count(bitArray.begin(), bitArray.end(), true);
    }
    // Get the false positive rate
    double getFalsePositiveRate() const {
        double numBitsSet = static_cast<double>(getNumBitsSet());
        double numHashFunctions = static_cast<double>(getNumHashFunctions());
        return std::pow(1 - std::exp(-numHashFunctions / size), numHashFunctions);
    }
     // Get the number of elements added
     size_t getNumElementsAdded() const {
         return numElementsAdded;
     }
     // Get the maximum number of elements that can be added
     size_t getMaxNumElements() const {
         return maxNumElements;
     }
     // Get the load factor
     double getLoadFactor() const {
         return static_cast<double>(getNumElementsAdded()) / getMaxNumElements();
     }
};

 int bloomRn() {
     // Define hash functions
     auto hash1 = [](const std::string& key) {
         std::hash<std::string> hashFn;
         return hashFn(key);
     };
     auto hash2 = [](const std::string& key) {
         std::hash<std::string> hashFn;
         return hashFn(key + "salt1");
     };
     auto hash3 = [](const std::string& key) {
         std::hash<std::string> hashFn;
         return hashFn(key + "salt2");
     };
     // Create a Bloom Filter with 1000 bits and 3 hash functions
     BloomFilter bloomFilter(1000, {hash1, hash2, hash3});
     // Add elements to the Bloom Filter
     bloomFilter.add("apple");
     bloomFilter.add("banana");
     bloomFilter.add("cherry");
     // Check for elements
     std::cout << "Contains 'apple': " << bloomFilter.contains("apple") << std::endl; // True
     std::cout << "Contains 'banana': " << bloomFilter.contains("banana") << std::endl; // True
     std::cout << "Contains 'grape': " << bloomFilter.contains("grape") << std::endl; // False (probably)
     std::cout << "Contains 'cherry': " << bloomFilter.contains("cherry") << std::endl; // True
     std::cout << "Contains 'orange': " << bloomFilter.contains("orange") << std::endl; // False (probably)
     return 0;
 }
 //Bloom Filter  
