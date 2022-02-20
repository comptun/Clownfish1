#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "move.h"
#include <string>
#include <iostream>
#include <vector>

namespace CFish
{
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
		typedef std::vector<Move> MoveList;
		Piece getBoard(int x, int y);
		bool setFen(std::string fen);
		void print();
		Team oppositeTeam(Team team);
		friend std::ostream& operator <<(std::ostream& output, Board data);
		Move stringToMove(std::string move);
		void move(Move m);
		void undo(Move m);
		void move(std::string m);
		void undo(std::string m);
		Vector2 indexToPos(int index);
		MoveList generateSlidingPieceMoves(Vector2 startPos);
		MoveList generateKnightMoves(Vector2 startPos);
		MoveList generateKingMoves(Vector2 startPos);
		MoveList generatePawnMoves(Vector2 startPos);
		MoveList generatePseudoLegalMoves(Team team);
		bool isLegalMove(Move move, Team team);
		bool isLegalMove(std::string move, Team team);
		Board(std::string fen);
		Board();
	};
}
#endif