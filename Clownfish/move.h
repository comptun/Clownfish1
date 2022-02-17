#ifndef MOVE_H
#define MOVE_H
namespace Clownfish 
{
	class Vector2
	{
	public:
		int x;
		int y;
		Vector2(int x, int y);
		Vector2();
	};

	class Move
	{
	public:
		Vector2 start;
		Vector2 end;
		Move(Vector2 start, Vector2 end);
		Move();
	};
}
#endif
