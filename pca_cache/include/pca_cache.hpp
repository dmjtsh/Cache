#pragma once

#include <unordered_map>
#include <queue>
#include <vector>

template <typename KeyT, typename ValueT>
class PCACache {
public:
    template <typename Iter>
    PCACache(size_t capacity, const Iter& keys_begin, const Iter& keys_end, const Iter& values_begin, const Iter& values_end)
    {
        capacity_ = capacity;

        for (Iter it = keys_begin; it != keys_end; ++it) {
            keys_.push_back(*it);
        }

        for (Iter it = values_begin; it != values_end; ++it) {
            values_.push_back(*it);
        }
    }

    size_t countCacheHit()
    {
        fillNextUseTable();

        size_t cache_hit_count = 0;

        for (size_t i = 0; i < keys_.size(); i++)
        {
            KeyT curr_elem_key = keys_[i];

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
                keyTable[curr_elem_key] = values_[i];
            else
            {
                int elem_to_replace_key = getFarthestElemKey(curr_elem_key);
                if(elem_to_replace_key == curr_elem_key)
                    continue;

                keyTable.erase(elem_to_replace_key);

                keyTable[curr_elem_key] = values_[i];
            }
        }

        return cache_hit_count;
    }

private:
    KeyT getFarthestElemKey(const KeyT& new_elem_key)
    {
        KeyT farthest_elem_key {};
        size_t farthest_elem_index = 0;

        for(auto curr_iter = keyTable.begin(); curr_iter != keyTable.end(); curr_iter++)
        {
            std::queue<size_t>& curr_queue = nextUseTable[curr_iter->first];
            const KeyT& curr_key = curr_iter->first;

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
        std::queue<size_t>& new_elem_queue = nextUseTable[new_elem_key];

        if(new_elem_queue.empty() || new_elem_queue.front() > farthest_elem_index)
            return new_elem_key;

        return farthest_elem_key;
    }

    void fillNextUseTable()
    {
        for (size_t i = 0; i < keys_.size(); i++)
            nextUseTable[keys_[i]].emplace(i);
    }

    std::unordered_map<KeyT, std::queue<size_t>> nextUseTable; // A table that shows in which indexes elem is used
    std::unordered_map<KeyT, ValueT> keyTable;

    std::vector<KeyT> keys_;
    std::vector<ValueT> values_;

    size_t capacity_;
};
