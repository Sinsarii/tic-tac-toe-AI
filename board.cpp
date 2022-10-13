#include <iostream>
#include "ai.h"
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <tuple>
#include <map>

using std::string;
using std::vector;
using std::cout;
using std::cin;

using namespace std;

/************* TODO LIST *************/
struct Player {
	string player_name;
	string player_symbol;
};

struct check_move
{
	bool valid_move;
	string error_message;
};

struct winner
{
	string player_name;
	int number_of_wins;
};

//function that creates a board
vector<vector<string>> new_board()
{
	string NONE = " ";

	vector<vector<string>> board;

	vector<string> l1 = { NONE, NONE, NONE };
	vector<string> l2 = { NONE,NONE,NONE };
	vector<string> l3 = { NONE, NONE, NONE };

	board.push_back(l1);
	board.push_back(l2);
	board.push_back(l3);

	return board;
}

//function that prints the board
void print_board(vector<vector<string>>& board)
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

//function that pretty prints the board
void render(vector<vector<string>>& board)
{
	//print top coordinate markers based on board size
	//make a 3 space buffer around board

	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "   ";
	for (int i = 0; i < board.size(); i++)
	{
		SetConsoleTextAttribute(console_color, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		if (i % 2)
		{
			SetConsoleTextAttribute(console_color, FOREGROUND_BLUE | FOREGROUND_RED);
		}
		cout << i << " ";
	}
	cout << endl;

	//print the top barrier
	cout << "   ";
	for (int i = 0; i < board.size(); i++)
	{
		cout << "--";
	}
	cout << endl;

	//print board with a space, coordinate, and barrier before each line
	for (int i = 0; i < board.size(); i++)
	{
		//Y-Coordinate and Left border color. Alternate Colors of numbers.
		SetConsoleTextAttribute(console_color, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		if (i % 2)
		{
			SetConsoleTextAttribute(console_color, FOREGROUND_BLUE | FOREGROUND_RED);
		}

		cout << " " << i;

		SetConsoleTextAttribute(console_color, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		cout << "|";

		for (int j = 0; j < board[i].size(); j++)
		{
			//PLAYER COLORS X = YELLOW, O = CYAN
			if (board[i][j] == "X")
			{
				SetConsoleTextAttribute(console_color, FOREGROUND_RED | FOREGROUND_GREEN);
			}
			else if (board[i][j] == "O")
			{
				SetConsoleTextAttribute(console_color, FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			cout << board[i][j] << " ";
		}

		//Right border color
		SetConsoleTextAttribute(console_color, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		cout << "|" << endl;
	}
	//print lower barrier
	//lower border color
	SetConsoleTextAttribute(console_color, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	cout << "   ";
	for (int i = 0; i < board.size(); i++)
	{
		cout << "--";
	}
	cout << endl;
}

tuple<int, int> human_player()
{
	int x_coord, y_coord;

	cout << "What is your X-coordinate move?" << endl;
	cin >> x_coord;

	cout << "What is your Y-coordinate move?" << endl;
	cin >> y_coord;

	tuple<int, int> player_move = { x_coord, y_coord };

	return player_move;
}


//function that gets move from player
tuple<int, int> get_move(vector<vector<string>> board, string player_name, string player_symbol)
{
	if (player_name == "randomAI")
	{
		return ai_random_move(board, player_name);
	}
	else if (player_name == "smartAI")
	{
		return find_winning_then_blocking_moves_ai(board, player_symbol);
	}
	else if (player_name == "minmaxAI")
	{
		return minmax(board, player_symbol);
	}
	else
	{
		return human_player();
	}
}


//function that swaps players after a move is made
string swap_player(string player)
{
	if (player == "X")
	{
		player = "O";
	}
	else if (player == "O")
	{
		player = "X";
	}
	return player;
}

Player set_player(vector<Player> player_list, Player current_player)
{
	//find current player
	Player next_player;


	for (int i = 0; i < player_list.size(); i++)
	{
		if (player_list[i].player_name == current_player.player_name)
		{
			if ((i + 1) >= player_list.size())
			{
				next_player = player_list[0];
			}
			else
			{
				next_player = player_list[++i];
			}
		}
	}

	//iterate to next player down the list, go back to beginning if necessary

	return next_player;
}
//function that makes move on the board
vector<vector<string>> make_move(vector<vector<string>> board, tuple<int, int> player_move, string player)
{
	board[get<0>(player_move)][get<1>(player_move)] = player;
	return board;
}

//function that checks if move is legal
check_move is_valid_moveset(vector<vector<string>> board, tuple<int, int> move, string player)
{
	check_move movecheck;
	
	if ((get<1>(move) >= 0 && get<1>(move) < board[0].size()) &&
		(get<0>(move) >= 0 && get<0>(move) < board.size()))
	{
		//second, check if player move is open
		if (board[get<0>(move)][get<1>(move)] == " ")
		{
			movecheck.valid_move = true;
			movecheck.error_message = "Move valid.";
		}
		else
		{
			movecheck.valid_move = false;
			movecheck.error_message = "Move location is already taken, try again.";
		}
	}
	else
	{
		movecheck.valid_move = false;
		movecheck.error_message = "Move was not within the bounds of the board, try again.";
	}
	return movecheck;
}

//function that checks if move is legal (and if board is full) **DEPRECATED**
tuple<int, int> is_valid_move(vector<vector<string>> board, string player)
{

	tuple<int, int> player_move;

	while (true)
	{
		//get the player move
		//player_move= get_move();
		// Get AI Move
		//player_move = random_ai(board);
		//first check if player move is within board bounds
		if ((get<1>(player_move) >= 0 && get<1>(player_move) < board[0].size()) &&
			(get<0>(player_move) >= 0 && get<0>(player_move) < board.size()))
		{
			//second, check if player move is open
			if (board[get<0>(player_move)][get<1>(player_move)] == " ")
			{
				break;
			}
			else
			{
				cout << "Move location is already taken, try again." << endl;
			}
		}
		else
		{
			cout << "Move was not within the bounds of the board, try again." << endl;
		}
	}
	return player_move;
}

//function that checks win conditions
bool check_win(vector<vector<string>> board, string current_player)
{
	bool winner = false;


	//check columns
	for (int column = 0; column < board[0].size(); column++)
	{
		//check if first element is an open same (stops complete blank column as being a win condition

		string first_element = current_player;

		if (first_element != " ")
		{
			for (int row = 0; row < board.size(); row++)
			{
				//if consecutive values are the same as the first element, continue to make winner true until it is false
				if (first_element == board[row][column])
				{
					winner = true;
				}
				else
				{
					winner = false;
					break;
				}
			}
		}
		//if a row was found to be a win, break and record true
		if (winner == true)
		{
			return winner;
		}
	}


	//check rows 

	for (int row = 0; row < board.size(); row++)
	{
		//check if first element is an open same (stops complete blank column as being a win condition

		string first_element = current_player;

		if (first_element != " ")
		{
			for (int column = 0; column < board[row].size(); column++)
			{
				//if consecutive values are the same as the first element, continue to make winner true until it is false
				if (first_element == board[row][column])
				{
					winner = true;
				}
				else
				{
					winner = false;
					break;
				}
			}
		}
		//if a column was found to be a win, break and record true
		if (winner == true)
		{
			return winner;
		}
	}


	//check diagonal

	//diagonal check should only work if board is a square and there is an entry in either top corner of game.

	bool left_diagonal_winner = true;
	bool right_diagonal_winner = true;
	bool left_diagonal_possible = true;
	bool right_diagonal_possible = true;

	string first_element_left_diagonal = current_player;
	string first_element_right_diagonal = current_player;

	if (board.size() == board[0].size() && (first_element_left_diagonal != " " || first_element_right_diagonal != " "))
	{


		for (int row = 0; row < board.size(); row++)
		{


			if (first_element_left_diagonal != " " && left_diagonal_possible)
			{
				if (first_element_left_diagonal == board[row][row] && left_diagonal_winner == true)
				{
					left_diagonal_winner = true;
				}


				if (first_element_left_diagonal != board[row][row])
				{
					left_diagonal_winner = false;
					left_diagonal_possible = false;
				}
			}
			else
			{
				left_diagonal_winner = false;
			}


			if (first_element_right_diagonal != " " && right_diagonal_possible)
			{

				if (first_element_right_diagonal == board[row][board[0].size() - 1 - row] && right_diagonal_winner == true)
				{
					right_diagonal_winner = true;
				}

				if (first_element_right_diagonal != board[row][board[0].size() - 1 - row])
				{
					right_diagonal_winner = false;
					right_diagonal_possible = false;
				}
			}
			else
			{
				right_diagonal_winner = false;
			}

		}

		if (left_diagonal_winner == true)
		{
			return left_diagonal_winner;
		}

		if (right_diagonal_winner == true)
		{
			return right_diagonal_winner;
		}
	}
	return winner;

}

//function that checks to see if all moves have been made
bool check_draw(vector<vector<string>> board)
{
	bool draw = true;

	for (int row = 0; row < board.size(); row++)
	{
		for (int column = 0; column < board[row].size(); column++)
		{
			if (board[row][column] == " ")
			{
				draw = false;
			}
		}
	}

	return draw;
}

bool check_endstate(vector<vector<string>> board, string player)
{
	bool winner = false;
	bool draw = false;

	winner = check_win(board, player);
	draw = check_draw(board);

	if (winner)
	{
		cout << player << " has won!" << endl;
		return true;

	}
	else if (draw)
	{
		cout << "There are no more moves left, the game is a draw." << endl;
		return true;
	}
	return false;
}

void win_print(string player)
{
	cout << "Player " << player << " has won." << endl;
}

bool check_continue()
{
	char continue_game;
	bool input = true;

	

	do
	{
		cout << "Would you like to play another game? (Y/N)" << endl;
		cin >> continue_game;
		if (continue_game == 'Y' || continue_game == 'y')
		{
			return true;
		}
		else if (continue_game == 'N' || continue_game == 'n')
		{
			return false;
		}
		else
		{
			cout << "Please enter a valid input (Y/N)" << endl;
		}
	} while (true);


}

vector<winner> archive_wins(vector<winner> game_record, Player current_winner)
{
	winner new_winner;
	new_winner.player_name = current_winner.player_name;
	new_winner.number_of_wins = 1;

	if (game_record.size() == 0)
	{
		game_record.push_back(new_winner);
		return game_record;
	}


	for (int i = 0; i < game_record.size(); i++)
	{
		if (game_record[i].player_name == current_winner.player_name)
		{
			game_record[i].number_of_wins = game_record[i].number_of_wins + 1;
			return game_record;
		}
	}
	game_record.push_back(new_winner);
	return game_record;
}

