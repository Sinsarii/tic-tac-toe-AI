#include "ai.h"
#include <vector>
#include <iostream>
#include <string>
#include <tuple>

using std::vector;
using std::tuple;
using std::string;

tuple<int, int> random_ai(vector<vector<string>> board)
{

	//random x coordinate

	int x_coord = rand() % board.size();
	int y_coord = rand() % board[0].size();

	tuple<int, int> move = { x_coord, y_coord };

	return move;
}

tuple<int, int> find_winning_moves_ai(vector<vector<string>> board, int player)
{
	int x_coord, y_coord;

	tuple<int, int> move = { x_coord, y_coord };

	//make first available move (left -> right, up -> down)
	for (int row = 0; row < board.size(); row++)
	{
		for (int col = 0; col < board[row].size(); col++)
		{

		}
	}


	return move;
}

