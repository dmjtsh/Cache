#pragma once

#include <cmath>
#include <unordered_map>
#include <list>

template<typename KeyT, typename ValueT>
struct Node
{
public:
    Node(const KeyT& key, const ValueT& value, size_t freq): key(key), value(value), freq(freq) {}

    KeyT key;
    ValueT value;

    size_t freq;
};

template<typename KeyT, typename ValueT>
class LFUCache {
public:
    LFUCache(size_t capacity) : capacity_(capacity), min_freq_(1) {}

    ValueT get(const KeyT& key)
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

    void put(const KeyT& key, const ValueT& value)
    {
        // Add a new node or replace an old value of node if it exists
        if(keyTable.find(key) == keyTable.end())
        {
            if (freqTable[1].empty())
            {
                freqTable[1] = std::list<Node<KeyT, ValueT>>();
                min_freq_ = 1;
            }

            std::list<Node<KeyT, ValueT>>& first_freq_list = freqTable[1];
            first_freq_list.emplace_front(Node<KeyT, ValueT>(key, value, 1));

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
    void deleteFrequencyList_(size_t freq)
    {
        freqTable.erase(freq);

        if(min_freq_ == freq)
            min_freq_++;

        return;
    }

    std::list<Node<KeyT, ValueT>>::iterator
    updateElementFrequency_(const std::list<Node<KeyT, ValueT>>::iterator& node)
    {
        size_t old_freq = node->freq;
        size_t new_freq = old_freq + 1;

        // If there is no new frequency list
        if (freqTable.find(new_freq) == freqTable.end())
            freqTable[new_freq] = std::list<Node<KeyT, ValueT>>();

        // Adding new elem in new list
        std::list<Node<KeyT, ValueT>>& new_freq_list = freqTable[new_freq];
        new_freq_list.emplace_front(Node(node->key, node->value, new_freq));
        keyTable[node->key] = new_freq_list.begin();

        std::list<Node<KeyT, ValueT>>& old_freq_list = freqTable[old_freq];
        old_freq_list.erase(node);

        // Old frequency list empty case
        if(old_freq_list.empty())
            deleteFrequencyList_(old_freq);

        typename std::list<Node<KeyT, ValueT>>::iterator new_node = new_freq_list.begin();

        return new_node;
    }

    std::unordered_map<size_t, std::list<Node<KeyT, ValueT>>> freqTable;
    std::unordered_map<KeyT, typename std::list<Node<KeyT, ValueT>>::iterator> keyTable;

    size_t min_freq_;
    size_t capacity_;
};
