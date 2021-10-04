#pragma once

#include <tuple>

#include <vector>

#include "../include/Size.h"

using Map = std::vector<std::vector<uint8_t>>;

namespace MapReader {
    std::tuple<Map, Size<size_t>> Read(const char* path);
};