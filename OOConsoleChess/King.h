#pragma once
#include <iostream>

#include "Piece.h"

class King : public Piece
{
	using Piece::Piece;
	
	// Gör en lista med bara kungar
	// Loopa igenom allPossibleCoordinatesKings 2ggr så att den första kungen vet vilka rutor motsatt kung attackkerar
	// eller gört en lista som kollar alla rutor som kungarna attackerar o reggar de separat

	bool square_is_not_attacked(BoardSquare board[8][8], int x, int y) {
		int opponent = 0;
		if (owner == Owner::Blue) opponent = 1;
		if (owner == Owner::Red) opponent = 0;
		
		std::string ownerName = owner == Owner::Blue ? "BLUE" : "RED";
		
		if (board[y][x].attackedSquare[opponent]) {
			std::cout << "RETURNING FALSE... for :" << ownerName << "@" << x+1 << y+1 << std::endl;
			return false;
		}

		return true;
	}
	
	void update_possible_coordinates(BoardSquare board[8][8]) override {
		possible_coordinates.clear();
		
		if (coordinate.x + 1 < 8) {
			if (square_is_not_attacked(board, coordinate.x + 1, coordinate.y)) {
				add_possible_board_square(board, coordinate.x + 1, coordinate.y);
			}
		}

		if (coordinate.x - 1 >= 0) {
			if (square_is_not_attacked(board, coordinate.x - 1, coordinate.y)) {
				add_possible_board_square(board, coordinate.x - 1, coordinate.y);
			}
		}

		if (coordinate.y + 1 < 8) {
			add_attacked_square(board, coordinate.x, coordinate.y + 1);
			if (square_is_not_attacked(board, coordinate.x, coordinate.y + 1)) {
				add_possible_board_square(board, coordinate.x, coordinate.y + 1);
			}
		}

		if (coordinate.y - 1 >= 0) {
			add_attacked_square(board, coordinate.x, coordinate.y - 1);
			if (square_is_not_attacked(board, coordinate.x, coordinate.y - 1)) {
				add_possible_board_square(board, coordinate.x, coordinate.y - 1);
			}
		}

		if (coordinate.y + 1 < 8 && coordinate.x + 1 < 8) {
			if (square_is_not_attacked(board, coordinate.x + 1, coordinate.y + 1)) {
				add_possible_board_square(board, coordinate.x + 1, coordinate.y + 1);
			}
		}

		if (coordinate.y + 1 < 8 && coordinate.x - 1 >= 0) {
			if (square_is_not_attacked(board, coordinate.x - 1, coordinate.y + 1)) {
				add_possible_board_square(board, coordinate.x - 1, coordinate.y + 1);
			}
		}

		if (coordinate.y - 1 >= 0 && coordinate.x + 1 < 8) {
			if (square_is_not_attacked(board, coordinate.x + 1, coordinate.y - 1)) {
				add_possible_board_square(board, coordinate.x + 1, coordinate.y - 1);
			}
		}

		if (coordinate.y - 1 >= 0 && coordinate.x - 1 >= 0) {
			if (square_is_not_attacked(board, coordinate.x - 1, coordinate.y - 1)) {
				add_possible_board_square(board, coordinate.x - 1, coordinate.y - 1);
			}
		}
	};
};

