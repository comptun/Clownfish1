#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "move.h"
#include <string>
#include <iostream>
#include <vector>

namespace CFish
{
	typedef std::vector<Move> MoveList;

	class Board
	{
	private:
		std::vector<Piece> capturedPieces;
		std::string fen;
		Piece position[64];
		Piece getFenPiece(char fenChar);
		char toFenChar(Piece piece);
		bool readFen(std::string fen);
	public:
		Piece getBoard(int x, int y);
		bool setFen(std::string fen);
		void print();
		friend std::ostream& operator <<(std::ostream& output, Board data);
		void move(Move m);
		void undo(Move m);
		Vector2 indexToPos(int index);
		MoveList generateSlidingPieceMoves(Vector2 startPos);
		MoveList generatePawnMoves(Vector2 startPos);
		MoveList generatePseudoLegalMoves(Team team);
		Board(std::string fen);
		Board();
	};
}
#endif