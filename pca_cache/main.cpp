#include <iostream>

#include "test_interface.hpp"

int main(int argc, char **argv)
{
    std::cout << CountPCACacheHitFromInput(std::cin) << std::endl;

    return 0;
}
