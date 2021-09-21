#pragma once

#include <stdint.h>

namespace glsl::vec {

    template <class T>
    struct vec2 {
        T x;
        T y;
    };

    template <class T>
    struct vec3 {
        T x;
        T y;
        T z;
    };

    template <class T>
    struct vec4 {
        T x;
        T y;
        T z;
        T w;
    };

    typedef vec2<bool> vec2b;
    typedef vec2<float> vec2f;
    typedef vec2<int32_t> vec2i;
    typedef vec2<uint32_t> vec2ui;

    typedef vec3<bool> vec3b;
    typedef vec3<float> vec3f;
    typedef vec3<int32_t> vec3i;
    typedef vec3<uint32_t> vec3ui;

    typedef vec4<bool> vec4b;
    typedef vec4<float> vec4f;
    typedef vec4<int32_t> vec4i;
    typedef vec4<uint32_t> vec4ui;

}