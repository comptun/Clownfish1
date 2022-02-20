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