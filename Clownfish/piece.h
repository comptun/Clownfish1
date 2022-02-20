#ifndef PIECE_H
#define	PIECE_H
#include <iostream>
namespace CFish
{
	enum class PieceName : uint8_t
	{
		Pawn = 0,
		Knight,
		Bishop,
		Rook,
		Queen,
		King,
		None
	};

	enum class Team : uint8_t
	{
		White = 0,
		Black,
		None
	};

	class Piece
	{
	public:
		Piece(PieceName name, Team team);
		Piece();
		PieceName getPiece();
		Team getTeam();
		void setPiece(PieceName name);
		void setTeam(Team team);
	private:
		PieceName name;
		Team team;
	};
}
#endif
