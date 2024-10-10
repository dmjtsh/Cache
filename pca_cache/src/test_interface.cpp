#include <fstream>
#include <sstream>

#include "test_interface.hpp"
#include "pca_cache.hpp"

size_t CountPCACacheHitFromInput(std::istream& input)
{
    int cache_capacity = 0;
    input >> cache_capacity;

    PCACache<int, int> PCACache(cache_capacity);

    int elems_count = 0;
    input >> elems_count;

    std::vector<int> values(10, FICT_ELEM_VALUE);
    std::vector<int> keys(elems_count);

    int elems_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        input >> elems_key;
        keys[i] = elems_key;
    }

    size_t cache_hit_count = PCACache.countCacheHit(keys, values);

    return cache_hit_count;
}
