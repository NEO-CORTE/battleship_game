#pragma once
#include "settings.h"


// SHIP class
class Ship {
public:
	int size = 0;
	int orientation = 0; // 0 - horizontal, 1 - vertical
	int HP = 0;
	pair<int, int> position = make_pair(0, 0);
	bool isSunken() {
		return HP == 0;
	}
};


// Ships by sizes

// Size = 1
class ship_1 : public Ship {
public:
	ship_1() :Ship() {
		HP = 1;
		size = 1;
	}
};

// Size = 2
class ship_2 : public Ship {
public:
	ship_2() :Ship() {
		HP = 2;
		size = 2;
	}
};

// Size = 3
class ship_3 : public Ship {
public:
	ship_3() :Ship() {
		HP = 3;
		size = 3;
	}
};

// Size = 4
class ship_4 : public Ship {
public:
	ship_4() :Ship() {
		HP = 4;
		size = 4;
	}
};

