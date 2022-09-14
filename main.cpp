#include <iostream>
#include "ai.h"
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

/************* TODO LIST *************/

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
void print_board(vector<vector<string>> & board)
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			cout << board[i][j] << " ";
		}
		cout <<  endl;
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

//function that gets move from player
tuple<int,int> get_move()
{
	int x_coord, y_coord;

	cout << "What is your X-coordinate move?" << endl;
	cin >> x_coord;

	cout << "What is your Y-coordinate move?" << endl;
	cin >> y_coord;

	tuple<int, int> player_move = { x_coord, y_coord };

	return player_move;
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

//function that makes move on the board
vector<vector<string>> make_move(vector<vector<string>> board, tuple<int, int> player_move, string player)
{
	board[get<1>(player_move)][get<0>(player_move)] = player;
	return board;
}

//function that checks if move is legal (and if board is full)
tuple<int, int> is_valid_move(vector<vector<string>> board, string player)
{

	tuple<int, int> player_move;

	while (true)
	{
		//get the player move
		//player_move= get_move();
		// Get AI Move
		player_move = random_ai(board);
		//first check if player move is within board bounds
		if ((get<1>(player_move) >= 0 && get<1>(player_move) < board[0].size()) &&
			(get<0>(player_move) >= 0 && get<0>(player_move) < board.size()))
		{
			//second, check if player move is open
			if (board[get<1>(player_move)][get<0>(player_move)] == " ")
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
bool check_win(vector<vector<string>> board)
{
	bool winner = false;
	

	//check columns
	for (int column = 0; column < board[0].size(); column++)
	{
		//check if first element is an open same (stops complete blank column as being a win condition

		string first_element = board[0][column];

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
		
		string first_element = board[row][0];
		
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

	//diagonal check should only work if board is a square

	bool left_diagonal_winner = false;
	bool right_diagonal_winner = false;

	if (board.size() == board[0].size())
	{
		string first_element_left_diagonal = board[0][0];
		string first_element_right_diagonal = board[0][board[0].size() - 1];

		for (int row = 0; row < board.size(); row++)
		{


			if (first_element_left_diagonal != " ")
			{
				if (first_element_left_diagonal == board[row][row] && left_diagonal_winner == true)
				{
					left_diagonal_winner = true;
				}


				if (first_element_left_diagonal != board[row][row])
				{
					left_diagonal_winner = false;
				}
			}


			if (first_element_right_diagonal != " ")
			{

				if (first_element_right_diagonal == board[row][board[0].size() - 1 - row] && right_diagonal_winner == true)
				{
					right_diagonal_winner = true;
				}

				if (first_element_right_diagonal != board[row][board[0].size() - 1 - row])
				{
					right_diagonal_winner = false;
				}
			}

		}

		if (left_diagonal_winner == true )
		{
			return winner;
		}

		if (right_diagonal_winner == true)
		{
			return winner;
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

void win_print(string player)
{
	cout << "Player " << player << " has won." << endl;
}

bool continue_game()
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

void run_game()
{
	vector<vector<string>> board = new_board();

	render(board);

	string player = "X";

	bool winner;
	bool draw;
	bool continue_bool = true;

	while(continue_bool)
	{
		tuple<int, int> player_move = is_valid_move(board, player);

		board = make_move(board, player_move, player);

		render(board);

		player = swap_player(player);

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
		else if (draw)
		{
			cout << "Game is a draw" << endl;
			continue_bool = continue_game();
			if (continue_bool == true)
			{
				board = new_board();
				render(board);

			}
		}

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

void test_game()
{
	vector<vector<string>> test_board =
	{
		{"X","X","X"},
		{"O","X","O"},
		{"X","X","X"}

	};

	check_win(test_board);
}

void main()
{
	run_game();
		
}