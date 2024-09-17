#include <unordered_map>
#include <list>

struct Node {
public:
    Node(int key, int value, int freq): key(key), value(value), freq(freq) {}

    int key;
    int value;
    int freq;
};

class LFUCache {
public:
    LFUCache(int capacity) : capacity_(capacity), min_freq_(0) {}

    int  get(int key);
    void put(int key, int value);

private:
    void updateElementFrequency(auto node);
    
    std::unordered_map<int, std::list<Node>> freqTable;
    std::unordered_map<int, std::list<Node>::iterator> keyTable; 

    int min_freq_;
    int capacity_;
};

