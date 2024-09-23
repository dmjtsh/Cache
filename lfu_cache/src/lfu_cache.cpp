#include <unordered_map>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "lfu_cache.h"

//
// LFUCache Block
//

void LFUCache::deleteFrequencyList_(int freq)
{
    freqTable.erase(freq);

    if(min_freq_ == freq)
        min_freq_++;

    return;
}

void LFUCache::updateElementFrequency_(std::list<Node>::iterator node)
{
    int freq  = node->freq;
    int key   = node->key;
    int value = node->value;

    std::list<Node>* old_freq_list = &freqTable[freq];
    old_freq_list->erase(node);

    // Old frequency list empty case
    if(old_freq_list->empty())
        deleteFrequencyList_(freq);

    int new_freq = freq + 1;

    // If there is no new frequency list
    if (freqTable.find(new_freq) == freqTable.end())
        freqTable.insert({new_freq, std::list<Node>()});

    std::list<Node>* new_freq_list = &freqTable[new_freq];
    new_freq_list->push_front(Node(key, value, new_freq));
    keyTable[key] = new_freq_list->begin();

    return;
}

int LFUCache::get(int key)
{
    if(keyTable.find(key) == keyTable.end())
        return -1;

    std::list<Node>::iterator node = keyTable[key];
    int value = node->value;

    updateElementFrequency_(node);

    return value;
}

void LFUCache::put(int key, int value)
{
    // Add a new node or replace an old value of node if it exists
    if(keyTable.find(key) == keyTable.end())
    {
        if (freqTable[1].empty())
        {
            freqTable.insert({1, std::list<Node>()});
            min_freq_ = 1;
        }

        std::list<Node>* first_freq_list = &freqTable[1];
        first_freq_list->push_front(Node(key, value, 1));

        keyTable[key] = first_freq_list->begin();
    }
    else
    {
        std::list<Node>::iterator node = keyTable[key];
        updateElementFrequency_(node);

        node->value = value;
    }

    // LRU deletion
    if (keyTable.size() > capacity_)
    {
        std::list<Node>* least_freq_list = &freqTable[min_freq_];
        std::list<Node>::iterator node_to_delete = std::prev(least_freq_list->end());
        int delete_node_freq = node_to_delete->freq;
        int delete_node_key  = node_to_delete->key;

        keyTable.erase(delete_node_key);

        least_freq_list->erase(node_to_delete);
        // Least frequency list empty case
        if(least_freq_list->empty())
            deleteFrequencyList_(delete_node_freq);
    }

    return;
}