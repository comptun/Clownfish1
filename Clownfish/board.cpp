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

	void Board::move(std::string m)
	{
		Move mov = stringToMove(m);
		Move actualMove = Move(Vector2(mov.start.x, 8 - mov.start.y), Vector2(mov.end.x, 8 - mov.end.y));
		move(actualMove);
	}

	void Board::undo(std::string m)
	{
		Move mov = stringToMove(m);
		Move actualMove = Move(Vector2(mov.start.x, 8 - mov.start.y), Vector2(mov.end.x, 8 - mov.end.y));
		undo(actualMove);
	}

	Vector2 Board::indexToPos(int index) 
	{
		return Vector2(index % 8, index / 8);
	}

	Team Board::oppositeTeam(Team team)
	{
		if (team == Team::White)
			return Team::Black;
		if (team == Team::Black)
			return Team::White;
	}

	Board::MoveList Board::generateKnightMoves(Vector2 startPos)
	{
		MoveList moveList;
		Team team = getBoard(startPos.x, startPos.y).getTeam();

		if (startPos.x + 1 <= 7 && startPos.y - 2 >= 0)
		{
			if (getBoard(startPos.x + 1, startPos.y - 2).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x + 1, startPos.y - 2)));
			}
		}
		if (startPos.x + 2 <= 7 && startPos.y - 1 >= 0)
		{
			if (getBoard(startPos.x + 2, startPos.y - 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x + 2, startPos.y - 1)));
			}
		}

		if (startPos.x - 1 >= 0 && startPos.y - 2 >= 0)
		{
			if (getBoard(startPos.x - 1, startPos.y - 2).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x - 1, startPos.y - 2)));
			}
		}
		if (startPos.x - 2 >= 0 && startPos.y - 1 >= 0)
		{
			if (getBoard(startPos.x - 2, startPos.y - 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x - 2, startPos.y - 1)));
			}
		}

		if (startPos.x + 1 <= 7 && startPos.y + 2 <= 7)
		{
			if (getBoard(startPos.x + 1, startPos.y + 2).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x + 1, startPos.y + 2)));
			}
		}
		if (startPos.x + 2 <= 7 && startPos.y + 1 <= 7)
		{
			if (getBoard(startPos.x + 2, startPos.y + 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x + 2, startPos.y + 1)));
			}
		}
		if (startPos.x - 1 >= 0 && startPos.y + 2 <= 7)
		{
			if (getBoard(startPos.x - 1, startPos.y + 2).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x - 1, startPos.y + 2)));

			}
		}
		if (startPos.x - 2 >= 0 && startPos.y + 1 <= 7)
		{
			if (getBoard(startPos.x - 2, startPos.y + 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x - 2, startPos.y + 1)));

			}
		}

		return moveList;
	}

	Board::MoveList Board::generateKingMoves(Vector2 startPos)
	{
		MoveList moveList;
		Team team = getBoard(startPos.x, startPos.y).getTeam();

		if (startPos.y + 1 <= 7)
		{
			if (getBoard(startPos.x, startPos.y + 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x, startPos.y + 1)));
			}
		}
		if (startPos.y - 1 >= 0)
		{
			if (getBoard(startPos.x, startPos.y - 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x, startPos.y - 1)));
			}
		}
		if (startPos.x + 1 <= 7)
		{
			if (getBoard(startPos.x + 1, startPos.y).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x + 1, startPos.y)));
			}
		}
		if (startPos.x - 1 >= 0)
		{
			if (getBoard(startPos.x - 1, startPos.y).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x - 1, startPos.y)));
			}
		}

		if (startPos.y + 1 <= 7 && startPos.x + 1 <= 7)
		{
			if (getBoard(startPos.x + 1, startPos.y + 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x + 1, startPos.y + 1)));
			}
		}
		if (startPos.x - 1 >= 0 && startPos.y - 1 >= 0)
		{
			if (getBoard(startPos.x - 1, startPos.y - 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x - 1, startPos.y - 1)));
			}
		}
		if (startPos.x + 1 <= 7 && startPos.y - 1 >= 0)
		{
			if (getBoard(startPos.x + 1, startPos.y - 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x + 1, startPos.y - 1)));
			}
		}
		if (startPos.x - 1 >= 0 && startPos.y + 1 <= 7)
		{
			if (getBoard(startPos.x - 1, startPos.y + 1).getTeam() != team)
			{
				moveList.push_back(Move(startPos, Vector2(startPos.x - 1, startPos.y + 1)));
			}
		}

		return moveList;
	}

	Board::MoveList Board::generateSlidingPieceMoves(Vector2 startPos)
	{
		MoveList moveList;
		Team team = getBoard(startPos.x, startPos.y).getTeam();
		PieceName name = getBoard(startPos.x, startPos.y).getPiece();
		size_t index = startPos.y * 8 + startPos.x;
		
		if (name == PieceName::Queen || name == PieceName::Rook) {
			for (int i = index - 8; i >= 0; i -= 8) {
				if (position[i].getTeam() == team) {
					break;
				}
				else if (position[i].getTeam() == oppositeTeam(team)) {
					moveList.push_back(Move(startPos, indexToPos(i)));
					break;
				}
				moveList.push_back(Move(startPos, indexToPos(i)));
			}
			for (int i = index + 8; i <= 63; i += 8) {
				if (position[i].getTeam() == team) {
					break;
				}
				else if (position[i].getTeam() == oppositeTeam(team)) {
					moveList.push_back(Move(startPos, indexToPos(i)));
					break;
				}
				moveList.push_back(Move(startPos, indexToPos(i)));
			}
			for (int i = startPos.x + 1; i <= 7; ++i) {
				if (getBoard(i, startPos.y).getTeam() == team) {
					break;
				}
				else if (getBoard(i, startPos.y).getTeam() == oppositeTeam(team)) {
					moveList.push_back(Move(startPos, Vector2(i, startPos.y)));
					break;
				}
				moveList.push_back(Move(startPos, Vector2(i, startPos.y)));
			}
			for (int i = startPos.x - 1; i >= 0; --i) {
				if (getBoard(i, startPos.y).getTeam() == team) {
					break;
				}
				else if (getBoard(i, startPos.y).getTeam() == oppositeTeam(team)) {
					moveList.push_back(Move(startPos, Vector2(i, startPos.y)));
					break;
				}
				moveList.push_back(Move(startPos, Vector2(i, startPos.y)));
			}
		}

		if (name == PieceName::Queen || name == PieceName::Bishop) {
			for (int i = 1; startPos.x + i <= 7 && startPos.y - i >= 0; ++i)
			{
				if (getBoard(startPos.x + i, startPos.y - i).getTeam() == team)
				{
					break;
				}
				if ((startPos.x + i == 7 || startPos.y - i == 0) && getBoard(startPos.x + i, startPos.y - i).getPiece() == PieceName::None)
				{
					moveList.push_back(Move(startPos, Vector2(startPos.x + i, startPos.y - i)));
					break;
				}
				if (getBoard(startPos.x + i, startPos.y - i).getPiece() != PieceName::None)
				{
					moveList.push_back(Move(startPos, Vector2(startPos.x + i, startPos.y - i)));
					break;
				}
				moveList.push_back(Move(startPos, Vector2(startPos.x + i, startPos.y - i)));
			}
			for (int i = 1; startPos.x - i >= 0 && startPos.y - i >= 0; ++i)
			{
				if (getBoard(startPos.x - i, startPos.y - i).getTeam() == team)
				{
					break;
				}
				if ((startPos.x - i == 0 || startPos.y - i == 0) && getBoard(startPos.x - i, startPos.y - i).getPiece() == PieceName::None)
				{
					moveList.push_back(Move(startPos, Vector2(startPos.x - i, startPos.y - i)));
					break;
				}
				if (getBoard(startPos.x - i, startPos.y - i).getPiece() != PieceName::None)
				{
					moveList.push_back(Move(startPos, Vector2(startPos.x - i, startPos.y - i)));
					break;
				}
				moveList.push_back(Move(startPos, Vector2(startPos.x - i, startPos.y - i)));
			}
			for (int i = 1; startPos.x - i >= 0 && startPos.y + i <= 7; ++i)
			{
				if (getBoard(startPos.x - i, startPos.y + i).getTeam() == team)
				{
					break;
				}
				if ((startPos.x - i == 7 || startPos.y + i == 0) && getBoard(startPos.x - i, startPos.y + i).getPiece() == PieceName::None)
				{
					moveList.push_back(Move(startPos, Vector2(startPos.x - i, startPos.y + i)));
					break;
				}
				if (getBoard(startPos.x - i, startPos.y + i).getPiece() != PieceName::None)
				{
					moveList.push_back(Move(startPos, Vector2(startPos.x - i, startPos.y + i)));
					break;
				}
				moveList.push_back(Move(startPos, Vector2(startPos.x - i, startPos.y + i)));
			}
			for (int i = 1; startPos.x + i <= 7 && startPos.y + i <= 7; ++i)
			{
				if (getBoard(startPos.x + i, startPos.y + i).getTeam() == team)
				{
					break;
				}
				if ((startPos.x + i == 7 || startPos.y + i == 7) && getBoard(startPos.x + i, startPos.y + i).getPiece() == PieceName::None)
				{
					moveList.push_back(Move(startPos, Vector2(startPos.x + i, startPos.y + i)));
					break;
				}
				if (getBoard(startPos.x + i, startPos.y + i).getPiece() != PieceName::None)
				{
					moveList.push_back(Move(startPos, Vector2(startPos.x + i, startPos.y + i)));
					break;
				}
				moveList.push_back(Move(startPos, Vector2(startPos.x + i, startPos.y + i)));
			}
		}

		return moveList;
	}

	Board::MoveList Board::generatePawnMoves(Vector2 startPos)
	{
		MoveList moveList;
		Team team = getBoard(startPos.x, startPos.y).getTeam();
		PieceName name = getBoard(startPos.x, startPos.y).getPiece();
		if (name == PieceName::Pawn) {
			int offset = 1;
			if (team == Team::White)
				offset = -1;
			if ((team == Team::White && startPos.y > 0) || (team == Team::Black && startPos.y < 7)) {
				if (getBoard(startPos.x, startPos.y + offset).getPiece() == PieceName::None) {
					moveList.push_back(Move(startPos, Vector2(startPos.x, startPos.y + offset)));
					if (getBoard(startPos.x, startPos.y + (2 * offset)).getPiece() == PieceName::None) {
						if (team == Team::White && startPos.y == 6 && startPos.y > 1) {
							moveList.push_back(Move(startPos, Vector2(startPos.x, startPos.y + (2 * offset))));
						}
						else if (team == Team::Black && startPos.y == 1 && startPos.y < 6) {
							moveList.push_back(Move(startPos, Vector2(startPos.x, startPos.y + (2 * offset))));
						}
					}
				}
				if (startPos.x > 0) {
					if (getBoard(startPos.x - 1, startPos.y + offset).getTeam() == oppositeTeam(team)) {
						moveList.push_back(Move(startPos, Vector2(startPos.x - 1, startPos.y + offset)));
					}
				}
				if (startPos.x < 7) {
					if (getBoard(startPos.x + 1, startPos.y + offset).getTeam() == oppositeTeam(team)) {
						moveList.push_back(Move(startPos, Vector2(startPos.x + 1, startPos.y + offset)));
					}
				}
			}
		}
		return moveList;
	}

	Board::MoveList Board::generatePseudoLegalMoves(Team team)
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
				else if (name == PieceName::Knight) {
					MoveList newMoveList = generateKnightMoves(pos);
					moveList.insert(moveList.end(), newMoveList.begin(), newMoveList.end());
				}
				else if (name == PieceName::King) {
					MoveList newMoveList = generateKingMoves(pos);
					moveList.insert(moveList.end(), newMoveList.begin(), newMoveList.end());
				}
			}
		}
		return moveList;
	}

	Move Board::stringToMove(std::string move)
	{
		uint8_t startX = move.at(0) - 97;
		uint8_t startY = move.at(1) - '0';
		uint8_t endX = move.at(2) - 97;
		uint8_t endY = move.at(3) - '0';
		return Move(Vector2(startX, startY), Vector2(endX, endY));
	}

	bool Board::isLegalMove(Move move, Team team)
	{
		Move actualMove = Move(Vector2(move.start.x, 8 - move.start.y), Vector2(move.end.x, 8 - move.end.y));
		MoveList possibleMoves = generatePseudoLegalMoves(team);
		for (Move mov : possibleMoves) {
			if (mov == actualMove)
				return true;
		}
		return false;
	}

	bool Board::isLegalMove(std::string move, Team team)
	{
		return isLegalMove(stringToMove(move), team);
	}
}