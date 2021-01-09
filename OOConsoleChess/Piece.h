#pragma once
#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Owner.h"
#include "BoardSquare.h"

struct BoardSquare;

class Piece {
public:
	Piece(Coordinate c, Owner o, char s) {
		coordinate = c;
		owner = o;
		symbol = s;
		first_move = true;
		

		std::string ownerName = owner == Owner::Blue ? "BLUE" : "RED";
		std::cout << ownerName << "'s " << symbol << " has spawned!" << std::endl;
	};
	
	Coordinate coordinate;
	std::vector<Coordinate> possible_coordinates;
	Owner owner;
	char symbol;
	bool first_move;
	bool is_attacked = false;
	
	void add_attacked_square(BoardSquare board[8][8], int x, int y) {
		if (owner == Owner::Blue) {
			board[y][x].attackedSquare[0] = true;
			//board[y][x].symbol = '0';
		}
		if (owner == Owner::Red) {
			board[y][x].attackedSquare[1] = true;
			//board[y][x].symbol = '1';
		}
	}
	
	bool add_possible_board_square(BoardSquare board[8][8], int x, int y) {
		add_attacked_square(board, x, y);
		
		if (board[y][x].owner != owner) {
			possible_coordinates.emplace_back(Coordinate(x, y));
			
			if (board[y][x].owner != Owner::None && board[y][x].owner != owner)
				return true;
			
			return false;
		}

		return true;
	}
	
	virtual void update_possible_coordinates(BoardSquare board[8][8]) = 0;
};


