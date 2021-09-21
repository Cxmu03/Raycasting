#pragma once

#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <unordered_set>

#include "../include/Utilities.h"

class MazeGenerator {
public:
    template <size_t width, size_t height>
    static std::vector<std::vector<int>> Automata() {
        std::vector<std::vector<int>> board(height, std::vector<int>(width, 0));
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                board[y][x] = rand() % 2;
            }
        }
        for (int i = 0; i < 3000; i++) {
            if (i % 500 == 0) {
                std::cout << i << std::endl;
            }
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int neighbours = CountNeighbors(board, y, x);
                    if (board[y][x] == 0 && HashsetContains(s_BirthConditions, (uint8_t)neighbours)) {
                        board[y][x] = 1;
                    }
                    else if (board[y][x] == 1 && !HashsetContains(s_SurvivalConditions, (uint8_t)neighbours)) {
                        board[y][x] = 0;
                    }
                }
            }
        }
        return board;
    }

private:
    static int CountNeighbors(std::vector<std::vector<int>> board, int x, int y) {
        int neighbours = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newX = x + j;
                int newY = y + i;
                if ((i || j) && InRange(newX, 0, (int)board.size() - 1) && InRange(newY, 0, (int)board[0].size() - 1) && board[newY][newX]) {
                    neighbours++;
                }
            }
        }
        return neighbours;
    }

public:
    static std::unordered_set<uint8_t> s_SurvivalConditions;
    static std::unordered_set<uint8_t> s_BirthConditions;
};