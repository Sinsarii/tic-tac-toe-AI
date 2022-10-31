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

		Board();

		struct check_move;

		Player current_winner;

		vector<Player> playerList;

		vector<vector<string>> board;

		vector<Player> get_players(int number_players);

		vector<vector<string>> new_board();

		void print_board(vector<vector<string>>& board);

		void render(vector<vector<string>>& board);

		void reset();

		tuple<int, int> get_move(vector<vector<string>> board, string player_name, string player_symbol);

		tuple<int, int> human_player();

		string swap_player(string player);

		Player set_player(vector<Player> &player_list, Player current_player);

		vector<vector<string>> make_move(vector<vector<string>> board, tuple<int, int> player_move, string player);

		check_move is_valid_moveset(vector<vector<string>> board, tuple<int, int> move, string player);
		
		tuple<int, int> is_valid_move(vector<vector<string>> board, string player);

		bool check_win(vector<vector<string>> board, string current_player);

		bool check_draw(vector<vector<string>> board);

		bool check_endstate(vector<vector<string>> board, string player);

		void win_print(string player);

		vector<tuple<int, int>> get_legal_moves(vector<vector<string>> board);

		tuple<int, int> ai_random_move(vector<vector<string>> board, string player);

		tuple<int, int> find_winning_moves_ai(vector<vector<string>> board, string player);

		tuple<int, int> find_winning_then_blocking_moves_ai(vector<vector<string>> board, string player);

		int minmax_score(vector<vector<string>> board, string current_player, string opponent, string alternating_player);

		tuple<int, int> minmax(vector<vector<string>> board, string current_player);

		bool check_continue();

		void play();


};

