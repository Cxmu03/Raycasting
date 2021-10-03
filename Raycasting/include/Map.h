#pragma once

#include <tuple>

#include <vector>

#include "../include/Size.h"

namespace Map {
    std::tuple<std::vector<std::vector<uint8_t>>, Size<size_t>> Read(const char* path);
};