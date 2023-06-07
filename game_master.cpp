#include "game_master.h"

player P1;
player P2;
int player1_ships_count = 0;
int player2_ships_count = 0;

int player_board_print[10][10] = { 0 };
int ai_board_print[10][10] = { 0 };

bool isValidCoordinate(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool isValidPlacement(int x, int y, int rot, player& pl, int size = 1) {
	if (rot) {
		for (int i = y; i < y + size; ++i) {
			if (!isValidCoordinate(x, i) || pl.p_board[x][i] != 0) {
				return false;
			}
		}
	}
	else {
		for (int i = x; i < x + size; ++i) {
			if (!isValidCoordinate(i, y) || pl.p_board[i][y] != 0) {
				return false;
			}
		}
	}
	return true;
}

void placeShipOnBoard(int x, int y, int size, int rot, int play) {
	//if (rot) {
	//	for (int i = y; i < y + size; ++i) {
	//		if (play == 1) {
	//			player1_ships_count++;
	//			P1.p_board[x][i] = player1_ships_count;
	//			player_board_print[x][i] = player1_ships_count;
	//		}
	//		if (play == 2) {
	//			player2_ships_count++;
	//			P2.p_board[x][i] = player2_ships_count;
	//			ai_board_print[x][i] = player2_ships_count;
	//		}
	//	}
	//}
	//else {
	//	for (int i = x; i < x + size; ++i) {
	//		if (play == 1) {
	//			player1_ships_count++;
	//			P1.p_board[i][y] = player1_ships_count;
	//			player_board_print[i][y] = player1_ships_count;
	//		}
	//		if (play == 2) {
	//			player2_ships_count++;
	//			P2.p_board[i][y] = player2_ships_count;
	//			ai_board_print[i][y] = player2_ships_count;
	//		}
	//	}
	//}


	if (play == 1) {
		if (rot == 1) {
			player1_ships_count++;
			for (int i = x; i < y + size; ++i) {
				P1.p_board[x][i] = player1_ships_count;
				player_board_print[x][i] = player1_ships_count;
			}
		}
		else {
			player1_ships_count++;
			for (int i = x; i < x + size; ++i) {
				P1.p_board[i][y] = player1_ships_count;
				player_board_print[i][y] = player1_ships_count;
			}
		}
	}
	else{
		if (rot == 1) {
			player2_ships_count++;
			for (int i = x; i < y + size; ++i) {
				P2.p_board[x][i] = player2_ships_count;
				ai_board_print[x][i] = player2_ships_count;
			}
		}
		else {
			player2_ships_count++;
			for (int i = x; i < x + size; ++i) {
				P2.p_board[i][y] = player2_ships_count;
				ai_board_print[i][y] = player2_ships_count;
			}
		}
	}
}

void placePlayerShip() {
	for (int i = 0; i < P1.player_ships.size(); ++i) {
		bool validPlacement = false;
		while (!validPlacement) {
			cout << "Enter the coordinates (x, y) for a ship of size: " << P1.player_ships[i].size << endl;
			int x, y;
			int rota;
			cin >> x >> y;
			cout << "Enter the orientation (0 - horizontal, 1 - vertical)" << endl;
			cin >> rota;
			validPlacement = isValidPlacement(x,y,rota,P1,P1.player_ships[i].size);
			if (validPlacement) {
				P1.player_ships[i].position = make_pair(x, y);
				P1.player_ships[i].orientation = rota;
				placeShipOnBoard(x, y, P1.player_ships[i].size, rota, 1);
			}
			else {
				cout << "Invalid Placement" << endl;
			}
		}
	}
}

void placeAiShipsRand() {
	srand(time(NULL));
	for (int i = 0; i < P2.player_ships.size(); ++i) {
		bool validPlacement = false;
		while (!validPlacement) {
			int x = rand() % BOARD_SIZE;
			int y = rand() % BOARD_SIZE;
			bool rota = rand() % 2;
			validPlacement = isValidPlacement(x, y, rota, P2, P2.player_ships[i].size);
			if (validPlacement) {
				P2.player_ships[i].position = make_pair(x, y);
				P2.player_ships[i].orientation = rota;
				placeShipOnBoard(x, y, P2.player_ships[i].size, rota, 2);
			}
		}
	}
}
bool isValidGuess(int x, int y, player& p) {
	return isValidCoordinate(x, y) && (p.p_board[x][y] >= 0);
}

void playerGuessPosition() {
	int x, y;
	cout << "Enter your guess (x, y)";
	cin >> x >> y;
	if (isValidGuess(x, y, P2)) {
		if (P2.p_board[x][y] > 0) {
			cout << "You hit the enemy ship of size: " << P2.player_ships[P2.p_board[x][y]-1].size << endl;
			P2.player_ships[P2.p_board[x][y]-1].HP -= 1;
			P2.p_board[x][y] = -1;
			ai_board_print[x][y] = -1;
			if (P2.player_ships[P2.p_board[x][y]-1].isSunken()) {
				cout << "You destroyed enemy ship" << endl;
			}
		}
		else {
			cout << "You missed enemy ship" << endl;
			ai_board_print[x][y] = -2;

		}
	}
	else {
		cout << "Invalid guess. Please try again." << endl;
		playerGuessPosition();
	}
}
void aiGuessPosition() {
	int x = std::rand() % BOARD_SIZE;
	int y = std::rand() % BOARD_SIZE;

	if (isValidGuess(x, y, P1)) {
		if (P1.p_board[x][y] > 0) {
			cout << "The AI hit your ship of size: " << P1.player_ships[P1.p_board[x][y]-1].size << " at position (" << x << ", " << y << ")!" << endl;
			P1.player_ships[P1.p_board[x][y]-1].HP -= 1;
			P1.p_board[x][y] = -1;
			player_board_print[x][y] = -1;
			if (P1.player_ships[P1.p_board[x][y]-1].isSunken()) {
				cout << "Your ship was destroyed" << endl;
			}
		}
		else {
			cout << "The AI missed your ship at position (" << x << ", " << y << ")." << endl;
			player_board_print[x][y] = -2;

		}
	}
	else {
		aiGuessPosition();
	}
}

void printBoards() {
	cout << "Player board" << endl << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (player_board_print[i][j] == -1) {
				cout << "X ";
			}
			else if (player_board_print[i][j] == -2)
			{
				cout << "O ";
			}
			else {
				cout << "? ";
			}
		}
		cout << endl << endl;
	}
	cout << "Player Guesses" << endl << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (ai_board_print[i][j] == -1) {
				cout << "X ";
			}
			else if (ai_board_print[i][j] == -2)
			{
				cout << "O ";
			}
			else {
				cout << "? ";
			}
		}
		cout << endl << endl;
	}
}
void printenemyboard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			cout << P2.p_board[i][j] <<" ";
		}
		cout << endl;
	}
}
void game_master::VictoryCheck() {
	int enemy_HP = 0, player_HP = 0;
	for (auto& t : P2.player_ships) {
		enemy_HP += t.HP;
	}
	for (auto& t : P1.player_ships) {
		player_HP += t.HP;
	}
	if (enemy_HP <= 0) {
		cout << "You Won" << endl;
		game_ended = 1;
		return;
	}
	if (player_HP <= 0) {
		cout << "You Lost" << endl;
		game_ended = 1;
		return;
	}
}

