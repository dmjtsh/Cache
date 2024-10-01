#include <unordered_map>
#include <list>
#include <iostream>
#include <assert.h>

#include "pca_cache.h"

//
// PCACache block
//

void PCACache::fillNextUseTable(std::vector<int> elems)
{
    for (size_t i = 0; i < elems.size(); i++)
    {
        if(nextUseTable.find(elems[i]) == nextUseTable.end())
            nextUseTable[elems[i]] = std::queue<int>();

        nextUseTable[elems[i]].push(i);
    }

}

// Returns key of the farthest element comparing it with new elem that we can put in cache
int PCACache::getFarthestElemKey(int new_elem_key)
{
    int farthest_elem_key   = -1;
    int farthest_elem_index = -1;
    for(auto curr_iter = keyTable.begin(); curr_iter != keyTable.end(); curr_iter++)
    {
        std::queue curr_queue = nextUseTable[curr_iter->first];
        int        curr_key   = curr_iter->first;

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

size_t PCACache::countCacheHit(std::vector<int> elems)
{
    fillNextUseTable(elems);

    size_t cache_hit_count = 0;

    for (size_t i = 0; i < elems.size(); i++)
    {
        int curr_elem_key = elems[i];

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
            keyTable[curr_elem_key] = FICT_ELEM_VALUE;
        else
        {
            int elem_to_replace_key = getFarthestElemKey(curr_elem_key);
            if(elem_to_replace_key == curr_elem_key)
                continue;

            keyTable.erase(elem_to_replace_key);

            keyTable[curr_elem_key] = FICT_ELEM_VALUE;
        }
    }

    return cache_hit_count;
}

