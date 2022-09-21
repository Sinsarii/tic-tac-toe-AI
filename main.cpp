#include <iostream>
#include "ai.h"
#include "board.h"
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <tuple>

using std::string;
using std::vector;
using std::cout;
using std::cin;

using namespace std;

void run_game()
{
	vector<vector<string>> board = new_board();

	render(board);

	string player = "X";

	bool winner;
	bool draw;
	bool continue_bool = true;

	tuple<int, int> player_move;
	tuple<bool, string> check_move;

	while(continue_bool)
	{

		do
		{
			player_move = get_move();
			//player_move = random_ai(board);
			check_move = is_valid_moveset(board, player_move, player);
			if (get<0>(check_move) == false)
			{
				cout << get<1>(check_move) << endl;
			}

		} while (get<0>(check_move) == false);


		board = make_move(board, player_move, player);

		render(board);


		winner = check_win(board);

		draw = check_draw(board);

		if (winner)
		{
			win_print(player);
			continue_bool = continue_game();
			if (continue_bool == true)
			{
				board = new_board();
				render(board);

			}
		}
		else if (draw && winner == false)
		{
			cout << "Game is a draw" << endl;
			continue_bool = continue_game();
			if (continue_bool == true)
			{
				board = new_board();
				render(board);

			}
		}
		player = swap_player(player);


	}



	cout << "Thanks for playing!" << endl;


	//loop until there is a winner or the board is full
	//	print the board
	//	
	//	get move from player
	// 
	//	check if the move is legal
	// 
	//	make the move on the board
	// 
	//	check if move is winning
	//		if it is winner, declare winner and break out of loop
	//		if the board is full and no winner, declare a draw
	// 
	// 
}

void test_board()
{
	vector<vector<string>> test_board =
	{
		{"X"," "," "},
		{" ","X"," "},
		{"X"," ","O"}

	};

	render(test_board);

	tuple<int,int> ai_winning_move = find_winning_moves_ai(test_board, "O");

	test_board = make_move(test_board, ai_winning_move, "O");

	render(test_board);

	bool winner;
	bool draw;

	winner = check_win(test_board);

	draw = check_draw(test_board);
}

void main()
{
	//run_game();
	test_board();
		
}