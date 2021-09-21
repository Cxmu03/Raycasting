#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "../include/Map.h"
#include "../include/Utilities.h"

Map::Map(const char* path) {
    Read(path);
}

void Map::Read(const char* filename) {
    m_MapState.clear();
    std::string mapString = ReadFile(filename);
    std::string out;
    std::ranges::copy_if(mapString, std::back_inserter(out), [](char c) { return c != ' '; });
    mapString = out;
    auto lines = SplitString(mapString, '\n');
    m_MapSize.height = lines.size();
    m_MapSize.width = lines[0].size();
    for (const auto& line : lines) {
        for (const auto character : line) {
            if (isdigit(character)) {
                uint8_t value = character - '0';
                m_MapState.emplace_back(character);
            }
        }
    }
}

std::vector<int8_t> Map::operator[](size_t index) {
    auto startIterator = m_MapState.begin() + (index * m_MapSize.width);
    return {startIterator, startIterator + m_MapSize.width};
}