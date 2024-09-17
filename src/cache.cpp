#include <unordered_map>
#include <list>

#include "cache.h"

void LFUCache::updateElementFrequency(auto node)
{
    int freq  = node->freq;
    int key   = node->key;
    int value = node->value;

    auto old_freq_list = freqTable[freq];
    old_freq_list.erase(node);

    // Old frequency list empty case
    if(old_freq_list.empty())
    {
        freqTable.erase(freq);
        
        if(min_freq_ == freq)
            min_freq_++;
    }

    int new_freq = freq + 1;

    // If there is no new frequency list
    if (freqTable.find(new_freq) == freqTable.end())
        freqTable.insert({new_freq, std::list<Node>()});

    auto new_freq_list = freqTable[new_freq];
    new_freq_list.push_back(Node(key, value, new_freq));

    return;
}

int LFUCache::get(int key)
{    
    if(keyTable.find(key) == keyTable.end())
        return -1;

    auto node = keyTable[key];
    int value = node->value;

    updateElementFrequency(node);    

    return value;
}

void LFUCache::put(int key, int value)
{
    // Add a new node or replace an old value of node if it exists
    if(keyTable.find(key) == keyTable.end())
    {
        auto first_freq_list = freqTable[1];
        first_freq_list.push_back(Node(key, value, 1));

        keyTable[key] = first_freq_list.end();
    }
    else
    {
        auto node = keyTable[key];
        updateElementFrequency(node);
        
        node->value = value;
    }

    if (keyTable.size() > capacity_)
    {
        auto least_freq_list = freqTable[min_freq_];
        
        least_freq_list.erase(least_freq_list.begin());
        keyTable.erase(key);
    }
}