#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include <string>
namespace Clownfish
{
	class Board
	{
	private:
		Piece getFenPiece(char fenChar);
		char toFenChar(Piece piece);
		bool readFen(std::string fen);

	public:
		Piece getBoard(int x, int y);
		bool setFen(std::string fen);
		void print();
		Board(std::string fen);
		Board();


	private:
		std::string fen;
		Piece position[8][8];
	};
}
#endif