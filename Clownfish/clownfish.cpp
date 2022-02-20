#include "piece.h"
#include "clownfish.h"
#include "board.h"

namespace CFish
{
	Clownfish::Clownfish() // contructor for initial chess settings
	{
		this->gameRunning = true;
		this->currentTeam = Team::White;
	}

	void Clownfish::gameLoop()
	{
		while (gameRunning) {

			std::cout << board << "\n";
			
			std::string move;
			std::cin >> move;

			if (board.isLegalMove(move, currentTeam)) {
				board.move(move);
				currentTeam = board.oppositeTeam(currentTeam);
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