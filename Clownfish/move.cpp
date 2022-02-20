#include "move.h"

namespace CFish
{

	Vector2::Vector2(uint8_t x, uint8_t y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2::Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	bool operator==(const Move& lhs, const Move& rhs)
	{
		return lhs.start.x == rhs.start.x &&
			   lhs.start.y == rhs.start.y &&
			   lhs.end.x == rhs.end.x &&
			   lhs.end.y == rhs.end.y;
	}

	Move::Move(Vector2 start, Vector2 end)
	{
		this->start = start;
		this->end = end;
	}

	Move::Move()
	{
		this->start = Vector2();
		this->end = Vector2();
	}
}