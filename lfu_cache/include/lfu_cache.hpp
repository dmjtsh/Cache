#pragma once

#include <unordered_map>
#include <list>

template<typename KeyT, typename ValueT>
struct Node
{
public:
    Node(KeyT key, ValueT value, int freq): key(key), value(value), freq(freq) {}

    KeyT key;
    ValueT value;

    int freq;
};

template<typename KeyT, typename ValueT>
class LFUCache {
public:
    LFUCache(int capacity) : capacity_(capacity), min_freq_(1) {}

    ValueT get(KeyT key)
    {
        ValueT value {};

        // Return an empty value if elem wasn't found
        if(keyTable.find(key) == keyTable.end())
            return value;

        typename std::list<Node<KeyT, ValueT>>::iterator node = keyTable[key];
        value = node->value;

        updateElementFrequency_(node);

        return value;
    }

    void put(KeyT key, ValueT value)
    {
        // Add a new node or replace an old value of node if it exists
        if(keyTable.find(key) == keyTable.end())
        {
            if (freqTable[1].empty())
            {
                freqTable.insert({1, std::list<Node<KeyT, ValueT>>()});
                min_freq_ = 1;
            }

            std::list<Node<KeyT, ValueT>>& first_freq_list = freqTable[1];
            first_freq_list.push_front(Node<KeyT, ValueT>(key, value, 1));

            keyTable[key] = first_freq_list.begin();
        }
        else
        {
            typename std::list<Node<KeyT, ValueT>>::iterator node = keyTable[key];
            updateElementFrequency_(node);

            node->value = value;
        }

        // LRU deletion
        if (keyTable.size() > capacity_)
        {
            std::list<Node<KeyT, ValueT>>& least_freq_list = freqTable[min_freq_];
            typename std::list<Node<KeyT, ValueT>>::iterator node_to_delete = std::prev(least_freq_list.end());

            keyTable.erase(node_to_delete->key);

            least_freq_list.erase(node_to_delete);

            // Least frequency list empty case
            if(least_freq_list.empty())
                deleteFrequencyList_(node_to_delete->freq);
        }

        return;
    }

private:
    void deleteFrequencyList_(int freq)
    {
        freqTable.erase(freq);

        if(min_freq_ == freq)
            min_freq_++;

        return;
    }

    void updateElementFrequency_(std::list<Node<KeyT, ValueT>>::iterator node)
    {
        int old_freq = node->freq;
        int new_freq = old_freq + 1;

        // If there is no new frequency list
        if (freqTable.find(new_freq) == freqTable.end())
            freqTable.insert({new_freq, std::list<Node<KeyT, ValueT>>()});

        // Adding new elem in new list
        std::list<Node<KeyT, ValueT>>& new_freq_list = freqTable[new_freq];
        new_freq_list.push_front(Node(node->key, node->value, new_freq));
        keyTable[node->key] = new_freq_list.begin();

        std::list<Node<KeyT, ValueT>>& old_freq_list = freqTable[old_freq];
        old_freq_list.erase(node);

        // Old frequency list empty case
        if(old_freq_list.empty())
            deleteFrequencyList_(old_freq);

        return;
    }

    std::unordered_map<int, std::list<Node<KeyT, ValueT>>> freqTable;
    std::unordered_map<KeyT, typename std::list<Node<KeyT, ValueT>>::iterator> keyTable;

    int min_freq_;
    int capacity_;
};
