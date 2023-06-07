#pragma once
#include "settings.h"
class player {
public:
	int p_board[BOARD_SIZE][BOARD_SIZE];
	vector<Ship> player_ships;
	player() {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; i < BOARD_SIZE; i++) {
				p_board[i][j] = 0;
			}
		}
	}
	friend ostream& operator << (ostream& os, player& board) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; i < BOARD_SIZE; i++) {
				os << board.p_board[i][j];
			}
		}
		os << endl;
		return os;
	}
};