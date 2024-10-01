#include <fstream>
#include <sstream>

#include "pca_cache.h"

size_t CountPCACacheHitFromInput(std::istream& input)
{
    int cache_capacity = 0;
    input >> cache_capacity;

    PCACache PCACache(cache_capacity);

    int elems_count = 0;
    input >> elems_count;

    std::vector<int> elems(elems_count);
    int elems_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        input >> elems_key;
        elems[i] = elems_key;
    }

    size_t cache_hit_count = PCACache.countCacheHit(elems);

    return cache_hit_count;
}
