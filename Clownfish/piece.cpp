#include "piece.h"
namespace CFish
{

	Piece::Piece(PieceName name, Team team)
	{
		this->name = name;
		this->team = team;
	}
	Piece::Piece()
	{
		this->name = PieceName::None;
		this->team = Team::None;
	}

	PieceName Piece::getPiece()
	{
		return this->name;
	}

	Team Piece::getTeam()
	{
		return this->team;
	}

	void Piece::setPiece(PieceName name)
	{
		this->name = name;
	}

	void Piece::setTeam(Team team)
	{
		this->team = team;
	}
}