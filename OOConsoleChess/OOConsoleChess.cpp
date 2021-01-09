// OOConsoleChess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Board.h"

int main()
{
	Board board = Board();

	board.draw_board();

	while (board.end_game == false) {
		board.game_input();
	}
	
}