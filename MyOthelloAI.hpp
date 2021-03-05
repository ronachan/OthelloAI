#include "OthelloAI.hpp"
#include <string>
#include <cstdlib>
#include <iostream>

namespace ronac1
{
	class MyOthelloAI : public OthelloAI
	{
		public:
			// Override & create own implementation
			virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
			int search(std::unique_ptr<OthelloGameState> &clone, int depth, bool blackTurn);
			int eval(std::unique_ptr<OthelloGameState>& clone, bool blackTurn);
	};
}