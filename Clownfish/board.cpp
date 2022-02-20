#include "board.h"

namespace CFish
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
		return position[y * 8 + x];
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
				this->position[yIndex * 8 + xIndex] = fenPiece;
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
				if (this->position[i * 8 + j].getPiece() != PieceName::None) {
					std::cout << toFenChar(this->position[i * 8 + j]) << " ";
				}
				else {
					std::cout << ((i + j) % 2 == 0 ? "  " : std::string(1, char(254)) + " ");
				}
			}
			std::cout << "\n";
		}
		std::cout << "  A B C D E F G H\n";
	}

	std::ostream& operator <<(std::ostream& output, Board data)
	{
		data.print();
		return output;
	}

	void Board::move(Move m)
	{
		capturedPieces.push_back(getBoard(m.end.x, m.end.y));
		position[m.end.y * 8 + m.end.x] = position[m.start.y * 8 + m.start.x];
		position[m.start.y * 8 + m.start.x] = Piece();
	}

	void Board::undo(Move m)
	{
		position[m.start.y * 8 + m.start.x] = position[m.end.y * 8 + m.end.x];
		position[m.end.y * 8 + m.end.x] = capturedPieces.back();
		capturedPieces.pop_back();
	}

	Vector2 Board::indexToPos(int index) 
	{
		return Vector2(index % 8, index / 8);
	}

	MoveList Board::generateSlidingPieceMoves(Vector2 startPos)
	{
		MoveList moveList;
		Team team = getBoard(startPos.x, startPos.y).getTeam();
		PieceName name = getBoard(startPos.x, startPos.y).getPiece();
		size_t index = startPos.y * 8 + startPos.x;
		
		if (name == PieceName::Queen || name == PieceName::Rook) {
			for (int i = index - 8; i >= 0;) {
				if (position[i].getTeam() == Team::None) {
					moveList.push_back(Move(startPos, indexToPos(i)));
					i -= 8;
				}
				else if (position[i].getTeam() == team) {
					break;
				}
				else {
					moveList.push_back(Move(startPos, indexToPos(i)));
				}
				if (i == 0) break;
			}
			for (int i = index + 8; i <= 63;) {
				if (position[i].getTeam() == Team::None) {
					moveList.push_back(Move(startPos, indexToPos(i)));
					i += 8;
				}
				else if (position[i].getTeam() == team) {
					break;
				}
				else {
					moveList.push_back(Move(startPos, indexToPos(i)));
				}
				if (i == 63) break;
			}
		}

		return moveList;
	}

	MoveList Board::generatePawnMoves(Vector2 startPos)
	{
		MoveList moveList;
		Team team = getBoard(startPos.x, startPos.y).getTeam();
		PieceName name = getBoard(startPos.x, startPos.y).getPiece();
		if (name == PieceName::Pawn) {
			int offset = 1;
			if (team == Team::White)
				offset = -1;
			if (getBoard(startPos.x, startPos.y + offset).getPiece() == PieceName::None) {
				moveList.push_back(Move(startPos, Vector2(startPos.x, startPos.y + offset)));
				if (getBoard(startPos.x, startPos.y + (2 * offset)).getPiece() == PieceName::None) {
					moveList.push_back(Move(startPos, Vector2(startPos.x, startPos.y + (2 * offset))));

				}
			}
		}
		return moveList;
	}

	MoveList Board::generatePseudoLegalMoves(Team team)
	{
		MoveList moveList;
		for (uint8_t i = 0; i < 64; ++i) {
			if (position[i].getTeam() == team) {
				PieceName name = position[i].getPiece();
				Vector2 pos = indexToPos(i);
				if (name == PieceName::Pawn) {
					MoveList newMoveList = generatePawnMoves(pos);
					moveList.insert(moveList.end(), newMoveList.begin(), newMoveList.end());
				}
				else if (name == PieceName::Rook ||
						 name == PieceName::Queen ||
						 name == PieceName::Bishop) {
					MoveList newMoveList = generateSlidingPieceMoves(pos);
					moveList.insert(moveList.end(), newMoveList.begin(), newMoveList.end());
				}
			}
		}
		return moveList;
	}
}