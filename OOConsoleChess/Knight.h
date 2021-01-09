#pragma once
#include "Piece.h"

class Knight : public Piece
{
	using Piece::Piece;
	
	void update_possible_coordinates(BoardSquare board[8][8]) override {
		possible_coordinates.clear();
		
		if (coordinate.y + 2 < 8) {
			if (coordinate.x + 1 < 8) {
				add_possible_board_square(board, coordinate.x + 1, coordinate.y + 2);
			}

			if (coordinate.x - 1 >= 0) {
				add_possible_board_square(board, coordinate.x - 1, coordinate.y + 2);
			}
		}

		if (coordinate.y - 2 >= 0) {
			if (coordinate.x + 1 < 8) {
				add_possible_board_square(board, coordinate.x + 1, coordinate.y - 2);
			}

			if (coordinate.x - 1 >= 0) {
				add_possible_board_square(board, coordinate.x - 1, coordinate.y - 2);
			}
		}

		if (coordinate.x + 2 < 8) {
			if (coordinate.y + 1 < 8) {
				add_possible_board_square(board, coordinate.x + 2, coordinate.y + 1);

			}

			if (coordinate.y - 1 >= 0) {
				add_possible_board_square(board, coordinate.x + 2, coordinate.y - 1);

			}
		}

		if (coordinate.x - 2 >= 0) {
			if (coordinate.y + 1 < 8) {
				add_possible_board_square(board, coordinate.x - 2, coordinate.y + 1);
			}

			if (coordinate.y - 1 >= 0) {
				add_possible_board_square(board, coordinate.x - 2, coordinate.y - 1);
			}
		}
	};
};

