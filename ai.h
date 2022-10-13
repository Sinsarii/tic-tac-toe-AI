#include <tuple>
#include <vector>
#include <string>

#pragma once

using std::vector;
using std::string;
using std::tuple;

vector<tuple<int, int>> get_legal_moves(vector<vector<string>> board);

tuple<int, int> ai_random_move(vector<vector<string>> board,  string player);

tuple<int, int> find_winning_moves_ai(vector<vector<string>> board, string player);

tuple<int, int> find_winning_then_blocking_moves_ai(vector<vector<string>> board, string player);

int minmax_score(vector<vector<string>> board, string current_player, string opponent, string alternating_player);

tuple<int, int> minmax(vector<vector<string>> board, string current_player);



