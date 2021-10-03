#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <math.h>

#define STR(a) #a
#define MAP(v, r1, r2, e1, e2) (e1 + (((v - r1) / (r2 - r1)) * (e2 - e1)))
#define MAPC(c) MAP(c, 0.f, 255.f, 0.f, 1.f)
#define RGB2U(r, g, b) MAPC(r), MAPC(g), MAPC(b), 1.f
#define RGBA2U(r, g, b, a) MAPC(r), MAPC(g), MAPC(b), MAPC(a)
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(*arr))

constexpr float pi = 3.141592653f;
constexpr float two_pi = 2 * pi;
constexpr float pi_halves = pi / 2.f;

template <typename T>
inline T MapTo(T v, T r1, T r2, T e1, T e2) {
    return e1 + (((v - r1) / (r2 - r1)) * (e2 - e1));
}

template <typename T>
inline bool InRange(T v, T r1, T r2) {
    return v >= r1 && v <= r2;
}

template <typename T>
inline bool InRangeEx(T v, T r1, T r2) {
    return v > r1 && v < r2;
}

template <typename T>
inline bool HashsetContains(std::unordered_set<T> set, T val) {
    return set.find(val) != set.end();
}

void rotate(float theta, float& x, float& y, float pivotX = 0.f, float pivotY = 0.f);

std::string ReadFile(const char* filename);

std::vector<std::string> SplitString(std::string, const char delimiter);