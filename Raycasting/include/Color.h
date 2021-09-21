#pragma once

#include <stdint.h>

#include "Utilities.h"

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    void operator /=(uint8_t divisor);

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Magenta;
    static const Color Black;
    static const Color White;
};

struct HsvColor {
    double h;
    double s;
    double v;
};