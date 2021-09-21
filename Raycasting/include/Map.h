#pragma once

#include <vector>

#include "../include/Size.h"

class Map {
public:
    Map() = default;
    Map(const char* path);
public:
    void Read(const char* path);
    std::vector<int8_t> operator [](size_t index);
private:
    Size<uint8_t> m_MapSize;
    std::vector<int8_t> m_MapState;
};