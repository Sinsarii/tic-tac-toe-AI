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

struct check_move
{
	bool valid_move;
	string error_message;
}typedef check_move;

struct Player {
	string player_name;
	string player_symbol;
};

struct winner
{
	string player_name;
	int number_of_wins;
};

vector<vector<string>> new_board();

void print_board(vector<vector<string>>& board);

void render(vector<vector<string>>& board);

tuple<int, int> get_move(vector<vector<string>> board, string player_name, string player_symbol);

tuple<int, int> human_player();

string swap_player(string player);

Player set_player(vector<Player> player_list, Player current_player);

vector<vector<string>> make_move(vector<vector<string>> board, tuple<int, int> player_move, string player);

check_move is_valid_moveset(vector<vector<string>> board, tuple<int, int> move, string player);

/*DEPRECATED*/
//tuple<int, int> is_valid_move(vector<vector<string>> board, string player);

bool check_win(vector<vector<string>> board);

bool check_draw(vector<vector<string>> board);

bool check_endstate(vector<vector<string>> board, string player);


void win_print(string player);

bool check_continue();

vector<winner> archive_wins(vector<winner> game_record, Player current_winner);