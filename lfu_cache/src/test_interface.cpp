#include <fstream>
#include <sstream>

#include "lfu_cache.h"

size_t CountLFUCacheHitFromInput(std::istream& input)
{
    size_t cache_hit_count = 0;

    int cache_capacity = 0;
    input >> cache_capacity;

    LFUCache Cache(cache_capacity);

    int elems_count = 0;
    input >> elems_count;

    int elem_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        input >> elem_key;
        if (Cache.get(elem_key) != -1)
            cache_hit_count++;
        else
            Cache.put(elem_key, FICT_ELEM_VALUE);
    }

    return cache_hit_count;
}
