#include "move.h"

namespace Clownfish
{
	Vector2::Vector2(int x, int y)
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