game_master::game_master() {
	ship_1 ship_1_1;
	//ship_2 ship_2_1;
	//ship_2 ship_2_2;
	//ship_3 ship_3_1;
	//ship_3 ship_3_2;
	//ship_4 ship_4_1;

	P1.player_ships.push_back(ship_1_1);
	//P1.player_ships.push_back(ship_2_1);
	//P1.player_ships.push_back(ship_2_2);
	//P1.player_ships.push_back(ship_3_1);
	//P1.player_ships.push_back(ship_3_2);
	//P1.player_ships.push_back(ship_4_1);

	ship_1 ai_ship_1_1;
	ship_2 ai_ship_2_1;
	ship_2 ai_ship_2_2;
	ship_3 ai_ship_3_1;
	ship_3 ai_ship_3_2;
	ship_4 ai_ship_4_1;

	P2.player_ships.push_back(ai_ship_1_1);
	P2.player_ships.push_back(ai_ship_2_1);
	P2.player_ships.push_back(ai_ship_2_2);
	P2.player_ships.push_back(ai_ship_3_1);
	P2.player_ships.push_back(ai_ship_3_2);
	P2.player_ships.push_back(ai_ship_4_1);

	placePlayerShip();

	placeAiShipsRand();

	printenemyboard();

	while (!game_ended) {
		std::cout << "Player's Turn" << std::endl;
		printBoards();
		playerGuessPosition();
		VictoryCheck();

		std::cout << "AI's Turn" << std::endl;
		aiGuessPosition();
		VictoryCheck();
	}
	cout << "Thanks for playing";

}