#pragma once

#include <fstream>

constexpr inline int FICT_ELEM_VALUE  = 1; // Fictitious value for testing

size_t CountPCACacheHitFromInput(std::istream& input);
