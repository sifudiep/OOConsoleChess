#pragma once

#include "Piece.h"

class Pawn : public Piece
{
	using Piece::Piece;
	
	void update_possible_coordinates(BoardSquare board[8][8]) override {
		possible_coordinates.clear();
		
		if (owner == Owner::Blue) {
			if (coordinate.y + 1 < 8 && board[coordinate.y + 1][coordinate.x].owner == Owner::None) {
				possible_coordinates.emplace_back(Coordinate(coordinate.x, coordinate.y + 1));
			}
			
			if (first_move && board[coordinate.y + 2][coordinate.x].owner == Owner::None) {
				possible_coordinates.emplace_back(Coordinate(coordinate.x, coordinate.y + 2));
			}

			if (board[coordinate.y + 1][coordinate.x + 1].owner == Owner::Red) {
				possible_coordinates.emplace_back(Coordinate(coordinate.x+1, coordinate.y+1));
			}

			if (board[coordinate.y + 1][coordinate.x - 1].owner == Owner::Red) {
				possible_coordinates.emplace_back(Coordinate(coordinate.x - 1, coordinate.y + 1));
			}

			if (coordinate.x + 1 < 8) board[coordinate.y + 1][coordinate.x + 1].attackedSquare[0] = true;
			if (coordinate.x - 1 >= 0) board[coordinate.y + 1][coordinate.x - 1].attackedSquare[0] = true;
			 
		} else if (owner == Owner::Red) {
			if (coordinate.y - 1 >= 0 && board[coordinate.y - 1][coordinate.x].owner == Owner::None) {
				possible_coordinates.emplace_back(Coordinate(coordinate.x, coordinate.y - 1));
			}
			
			if (first_move && board[coordinate.y - 2][coordinate.x].owner == Owner::None) {
				possible_coordinates.emplace_back(Coordinate(coordinate.x, coordinate.y - 2));
			}

			if (board[coordinate.y - 1][coordinate.x + 1].owner == Owner::Blue) {
				possible_coordinates.emplace_back(Coordinate(coordinate.x + 1, coordinate.y - 1));
			}

			if (board[coordinate.y - 1][coordinate.x - 1].owner == Owner::Blue) {
				possible_coordinates.emplace_back(Coordinate(coordinate.x - 1, coordinate.y - 1));
			}

			if (coordinate.x + 1 < 8) board[coordinate.y - 1][coordinate.x + 1].attackedSquare[1] = true;
			if (coordinate.x - 1 >= 0) board[coordinate.y - 1][coordinate.x - 1].attackedSquare[1] = true;
		}
	};
};
