#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>

const int FICT_ELEM_VALUE = 0; // Fictitious value for testing

class PCACache {
public:
    PCACache(int capacity) : capacity_(capacity) {}

    size_t countCacheHit(int elems_number, int* elems);
private:
    int countFarthestElem(int elems_left, int* elems);

    std::unordered_map<int, int> keyTable;
    int capacity_;
};
