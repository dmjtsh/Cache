#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>

const int FICT_ELEM_VALUE = 0; // Fictitious value for testing

class PCACache {
public:
    PCACache(int capacity) : capacity_(capacity) {}

    size_t countCacheHit(int elems_number, int* elems);
private:
    int getFarthestElemKey(int elems_left, int* elems);
    void fillNextUseTable(int elems_number, int* elems);

    std::unordered_map<int, std::queue<int>> nextUseTable; // A table that shows in which indexes elem is used
    std::unordered_map<int, int> keyTable;
    int capacity_;
};
