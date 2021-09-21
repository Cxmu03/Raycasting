#pragma once

#include <stdint.h>

template <typename T = uint32_t>
struct Size {
    T width;
    T height;
};