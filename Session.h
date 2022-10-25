#pragma once


#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "winner.h"

using std::string;
using std::vector;


class Session
{
public:


	vector<winner> game_record;

	Player current_winner;

	vector<Player> playerList;

	void archive_wins(Player current_winner);

};

