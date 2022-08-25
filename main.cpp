#include <iostream>
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
	cout << "   ";
	for (int i = 0; i < board.size(); i++)
	{
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
		cout << " " << i << "|";
		for (int j = 0; j < board[i].size(); j++)
		{
			cout << board[i][j] << " ";
		}
		cout << "|" << endl;
	}
	//print lower barrier
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
int swap_player(int player)
{
	if (player == 1)
	{
		player = 2;
	}
	else if (player == 2)
	{
		player = 1;
	}
	return player;
}
//function that makes move on the board
vector<vector<string>> make_move(vector<vector<string>> board, tuple<int, int> player_move, int player)
{
	if (player == 1)
	{
		board[get<1>(player_move)][get<0>(player_move)] = "X";
	}
	else if (player == 2)
	{
		board[get<1>(player_move)][get<0>(player_move)] = "O";
	}
	return board;
}

//function that checks if move is legal (and if board is full)
bool is_valid_move(vector<vector<string>> board, tuple<int, int> player_move, int player)
{
	//first check if player move is within board bounds
	if ((get<1>(player_move) >= 0 && get<1>(player_move) < board[get<1>(player_move)].size()) &&
		(get<0>(player_move) >= 0 && get<0>(player_move) < board.size()))
	{
		//second, check if player move is open
		if (board[get<1>(player_move)][get<0>(player_move)] == " ")
		{
			return true;
		}
	}

	return false;
}

//function that checks win conditions
void check_win(vector<vector<string>> board)
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
			cout << "Winner column match" << endl;
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
			cout << "Winner row match" << endl;
		}
	}


	//check diagonal

}

void run_game()
{
	vector<vector<string>> board = new_board();

	render(board);

	int player = 1;

	for (int i = 0; i < 9; i++)
	{
		tuple<int, int> player_move = get_move();

		board = make_move(board, player_move, player);

		render(board);

		player = swap_player(player);

		check_win(board);
	}



	print_board(board);


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
	test_game();
		
}