#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>

const int FICT_ELEM_VALUE = 0; // Fictitious value for testing

struct Node {
public:
    Node(int key, int value, int freq): key(key), value(value), freq(freq) {}

    int key;
    int value;
    int freq;
};

class LFUCache {
public:
    LFUCache(int capacity) : capacity_(capacity), min_freq_(1) {}

    int  get(int key);
    void put(int key, int value);

private:
    void deleteFrequencyList_(int freq);
    void updateElementFrequency_(std::list<Node>::iterator node);
    
    std::unordered_map<int, std::list<Node>> freqTable;
    std::unordered_map<int, std::list<Node>::iterator> keyTable; 

    int min_freq_;
    int capacity_;
};

class PCACache {
public:
    PCACache(int capacity) : capacity_(capacity) {}
    
    size_t countCacheHit(int elems_number, int* elems);
private:
    int countFarthestElem(int elems_left, int* elems);

    std::unordered_map<int, int> keyTable;
    int capacity_;
};
