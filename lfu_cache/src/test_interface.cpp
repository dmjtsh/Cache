#include "lfu_cache.hpp"
#include "test_interface.hpp"

#include <fstream>

size_t CountLFUCacheHitFromInput(std::istream& input)
{
    size_t cache_hit_count = 0;

    size_t cache_capacity = 0;
    if(!(input >> cache_capacity))
        throw std::invalid_argument("Invalid input for cache capacity.");

    LFUCache<int, int> Cache(cache_capacity);

    size_t elems_count = 0;
    if(!(input >> elems_count))
        throw std::invalid_argument("Invalid input for elements count.");

    int elem_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        if(!(input >> elem_key))
            throw std::invalid_argument("Invalid input for elements key.");

        if (Cache.get(elem_key) != 0)
            cache_hit_count++;
        else
            Cache.put(elem_key, FICT_ELEM_VALUE);
    }

    return cache_hit_count;
}
