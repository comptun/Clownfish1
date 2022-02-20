#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H

#include "clownfish.h"
#include "piece.h"
#include "move.h"
#include <vector>

namespace CFish
{
	class MoveList
	{
	private:
		std::vector<Move> moves;
	public:
		void push_move(Move move);
		Move* begin();
		Move* end();
		size_t size();
		Move at(size_t index);
	};
}

#endif
