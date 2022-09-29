#include <iostream>
#include "ai.h"
#include "board.h"
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <tuple>
#include <functional>

using std::string;
using std::vector;
using std::cout;
using std::cin;

using namespace std;



vector<string> get_players()
{
	int player1, player2;
	string player1_name, player2_name;

	vector<string> player_names;

	cout	<< "Select who will go first:" << endl
			<< "1. Player" << endl
			<< "2. Random AI" << endl
			<< "3. Smart AI";
	
	cin >> player1;

	switch (player1)
	{
	case 1:
		cout << "Enter your name." << endl;
		cin >> player1_name;
		player_names.push_back(player1_name);
	case 2: 
		player1_name = "randomAI";
	case 3:
		player1_name = "smartAI";
	}

	player_names.push_back(player1_name);



	cout	<< "Select who will go second:" << endl
			<< "1. Player" << endl
			<< "2. Random AI" << endl
			<< "3. Smart AI" << endl;
	
	cin >> player2;

	switch (player2)
	{
	case 1:
		cout << "Enter your name." << endl;
		cin >> player2_name;
	case 2:
		player2_name = "randomAI";
	case 3:
		player2_name = "smartAI";
	}

	player_names.push_back(player2_name);

	return player_names;

}

void play()
{
	//Create a new board
	vector<vector<string>> board = new_board();

	//display empty board
	render(board);

	bool continue_game = true;
	bool winner = false;
	bool draw = false;;

	tuple<int, int> player_move;

	check_move move_check;

	//lambda which will switch between which AI function that is chosen
	std::function <tuple<int, int>(vector<vector<string>>, string)> AI;

	//get the player names
	vector<string> player_names = get_players();

	string current_player = "X";
	string current_player_id = player_names[0];

	//Start Game
	while (continue_game)
	{
		do
		{
			player_move = get_move(board, current_player, current_player_id);

			move_check = is_valid_moveset(board, player_move, current_player);

			//if move is false, show error message

			if (move_check.valid_move == false)
			{
				cout << move_check.error_message << endl;
			}


		} while (move_check.valid_move == false);

		//make the move since it now valid

		board = make_move(board, player_move, current_player);

		render(board);

		//check if there is an endstate to the board (win or draw)


		winner = check_win(board);

		draw = check_draw(board);


		if (winner)
		{
			win_print(current_player);
			continue_game = check_continue();
			if (continue_game == true)
			{
				board = new_board();
				render(board);

			}
		}
		else if (draw && winner == false)
		{
			cout << "Game is a draw" << endl;
			continue_game = check_continue();
			if (continue_game == true)
			{
				board = new_board();
				render(board);

			}
		}
		current_player = swap_player(current_player);

	}
}

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

	//Polymorphic function wrapper to call different type of AI function
	std::function <tuple<int, int>(vector<vector<string>>, string)> AI;

	while(continue_bool)
	{

		do
		{
			//player_move = get_move();
			if (player == "X")
			{
				AI = ai_random_move;
			}
			else
			{
				AI = find_winning_then_blocking_moves_ai;
			}

			player_move = AI(board, player);

			//player_move = find_winning_then_blocking_moves_ai(board, player);
			//check_move = is_valid_moveset(board, player_move, player);
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
			continue_bool = check_continue();
			if (continue_bool == true)
			{
				board = new_board();
				render(board);

			}
		}
		else if (draw && winner == false)
		{
			cout << "Game is a draw" << endl;
			continue_bool = check_continue();
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
		{" ","X","O"}

	};

	render(test_board);

	tuple<int,int> ai_winning_move = find_winning_then_blocking_moves_ai(test_board, "X");

	test_board = make_move(test_board, ai_winning_move, "X");

	render(test_board);

	bool winner;
	bool draw;

	winner = check_win(test_board);

	draw = check_draw(test_board);
}

void menu()
{

}

void main()
{
	play();
	test_board();
		
}

