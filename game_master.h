#pragma once
#include "settings.h"
#include "ships.h"
#include "player.h"
class game_master
{
public:
	bool game_ended = 0; // 0 - game goes on, 1 - game is finished
	void VictoryCheck();
	game_master();
};