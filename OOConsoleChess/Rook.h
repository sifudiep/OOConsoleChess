#pragma once
#include "Piece.h"

class Rook : public Piece
{
	using Piece::Piece;

	void update_possible_coordinates(BoardSquare board[8][8]) override {
		possible_coordinates.clear();
		
		for (int i = 1; coordinate.y + i < 8; i++) {
			bool squareIsOccupiedByOwner = add_possible_board_square(board, coordinate.x, coordinate.y + i);
			if (squareIsOccupiedByOwner)
				break;
		}

		for (int i = 1; coordinate.y - i >= 0; i++) {
			bool squareIsOccupiedByOwner = add_possible_board_square(board, coordinate.x, coordinate.y - i);
			if (squareIsOccupiedByOwner)
				break;
		}

		for (int i = 1; coordinate.x + i < 8; i++) {
			bool squareIsOccupiedByOwner = add_possible_board_square(board, coordinate.x + i, coordinate.y);
			if (squareIsOccupiedByOwner)
				break;
		}

		for (int i = 1; coordinate.x - i >= 0; i++) {
			bool squareIsOccupiedByOwner = add_possible_board_square(board, coordinate.x - i, coordinate.y);
			if (squareIsOccupiedByOwner)
				break;
		}
	};
};

