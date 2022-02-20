#ifndef CLOWNFISH_H
#define CLOWNFISH_H

#include "move.h"
#include "board.h"
#include "ai.h"

namespace CFish
{
	class Clownfish : public AI
	{
	private:
		Board board;
		Team currentTeam;
		bool gameRunning;
	public:
		void gameLoop();
		int main();
		Clownfish();
	};
}
	
#endif