#include "piece.h"
#include "clownfish.h"
#include "board.h"

namespace CFish
{
	Clownfish::Clownfish()
	{
		this->gameRunning = true;
	}

	void Clownfish::gameLoop()
	{
		while (gameRunning) {

			std::cout << board << "\n";
			
			std::string move;
			std::cin >> move;

			if (board.isLegalMove(move, Team::White)) {
				board.move(move);
			}
			else {
				std::cout << "Illegal Move\n";
			}
		}
	}

	int Clownfish::main()
	{
		gameLoop();
		return 1;
	}
}