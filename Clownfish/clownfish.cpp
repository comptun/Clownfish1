#include "piece.h"
#include "clownfish.h"
#include "board.h"

namespace CFish
{
	Clownfish::Clownfish() {}

	int Clownfish::main()
	{
		Board board;
		std::cout << board.generatePseudoLegalMoves(Team::White).size();
		return 1;
	}
}