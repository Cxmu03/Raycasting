#include <ranges>
#include <string_view>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/Utilities.h"

void rotate(float theta, float& x, float& y, float pivotX /*= 0.f*/, float pivotY /*= 0.f*/) {
    float xPrime = (x - pivotX) * cosf(theta) - (y - pivotY) * sinf(theta) + 250;
    float yPrime = (x - pivotX) * sinf(theta) + (y - pivotY) * cosf(theta) + 250;
    x = xPrime;
    y = yPrime;
}

std::string ReadFile(const char* filename) {
    std::fstream stream(filename, std::fstream::in);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    std::string contents(buffer.str());
    return contents;
}

std::vector<std::string> SplitString(std::string str, const char delim) {
    auto result = str
        | std::ranges::views::split(delim)
        | std::ranges::views::transform([](auto&& str) { return std::string_view(&*str.begin(), std::ranges::distance(str)); });
    std::vector<std::string> out(result.begin(), result.end());
    return out;
}