#include <unordered_map>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

const int FICT_ELEM_VALUE = 0; // Fictitious value for testing

class PCACache {
public:
    PCACache(int capacity) : capacity_(capacity) {}

    size_t countCacheHit(std::vector<int> elems);
private:
    int  getFarthestElemKey(int new_elem_key);
    void fillNextUseTable(std::vector<int> elems);

    std::unordered_map<int, std::queue<int>> nextUseTable; // A table that shows in which indexes elem is used
    std::unordered_map<int, int> keyTable;
    int capacity_;
};
