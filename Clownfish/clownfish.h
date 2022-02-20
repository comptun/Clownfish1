#ifndef CLOWNFISH_H
#define CLOWNFISH_H

#include "move.h"
#include "board.h"

namespace CFish
{
	class Clownfish
	{
	private:
		Board board;
		bool gameRunning;
	public:
		void gameLoop();
		int main();
		Clownfish();
	};
}
	
#endif