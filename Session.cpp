#include "Session.h"
#include "Board.h"
#include "Player.h"
#include "winner.h"

using std::string;
using std::vector;


void Session::archive_wins(Player current_winner)
{
	winner new_winner;
	new_winner.player_name = current_winner.player_name;
	new_winner.number_of_wins = 1;
	bool name_found = false;
	if (game_record.size() == 0)
	{
		game_record.push_back(new_winner);
	}
	else
	{
		for (int i = 0; i < game_record.size(); i++)
		{
			if (game_record[i].player_name == current_winner.player_name)
			{
				game_record[i].number_of_wins = game_record[i].number_of_wins + 1;
				name_found = true;
			}
		}
	}
	if (name_found == false)
	{
		game_record.push_back(new_winner);
	}
}
