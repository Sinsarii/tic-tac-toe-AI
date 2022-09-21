#include "board.h"
#include <vector>
#include <iostream>
#include <string>
#include <tuple>

using std::vector;
using std::tuple;
using std::string;

tuple<int, int> ai_random_move(vector<vector<string>> board, string player)
{

	//random x coordinate
	tuple<int, int> move;
	tuple<bool, string> is_valid_ai_move;

	do
	{

	int x_coord = rand() % board.size();
	int y_coord = rand() % board[0].size();

	move = { x_coord, y_coord };

	is_valid_ai_move = is_valid_moveset(board, move, player);

	}while (get<0>(is_valid_ai_move) == false);

	return move;
}

tuple<int, int> find_winning_moves_ai(vector<vector<string>> board, string player)
{
	int x_coord, y_coord;

	tuple<int, int> move = { x_coord, y_coord };

	

	//make first available move (left -> right, up -> down)
	for (int row = 0; row < board.size(); row++)
	{
		for (int col = 0; col < board[row].size(); col++)
		{
			vector<vector<string>> temp_board = board;
			tuple<bool, string> movecheck = is_valid_moveset(temp_board, { row, col }, player);

			if (get<0>(movecheck))
			{
				temp_board = make_move(temp_board, { row, col }, player);
				if (check_win(temp_board))
				{
					return { row, col };
				}
			}


		}
	}


	return ai_random_move(board, player);
}

tuple<int, int> find_winning_then_blocking_moves_ai(vector<vector<string>> board, string player)
{

	tuple<int, int> move;
	tuple<int, int> blocking_move = { -1, -1 };
	string opponent = swap_player(player);



	//make first available move (left -> right, up -> down)
	for (int row = 0; row < board.size(); row++)
	{
		for (int col = 0; col < board[row].size(); col++)
		{
			vector<vector<string>> temp_board_win_move = board;
			vector<vector<string>> temp_board_block_move = board;
			tuple<bool, string> movecheck = is_valid_moveset(board, { row, col }, player);

			if (get<0>(movecheck))
			{
				temp_board_win_move = make_move(board, { row, col }, player);
				temp_board_block_move = make_move(board, { row, col }, opponent);

				if (check_win(temp_board_win_move))
				{
					return { row, col };
				}
				else if(check_win(temp_board_block_move))
				{
					blocking_move = { row, col };
				}

			}


		}
	}

	if (get<0>(blocking_move) != -1 && get<1>(blocking_move) != -1)
	{
		return blocking_move;
	}
	else
	{
		return ai_random_move(board, player);
	}

}