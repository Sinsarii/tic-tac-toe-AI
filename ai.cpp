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
	check_move move_check;

	do
	{

	int x_coord = rand() % board.size();
	int y_coord = rand() % board[0].size();

	move = { x_coord, y_coord };

	move_check = is_valid_moveset(board, move, player);

	}while (move_check.valid_move == false);

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
			check_move move_check = is_valid_moveset(temp_board, { row, col }, player);

			if (move_check.valid_move)
			{
				temp_board = make_move(temp_board, { row, col }, player);
				if (check_win(temp_board, player))
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
			check_move move_check = is_valid_moveset(board, { row, col }, player);

			if (move_check.valid_move)
			{
				temp_board_win_move = make_move(board, { row, col }, player);
				temp_board_block_move = make_move(board, { row, col }, opponent);

				if (check_win(temp_board_win_move, player))
				{
					return { row, col };
				}
				else if(check_win(temp_board_block_move, opponent))
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

tuple<int, int> minmax(vector<vector<string>> board, string current_player)
{
	tuple<int, int> move;
	string opponent = swap_player(current_player);
	
	//call minmax_score to calculate the value of all available moves
	

	return move;
}

int minmax_score(vector<vector<string>> board, string current_player, string opponent, string alternating_player)
{
	//if there is a terminal state, end immediatly
	if (check_win(board, current_player))
	{
		return 10;
	}
	else if (check_win(board, opponent))
	{
		return -10;
	}
	else if (check_draw(board))
	{
		return 0;
	}

	//if board is not in a terminal state, get all possible moves
	tuple<int, int> move;
	vector<tuple<int, int>> possible_moves;


	return 0;
}

vector<tuple<int, int>> get_legal_moves(vector<vector<string>> board)
{

	vector<tuple<int, int>> possible_moves;

	for (int row = 0; row < board.size(); row++)
	{
		for (int column = 0; column < board[row].size(); column++)
		{
			if (board[row][column] == " ")
			{
				possible_moves.push_back({ row, column });
			}
		}
	}

	return possible_moves;
}