#include "../include/MazeGenerator.h"

std::unordered_set<uint8_t> MazeGenerator::s_SurvivalConditions = {  1, 2, 3, 4, 5 };
std::unordered_set<uint8_t> MazeGenerator::s_BirthConditions = {3};