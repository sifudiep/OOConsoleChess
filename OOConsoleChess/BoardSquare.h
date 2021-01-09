#pragma once
#include "Owner.h"

struct BoardSquare {
	BoardSquare(char s = ' ', Owner o = Owner::None) {
		symbol = s;
		owner = o;
	}
	
	char symbol;
	Owner owner;
	bool attackedSquare[2] {false, false};
};
