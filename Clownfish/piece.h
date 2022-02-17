#ifndef PIECE_H
#define	PIECE_H
namespace Clownfish
{
	enum class PieceName
	{
		Pawn = 0,
		Knight,
		Bishop,
		Rook,
		Queen,
		King,
		None
	};

	enum class Team
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
