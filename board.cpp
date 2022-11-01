#include <iostream>
//#include "ai.h"
#include "Player.h"
#include "winner.h"
#include "Board.h"
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <algorithm>

using std::max_element;
using std::min_element;

using std::string;
using std::vector;
using std::cout;
using std::cin;

using namespace std;

/************* TODO LIST *************/

struct Board::check_move
{
	bool valid_move;
	string error_message;
};

vector<Player> Board::get_players(int number_players)
{
	int menu_input;
	vector<string> symbols_list = { "X", "O", "#", "$", "&" };
	string player_name_input;
	vector<Player> player_list;
	vector<string> player_names;
	Player current_player;

	for (int i = 0; i < number_players; i++)
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
	return player_list;

}

//function that creates a board
vector<vector<string>> Board::new_board()
{
	string NONE = " ";

	vector<vector<string>> board;

	vector<string> l1 = { NONE, NONE, NONE };
	vector<string> l2 = { NONE,NONE,NONE };
	vector<string> l3 = { NONE, NONE, NONE };

	//vector<string> l1 = { NONE, NONE, NONE,NONE };
	//vector<string> l2 = { NONE,NONE,NONE,NONE };
	//vector<string> l3 = { NONE, NONE, NONE ,NONE };
	//vector<string> l4 = { NONE, NONE, NONE,NONE };

	board.push_back(l1);
	board.push_back(l2);
	board.push_back(l3);
	//board.push_back(l4);

	return board;
}

//function that prints the board
void Board::print_board(vector<vector<string>>& board)
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
void Board::render(vector<vector<string>>& board)
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

void Board::reset()
{
	board = new_board();
}

tuple<int, int> Board::human_player()
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
tuple<int, int> Board::get_move(vector<vector<string>> board, string player_name, string player_symbol)
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
string Board::swap_player(string player)
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

Player Board::set_player(vector<Player> &player_list, Player current_player)
{
	//find current player
	Player next_player;


	for (int i = 0; i < player_list.size(); i++)
	{
		if (player_list[i].player_symbol == current_player.player_symbol)
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
vector<vector<string>> Board::make_move(vector<vector<string>> board, tuple<int, int> player_move, string player)
{
	board[get<0>(player_move)][get<1>(player_move)] = player;
	return board;
}

//function that checks if move is legal
Board::check_move Board::is_valid_moveset(vector<vector<string>> board, tuple<int, int> move, string player)
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
tuple<int, int> Board::is_valid_move(vector<vector<string>> board, string player)
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
bool Board::check_win(vector<vector<string>> board, string current_player)
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
bool Board::check_draw(vector<vector<string>> board)
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

bool Board::check_endstate(vector<vector<string>> board, string player)
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

void Board::win_print(string player)
{
	cout << "Player " << player << " has won." << endl;
}

bool Board::check_continue()
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

vector<tuple<int, int>> Board::get_legal_moves(vector<vector<string>> board)
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

tuple<int, int> Board::ai_random_move(vector<vector<string>> board, string player)
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

	} while (move_check.valid_move == false);

	return move;
}

tuple<int, int> Board::find_winning_moves_ai(vector<vector<string>> board, string player)
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

tuple<int, int> Board::find_winning_then_blocking_moves_ai(vector<vector<string>> board, string player)
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
				else if (check_win(temp_board_block_move, opponent))
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

string Board::hash_Board(vector<vector<string>> board)
{
	string board_hash = "";

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			board_hash = board_hash.append(board[i][j]);
		}
	}

	return board_hash;
}

bool Board::check_hash_map(string hash)
{
	if (HASH_MAP.find(hash) == HASH_MAP.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

int Board::minmax_score(vector<vector<string>> board, string current_player, string opponent, string alternating_player)
{

	//if there is a terminal state, end immediatly
	if (check_win(board, current_player))
	{
		return +10;
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
	vector<tuple<int, int>> possible_moves = get_legal_moves(board);
	vector<int> scores;
	int score;
	//iterate through all moves and get a score for each move
	for (int i = 0; i < possible_moves.size(); i++)
	{
		//copy current board
		vector<vector<string>> new_board = board;
		//make move on new board
		new_board = make_move(board, possible_moves[i], alternating_player);

		//get score from new board and swap player
		score = minmax_score(new_board, current_player, opponent, swap_player(alternating_player));

		scores.push_back(score);

	}

	if (alternating_player == current_player)
	{
		return *max_element(scores.begin(), scores.end());
	}
	else
	{
		return *min_element(scores.begin(), scores.end());
	}


}

tuple<int, int> Board::minmax(vector<vector<string>> board, string current_player)
{
	tuple<int, int> move;

	string opponent = swap_player(current_player);

	//call minmax_score to calculate the value of all available moves
	vector<tuple<int, int>> possible_moves = get_legal_moves(board);

	//initialize at less than -10 so that all numbers will be larger
	int top_score = -20;
	int score;

	for (int i = 0; i < possible_moves.size(); i++)
	{
		// copy current board
		vector<vector<string>> new_board = board;

		//make move on new board
		new_board = make_move(board, possible_moves[i], current_player);

		//check if the board has already been calculated
		string board_hash = hash_Board(new_board);

		if (check_hash_map(board_hash))
		{
			score = HASH_MAP[board_hash];
		}
		else
		{
			score = minmax_score(new_board, current_player, opponent, swap_player(current_player));
			HASH_MAP.insert(pair<string,int>(board_hash, score));
		}

		if (score > top_score)
		{
			top_score = score;
			move = possible_moves[i];
		}
	}

	return move;
}

Board::Board()
{
	//Get all player and board information
	playerList = get_players(2);

	//create a new board and display it
	board = new_board();
	render(board);

}

void Board::play()
{
	//Create a new board
	

	//display empty board

	bool continue_game = true;
	bool winner = false;
	bool draw = false;;

	tuple<int, int> player_move;

	check_move move_check;

	//lambda which will switch between which AI function that is chosen
	//std::function <tuple<int, int>(vector<vector<string>>, string)> AI;

	//get the player names
	//vector<string> player_names = get_players(2);

	Player current_player;

	current_player = playerList[0];

	//Start Game

	//render(board);


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
			current_winner =  current_player;
			break;
		}

		current_player = set_player(playerList, current_player);

	}
}



