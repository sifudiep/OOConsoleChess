#pragma once
#include <cctype>
#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <string>

#include "Bishop.h"
#include "BoardSquare.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"

class Board
{
public:
	BoardSquare board[8][8];
	std::vector<Piece*> all_pieces;
	bool end_game = false;
	Owner turn = Owner::Blue;

	Piece* redKing = all_pieces[all_pieces.size() - 1];
	Piece* blueKing = all_pieces[all_pieces.size() - 2];

	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

	Board() {
		reset_board_pieces();
		clear_board();
		update_all_possible_coordinates();
	}

	bool move_piece(char symbol, Coordinate destination, Coordinate startPosition, bool draw) {
		for (size_t i = 0; i < all_pieces.size(); i++) {
			if (all_pieces[i]->owner == turn) {
				if (all_pieces[i]->symbol == symbol) {
					if (all_pieces[i]->coordinate.x == startPosition.x && all_pieces[i]->coordinate.y == startPosition.y) {
						for (size_t j = 0; j < all_pieces[i]->possible_coordinates.size(); j++) {
							if (destination.x == all_pieces[i]->possible_coordinates[j].x && destination.y == all_pieces[i]->possible_coordinates[j].y) {
								capture_square(destination);
								all_pieces[i]->coordinate = destination;
								if (all_pieces[i]->first_move) all_pieces[i]->first_move = false;
								clear_board();
								update_all_possible_coordinates();
								if (draw) draw_board();
								
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool move_removes_king_check(Coordinate start, Coordinate destination, char symbol) {
		if (move_piece(symbol,destination,start, false)) {
			king_is_under_check();
			
			Piece* king_to_check = turn == Owner::Blue ? blueKing : redKing;
			if (king_to_check->is_attacked == false) {
				draw_board();
				return true;
			}

			move_piece(symbol, start, destination, true);
			return false;
		}

		return false;
	}

	void capture_square(Coordinate destination) {
		for (size_t i = 0; i < all_pieces.size(); i++) {
			if (all_pieces[i]->coordinate.x == destination.x && all_pieces[i]->coordinate.y == destination.y) {
				all_pieces.erase(all_pieces.begin() + i);
				break;
			}
		}
	}

	void update_all_possible_coordinates() {
		for (size_t i = 0; i < all_pieces.size(); i++) {
			all_pieces[i]->update_possible_coordinates(board);
		}

		//all_pieces[all_pieces.size() - 1]->update_possible_coordinates(board);
		//all_pieces[all_pieces.size() - 2]->update_possible_coordinates(board);
	}

	void king_is_under_check() {
		bool redIsUnderCheck = false;
		bool blueIsUnderCheck = false;
		
		for (size_t i = 0; i < all_pieces.size()-1; i++) {
			for (size_t j = 0; j < all_pieces[j]->possible_coordinates.size(); j++) {
				if (all_pieces[i]->owner == Owner::Blue) {
					if (all_pieces[i]->coordinate.x == redKing->coordinate.x && all_pieces[i]->coordinate.y == redKing->coordinate.y) {
						redIsUnderCheck = true;
					}
				}

				if (all_pieces[i]->owner == Owner::Red) {
					if (all_pieces[i]->coordinate.x == blueKing->coordinate.x && all_pieces[i]->coordinate.y == blueKing->coordinate.y) {
						blueIsUnderCheck = true;
					}
				}
			}
		}

		if (redIsUnderCheck) {
			redKing->is_attacked = true;
		} else {
			redKing->is_attacked = false;
		}

		if (blueIsUnderCheck) {
			blueKing->is_attacked = true;
		}
		else {
			blueKing->is_attacked = false;
		}
	}

	void game_input() {
		start:
		std::string input;

		std::cout << "Please move a chess piece using chess notation: " << std::endl;
		
		Piece* king_to_check = turn == Owner::Blue ? blueKing : redKing;
		if (king_to_check->is_attacked) {
			std::cout << "KING IS UNDER CHECK, MAKE A MOVE TO REMOVE THE CHECK! :" << std::endl;
		}
		std::cin >> input;

		if (input.size() == 2) {
			int x = std::tolower(input[0]) - 97;
			int y = (int)input[1] - 49;

			std::cout << "SQUARE : " << input[0] << "/" << input[1] << std::endl;
			std::cout << "ATTACKED BY BLUE : " << board[y][x].attackedSquare[0] << std::endl;
			std::cout << "ATTACKED BY RED : " << board[y][x].attackedSquare[1] << std::endl;
			return;
		}
		
		if (std::isalpha(input[0]) && input.size() == 5) {
			int startX = std::tolower(input[1]) - 97;
			int startY = (int)input[2] - 49;

			int endX = std::tolower(input[3]) - 97;
			int endY = (int)input[4] - 49;

			if (king_to_check->is_attacked) {
				bool removes_check = move_removes_king_check(Coordinate(startX, startY), Coordinate(endX,endY), input[0]);
				if (!removes_check) {
					std::cout << "Move is not legal, try again:" << std::endl;
					goto start;
				}
			} else {
				bool movePieceWorked = move_piece(input[0], Coordinate(endX, endY), Coordinate(startX, startY), true);
				if (!movePieceWorked) {
					std::cout << "Something went wrong with your input....";
					goto start;
				}
			} 
			
			turn = (turn == Owner::Blue) ? Owner::Red : Owner::Blue;
			std::string turnText = (turn == Owner::Blue) ? "BLUE" : "RED";
			int textColor = turn == Owner::Blue ? 9 : 12;
			std::cout << "Success, it's: ";
			SetConsoleTextAttribute(h_console, textColor);
			std::cout << turnText;
			SetConsoleTextAttribute(h_console, 7);
			std::cout << "'s turn to make a move!";
		} else {
			std::cout << "Input was not correctly formatted...";
			goto start;
		}
	}

	void clear_board() {
		system("cls");
		
		for (int i = 7; i >= 0; i--) {
			for (int j = 0; j < 8; j++) {
				board[i][j] = BoardSquare(' ', Owner::None);
			}
		}

		for (size_t i = 0; i < all_pieces.size(); i++) {
			board[all_pieces[i]->coordinate.y][all_pieces[i]->coordinate.x] = BoardSquare(all_pieces[i]->symbol, all_pieces[i]->owner);
		}
	}

	void draw_board() {
		for (int i = 7; i >= 0; i--) {
			std::cout << '|' << i+1 << "| ";
			for (int j = 0; j < 8; j++) {
				if (board[i][j].owner == Owner::Blue) {
					SetConsoleTextAttribute(h_console, 9);
				}

				if (board[i][j].owner == Owner::Red) {
					SetConsoleTextAttribute(h_console, 12);
				}

				std::cout << '[' << board[i][j].symbol << ']';
				SetConsoleTextAttribute(h_console, 7);
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "    |a||b||c||d||e||f||g||h|" << std::endl;
	}

	void reset_board_pieces() {
		all_pieces.clear();

		// Spawning Pawns
		//for (int i = 0; i < 8; i++) {
		//	all_pieces.emplace_back(new Pawn(Coordinate(i, 1), Owner::Blue, 'P'));
		//	all_pieces.emplace_back(new Pawn(Coordinate(i, 6), Owner::Red, 'P'));
		//}

		// Spawning Rooks
		//all_pieces.emplace_back(new Rook(Coordinate(0, 0), Owner::Blue, 'R'));
		//all_pieces.emplace_back(new Rook(Coordinate(7, 0), Owner::Blue, 'R'));
		//all_pieces.emplace_back(new Rook(Coordinate(0, 7), Owner::Red, 'R'));
		//all_pieces.emplace_back(new Rook(Coordinate(7, 7), Owner::Red, 'R'));

		//// Spawning Knights
		//all_pieces.emplace_back(new Knight(Coordinate(1, 0), Owner::Blue, 'N'));
		//all_pieces.emplace_back(new Knight(Coordinate(6, 0), Owner::Blue, 'N'));
		//all_pieces.emplace_back(new Knight(Coordinate(1, 7), Owner::Red, 'N'));
		//all_pieces.emplace_back(new Knight(Coordinate(6, 7), Owner::Red, 'N'));

		// Spawning Bishops
		//all_pieces.emplace_back(new Bishop(Coordinate(2, 0), Owner::Blue, 'B'));
		//all_pieces.emplace_back(new Bishop(Coordinate(5, 0), Owner::Blue, 'B'));
		//all_pieces.emplace_back(new Bishop(Coordinate(2, 7), Owner::Red, 'B'));
		//all_pieces.emplace_back(new Bishop(Coordinate(5, 7), Owner::Red, 'B'));

		//// Spawning Queens
		//all_pieces.emplace_back(new Queen(Coordinate(3, 0), Owner::Blue, 'Q'));
		all_pieces.emplace_back(new Queen(Coordinate(3, 7), Owner::Red, 'Q'));

		//// Spawning Kings
		all_pieces.emplace_back(new King(Coordinate(4, 3), Owner::Blue, 'K'));
		all_pieces.emplace_back(new King(Coordinate(4, 7), Owner::Red, 'K'));
	
	}
};

