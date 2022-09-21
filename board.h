#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using std::string;
using std::vector;
using std::cout;
using std::cin;

using namespace std;

vector<vector<string>> new_board();

void print_board(vector<vector<string>>& board);

void render(vector<vector<string>>& board);

tuple<int, int> get_move();

string swap_player(string player);

vector<vector<string>> make_move(vector<vector<string>> board, tuple<int, int> player_move, string player);

tuple<bool, string> is_valid_moveset(vector<vector<string>> board, tuple<int, int> move, string player);

/*DEPRECATED*/
//tuple<int, int> is_valid_move(vector<vector<string>> board, string player);

bool check_win(vector<vector<string>> board);

bool check_draw(vector<vector<string>> board);

void win_print(string player);

bool continue_game();