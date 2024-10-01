#include <iostream>

#include "test_interface.h"
#include "pca_cache.h"

int main(int argc, char **argv)
{
    std::cout << CountPCACacheHitFromInput(std::cin) << std::endl;

    return 0;
}
