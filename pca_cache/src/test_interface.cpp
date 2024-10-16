#include "test_interface.hpp"
#include "pca_cache.hpp"

#include <fstream>
#include <sstream>

size_t CountPCACacheHitFromInput(std::istream& input)
{
    size_t cache_capacity = 0;
    if (!(input >> cache_capacity))
        throw std::invalid_argument("Invalid input for cache capacity.");

    size_t elems_count = 0;
    if(!(input >> elems_count))
        throw std::invalid_argument("Invalid input for elements count.");

    std::vector<size_t> values(10, FICT_ELEM_VALUE);
    std::vector<size_t> keys(elems_count);

    size_t elems_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        if(!(input >> elems_key))
            throw std::invalid_argument("Invalid input for elements key.");

        keys[i] = elems_key;
    }

    PCACache<int, int> PCACache(cache_capacity, keys.begin(), keys.end(), values.begin(), values.end());

    size_t cache_hit_count = PCACache.countCacheHit();

    return cache_hit_count;
}
