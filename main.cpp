#include <iostream>
#include <vector>
#include <string>

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

	vector<string> l1 = { NONE, "O", NONE };
	vector<string> l2 = { "X",NONE, "O" };
	vector<string> l3 = { "X", "X", NONE };

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

//function that gets move from player
void get_move()
{

}
//function that makes move on the board
void make_move()
{

}

//function that checks if move is legal (and if board is full)
bool check_move()
{
	return true;
}

//function that checks win conditions


void main()
{
	vector<vector<string>> board = new_board();

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