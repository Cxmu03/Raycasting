#pragma once

#include <ostream>
#include <stdint.h>

template <typename T = uint32_t>
struct Size {
    T width;
    T height;

    friend std::ostream& operator <<(std::ostream& out, Size size) {
        out << "{width: " << size.width << ", height: " << size.height << "}";
        return out;
    }
};