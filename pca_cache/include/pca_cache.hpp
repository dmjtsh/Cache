#pragma once

#include <unordered_map>
#include <queue>
#include <vector>

template <typename KeyT, typename ValueT>
class PCACache {
public:
    PCACache(int capacity) : capacity_(capacity) {}

    size_t countCacheHit(std::vector<KeyT> keys, std::vector<ValueT> values)
    {
        fillNextUseTable(keys);

        size_t cache_hit_count = 0;

        for (size_t i = 0; i < keys.size(); i++)
        {
            KeyT curr_elem_key = keys[i];

            // Used for keep nextUseTable in working state
            if(!nextUseTable[curr_elem_key].empty())
                nextUseTable[curr_elem_key].pop();

            if(keyTable.find(curr_elem_key) != keyTable.end())
            {
                cache_hit_count++;
                continue;
            }

            // If cache is not full than fill it
            if(keyTable.size() < capacity_)
                keyTable[curr_elem_key] = values[i];
            else
            {
                int elem_to_replace_key = getFarthestElemKey(curr_elem_key);
                if(elem_to_replace_key == curr_elem_key)
                    continue;

                keyTable.erase(elem_to_replace_key);

                keyTable[curr_elem_key] = values[i];
            }
        }

        return cache_hit_count;
    }

private:
    KeyT getFarthestElemKey(KeyT new_elem_key)
    {
        KeyT farthest_elem_key {};
        size_t farthest_elem_index = 0;

        for(auto curr_iter = keyTable.begin(); curr_iter != keyTable.end(); curr_iter++)
        {
            std::queue curr_queue = nextUseTable[curr_iter->first];
            KeyT       curr_key   = curr_iter->first;

            // if element will not appear in list
            if(curr_queue.empty())
                return curr_key;

            if(curr_queue.front() > farthest_elem_index)
            {
                farthest_elem_index = curr_queue.front();
                farthest_elem_key   = curr_key;
            }
        }

        // Comparing it with new elem that we can put in cache
        std::queue new_elem_queue = nextUseTable[new_elem_key];

        if(new_elem_queue.empty() || new_elem_queue.front() > farthest_elem_index)
            return new_elem_key;

        return farthest_elem_key;
    }

    void fillNextUseTable(std::vector<KeyT> keys)
    {
        for (size_t i = 0; i < keys.size(); i++)
        {
            if(nextUseTable.find(keys[i]) == nextUseTable.end())
                nextUseTable[keys[i]] = std::queue<size_t>();

            nextUseTable[keys[i]].push(i);
        }
    }

    std::unordered_map<KeyT, std::queue<size_t>> nextUseTable; // A table that shows in which indexes elem is used
    std::unordered_map<KeyT, ValueT> keyTable;

    int capacity_;
};
