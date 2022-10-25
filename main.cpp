#include <iostream>

//#include "ai.h"
#include "Board.h"
#include "Player.h"
#include "Session.h"

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
/*
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
*/
void test_ai()
{
	vector<vector<string>> test_board =
	{
		{" "," "," "},
		{" "," "," "},
		{" "," "," "}

	};

	//tuple<int, int> move = minmax(test_board, "X");
}

void play_game()
{
	Session current_session;

	Board tictactoeBoard;

	bool continue_game = true;
	int test_amount = 0;

	//menu to get player information
	tictactoeBoard.playerList = tictactoeBoard.get_players(2);
	//play game
	do
	{
		tictactoeBoard.play();
		//continue_game = check_continue();
		current_session.archive_wins(tictactoeBoard.current_winner);
		test_amount++;
	} while (continue_game && (test_amount < 10));
	//test_board();
		
}

void main()
{
	play_game();
	//test_board();
	//test_ai();
	//ask what game they will play

	//ask for players or ai

}