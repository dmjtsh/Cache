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
