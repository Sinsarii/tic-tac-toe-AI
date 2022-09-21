#include <tuple>
#include <vector>
#include <string>

#pragma once

using std::vector;
using std::string;
using std::tuple;

tuple<int, int> ai_random_move(vector<vector<string>> board,  string player);

tuple<int, int> find_winning_moves_ai(vector<vector<string>> board, string player);