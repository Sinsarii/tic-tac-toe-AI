#pragma once
#include "Player.h"
#include "winner.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>


using namespace std;


class Board
{

	public:
		struct check_move;

		Player current_winner;

		vector<Player> playerList;

		vector<Player> get_players(int number_players);

		vector<vector<string>> new_board();

		void print_board(vector<vector<string>>& board);

		void render(vector<vector<string>>& board);

		tuple<int, int> get_move(vector<vector<string>> board, string player_name, string player_symbol);

		tuple<int, int> human_player();

		string swap_player(string player);

		Player set_player(vector<Player> player_list, Player current_player);

		vector<vector<string>> make_move(vector<vector<string>> board, tuple<int, int> player_move, string player);

		check_move is_valid_moveset(vector<vector<string>> board, tuple<int, int> move, string player);

		
		tuple<int, int> is_valid_move(vector<vector<string>> board, string player);

		bool check_win(vector<vector<string>> board, string current_player);

		bool check_draw(vector<vector<string>> board);

		bool check_endstate(vector<vector<string>> board, string player);


		void win_print(string player);

		bool check_continue();

		void play();


};

