#include "board.h"
#include <iostream>

namespace Clownfish
{
	Board::Board()
	{
		setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"); // default chessboard position
	}

	Board::Board(std::string fen)
	{
		setFen(fen);
	}

	Piece Board::getBoard(int x, int y)
	{
		return position[y][x];
	}

	Piece Board::getFenPiece(char fenChar)
	{
		std::string fenChars = "PNBRQK"; // white pieces
		std::string fenChars2 = "pnbrqk"; // black pieces
		for (int i = 0; i < fenChars.size(); ++i) {
			if (fenChar == fenChars.at(i)) {
				return Piece(static_cast<PieceName>(i), Team::White);
			}
			else if (fenChar == fenChars2.at(i)) {
				return Piece(static_cast<PieceName>(i), Team::Black);
			}
		}
		return Piece();
	}


	bool Board::readFen(std::string fen) 
	{
		int yIndex = 0;
		int xIndex = 0;
		for (size_t i = 0; i < fen.size(); ++i) {
			if (isdigit(fen.at(i))) {
				xIndex += (fen.at(i) - '0') - 1;
				continue;
			}
			if (fen.at(i) == '/') {
				yIndex += 1;
				xIndex = 0;
				continue;
			}
			Piece fenPiece = getFenPiece(fen.at(i));
			if (fenPiece.getPiece() != PieceName::None && fenPiece.getTeam() != Team::None) {
				this->position[yIndex][xIndex] = fenPiece;
				xIndex += 1;
			}
			else {
				return false; // error
			}
		}
		return true;
	}

	bool Board::setFen(std::string fen) {
		this->fen = fen;
		return readFen(fen);
	}

	char Board::toFenChar(Piece piece)
	{
		std::string fenChars = "PNBRQK"; // white pieces
		std::string fenChars2 = "pnbrqk"; // black pieces
		if (piece.getTeam() == Team::White) {
			return fenChars.at(static_cast<int>(piece.getPiece()));
		}
		else if (piece.getTeam() == Team::Black) {
			return fenChars2.at(static_cast<int>(piece.getPiece()));
		}
	}

	void Board::print()
	{
		for (int i = 0; i < 8; ++i) {
			std::cout << 8 - i << " ";
			for (int j = 0; j < 8; ++j) {
				if (this->position[i][j].getPiece() != PieceName::None) {
					std::cout << toFenChar(this->position[i][j]) << " ";
				}
				else {
					std::cout << "  ";
				}
			}
			std::cout << "\n";
		}
		std::cout << "  A B C D E F G H\n";
	}
}