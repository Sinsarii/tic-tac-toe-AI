#include <iostream>
#include "ai.h"
#include "board.h"
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <tuple>
#include <functional>
#include <map>

using std::string;
using std::vector;
using std::cout;
using std::cin;

using namespace std;



vector<Player> get_players(int number_players)
{
	int menu_input;
	vector<string> symbols_list = { "X", "O", "#", "$", "&" };
	string player_name_input;
	vector<Player> player_list;
	vector<string> player_names;
	Player current_player;

	for(int i = 0; i < number_players; i++)
	{
		cout << "Select Player " << (i + 1) << endl
			<< "1. Player" << endl
			<< "2. Random AI" << endl
			<< "3. Smart AI" << endl
			<< "4. Minmax AI" << endl;

		cin >> menu_input;

		switch (menu_input)
		{
		case 1:
			cout << "Enter your name." << endl;
			cin >> player_name_input;
			break;
		case 2:
			player_name_input = "randomAI";
			break;
		case 3:
			player_name_input = "smartAI";
			break;
		case 4:
			player_name_input = "minmaxAI";
			break;
		}

		current_player.player_name = player_name_input;
		current_player.player_symbol = symbols_list[i];
		player_list.push_back(current_player);
	}


	/*

	cout	<< "Select who will go second:" << endl
			<< "1. Player" << endl
			<< "2. Random AI" << endl
			<< "3. Smart AI" << endl;
	
	cin >> menu_input;

	switch (menu_input)
	{
	case 1:
		cout << "Enter your name." << endl;
		cin >> player_name_input;
	case 2:
		player_name_input = "randomAI";
	case 3:
		player_name_input = "smartAI";
	}

	player_names.push_back(player_name_input);
	*/
	return player_list;
	
}


Player play(vector<Player> player_list)
{
	//Create a new board
	vector<vector<string>> board = new_board();

	//display empty board

	bool continue_game = true;
	bool winner = false;
	bool draw = false;;

	tuple<int, int> player_move;

	check_move move_check;

	//lambda which will switch between which AI function that is chosen
	std::function <tuple<int, int>(vector<vector<string>>, string)> AI;

	//get the player names
	//vector<string> player_names = get_players(2);
	 
	Player current_player;

	current_player = player_list[0];

	//Start Game

	render(board);


	while (continue_game)
	{



		do
		{
			player_move = get_move(board, current_player.player_name, current_player.player_symbol);

			move_check = is_valid_moveset(board, player_move, current_player.player_symbol);

			//if move is false, show error message

			if (move_check.valid_move == false)
			{
				cout << move_check.error_message << endl;
			}


		} while (move_check.valid_move == false);

		//make the move since it now valid

		board = make_move(board, player_move, current_player.player_symbol);

		render(board);

		//check if there is an endstate to the board (win or draw)

		if (check_endstate(board, current_player.player_symbol))
		{
			return current_player;
		}

		current_player = set_player(player_list, current_player);

	}
}

void test_board()
{
	vector<tuple<int, int>> possible_moves;

	vector<vector<string>> test_board =
	{
		{"X"," "," "},
		{" ","X"," "},
		{" ","X","O"}

	};

	possible_moves = get_legal_moves(test_board);
	render(test_board);

	tuple<int,int> ai_winning_move = find_winning_then_blocking_moves_ai(test_board, "X");

	test_board = make_move(test_board, ai_winning_move, "X");

	render(test_board);

	bool winner;
	bool draw;

	winner = check_win(test_board, "X");

	draw = check_draw(test_board);
}

void test_ai()
{
	vector<vector<string>> test_board =
	{
		{" "," "," "},
		{" "," "," "},
		{" "," "," "}

	};

	tuple<int, int> move = minmax(test_board, "X");
}

void play_game()
{
	vector<winner> game_record;

	bool continue_game = true;
	int test_amount = 0;
	Player current_winner;
	//menu to get player information
	vector<Player> Player_list = get_players(2);
	//play game
	do
	{
		current_winner = play(Player_list);
		//continue_game = check_continue();
		game_record = archive_wins(game_record, current_winner);
		test_amount++;
	} while (continue_game && (test_amount < 10));
	test_board();
		
}

void main()
{
	play_game();
	//test_board();
	//test_ai();
	//ask what game they will play

	//ask for players or ai

}