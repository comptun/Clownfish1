#ifndef MOVE_H
#define MOVE_H
#include <iostream>
namespace CFish
{
	class Vector2
	{
	public:
		uint8_t x;
		uint8_t y;
		Vector2(uint8_t x, uint8_t y);
		Vector2();
	};

	class Move
	{
	public:
		Vector2 start;
		Vector2 end;
		friend bool operator==(const Move& lhs, const Move& rhs);
		Move(Vector2 start, Vector2 end);
		Move();
	};
}
#endif
