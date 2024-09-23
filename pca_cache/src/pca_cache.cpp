#include <unordered_map>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "pca_cache.h"

//
// PCACache block
//

void PCACache::fillNextUseTable(int elems_number, int* elems)
{
    assert(elems != nullptr);

    for (size_t i = 0; i < elems_number; i++)
    {
        if(nextUseTable.find(elems[i]) == nextUseTable.end())
            nextUseTable[elems[i]] = std::queue<int>();

        nextUseTable[elems[i]].push(i);
    }

}

int PCACache::getFarthestElemKey(int elems_left, int* elems)
{
    assert(elems != nullptr);

    int farthest_elem_key = -1;
    for(auto curr_iter = nextUseTable.begin(); curr_iter != nextUseTable.end(); curr_iter = std::next(curr_iter))
    {
        std::queue curr_queue = curr_iter->second;
        int        curr_key   = curr_iter->first;

        // if element will not appear in list
        if(curr_queue.empty())
            return curr_key;

        if(curr_queue.front() > farthest_elem_key)
            farthest_elem_key = curr_key;
    }

    return farthest_elem_key;
}

size_t PCACache::countCacheHit(int elems_number, int* elems)
{
    assert(elems != nullptr);

    fillNextUseTable(elems_number, elems);

    size_t cache_hit_count = 0;
    for (size_t i = 0; i < elems_number; i++)
    {
        int curr_elem_key = elems[i];

        // Used for keep nextUseTable in working state
        while(!nextUseTable[curr_elem_key].empty() && nextUseTable[curr_elem_key].front() <= i)
        {
            nextUseTable[curr_elem_key].pop();
        }

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
            keyTable.erase(getFarthestElemKey(elems_number, elems));

            keyTable[curr_elem_key] = FICT_ELEM_VALUE;
        }
    }

    return cache_hit_count;
}
