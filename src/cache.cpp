#include <unordered_map>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "cache.h"

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

//
// PCACache block
//

int PCACache::countFarthestElem(int elems_left, int* elems)
{
    assert(elems != nullptr);

    int farthest_elem_key  = 0;
    int farthest_distance  = 0;
    int curr_elem_key      = 0;
    int curr_elem_distance = 0;

    for (size_t i = 0; i < capacity_; i++)
    {
        curr_elem_key = std::next(keyTable.begin(), i)->first;
        curr_elem_distance = -1;

        for (size_t j = 0; j < elems_left; j++)
        {
            if(curr_elem_key == *(elems+j))
            {
                curr_elem_distance = j;
                
                if(curr_elem_distance > farthest_distance)
                {
                    farthest_distance = curr_elem_distance;
                    farthest_elem_key = curr_elem_key;
                }
                    
                break;                
            }
        }
        
        // Elem is not in list case
        if (curr_elem_distance == -1) 
        {
            farthest_elem_key = curr_elem_key;
            break;
        }
    }

    return farthest_elem_key;
}

size_t PCACache::countCacheHit(int elems_number, int* elems)
{
    assert(elems != nullptr);

    size_t cache_hit_count = 0;

    for (size_t i = 0; i < elems_number; i++)
    {
        int curr_elem_key = *(elems+i);

        if(keyTable.find(curr_elem_key) != keyTable.end())
        {
            cache_hit_count++;
            continue;
        }

        // If cache is not full than fill it
        if(keyTable.size() < capacity_)
            keyTable[curr_elem_key] = FICT_ELEM_VALUE;
        else
        {
            // Replace most Farthest Elem
            int elem_to_replace_key =  countFarthestElem(elems_number-i, elems+i);
            keyTable.erase(elem_to_replace_key);
            
            keyTable[curr_elem_key] = FICT_ELEM_VALUE;
        }
    }

    return cache_hit_count;
}