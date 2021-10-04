#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>

#include "../include/Map.h"
#include "../include/Utilities.h"

namespace MapReader {
    std::tuple<Map, Size<size_t>> Read(const char* filename) {
        Map completeMap;
        Size<size_t> size;
        std::string mapString = ReadFile(filename);
        std::string out;
        std::ranges::copy_if(mapString, std::back_inserter(out), [](char c) { return c != ' '; });
        mapString = out;
        auto lines = SplitString(mapString, '\n');
        size.height = lines.size();
        size.width = lines[0].size();

        for (int i = 0; i < lines.size(); i++) {
            completeMap.emplace_back(std::vector<uint8_t>(size.width, 0));
            for (int j = 0; j < lines[i].size(); j++) {
                if (isdigit(lines[i][j])) {
                    uint8_t value = lines[i][j] - '0';
                    completeMap[i][j] = value;
                }
            }
        }
        return std::make_tuple(completeMap, size);
    }
};