#include "MyOthelloAI.hpp"
#include "OthelloAI.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <string>
#include <cstdlib>
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, ronac1::MyOthelloAI, "Troll (Required)");

// chooseMove() takes a constant OthelloGameState and decides on
// a move, returning a std::pair whose elements describe the (x, y)
// coordinate of the cell where the chosen move should be made.
std::pair<int, int> ronac1::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
	std::pair<int, int> gameOver(-1, -1);
	std::pair<int, int> nextMove;

	int searchVal;
	//negative infinity
	int bestMove = -10000;
	// Make sure which color you are
	// color will be uncertain in search()
	bool blackTurn = state.isBlackTurn();

	if(state.isGameOver())
	{
		return gameOver;
	}
	else
	{
		for(int i = 0; i < state.board().width(); ++i)
		{
			for(int j = 0; j < state.board().height(); ++j)
			{
				if (state.isValidMove(i, j)) {
					std::unique_ptr<OthelloGameState>clone = state.clone();
					// Search should return the max
					searchVal = search(clone, 3, blackTurn);

					if(searchVal > bestMove)
					{
						bestMove = searchVal;
						// set the pair's coordinates
						nextMove.first = i;
						nextMove.second = j;
					}
				}
			}
		}

	}
	return nextMove;
}


int ronac1::MyOthelloAI::search(std::unique_ptr<OthelloGameState>& clone, int depth, bool blackTurn)
{
	int min = 100000;
	int max = -100000;
	int tempMax;
	int tempMin;

	if(depth == 0 || clone->isGameOver())
	{
		// current evaluation of board
		return eval(clone, blackTurn);
	}
	else
	{
		// if it's my turn (there's a chance you'll be black or white)
		// choose move will show you which color you are
		if(clone->isBlackTurn() == blackTurn)
		{
			// for each valid move that I can make from s
			for(int i = 0; i < clone->board().width(); ++i)
			{
				for(int j = 0; j < clone->board().height(); ++j)
				{
					// make that move on s yielding a state s' search (s', depth - 1)
					if(clone->isValidMove(i, j))
					{
						
						//create another clone
						std::unique_ptr<OthelloGameState> cloneState = clone->clone();
						cloneState->makeMove(i, j);

						// after making a move it should be white's turn not black's turn

						// Must compare the values to find max before searching again
						tempMax = search(cloneState, depth-1, blackTurn);

						if(tempMax > max)
						{
							max = tempMax;
						}
					}
				}

			}
			//return the maximum value returned from recursive search calls
			return max;
		}

		else
		{
			for(int i = 0; i < clone->board().height(); ++i)
			{
				for(int j = 0; j < clone->board().width(); ++j)
				{
						
					// make that move on s yielding a state s' search (s', depth - 1)
					if(clone->isValidMove(i, j))
					{
						
						//create another clone
						std::unique_ptr<OthelloGameState> cloneState= clone->clone();

						cloneState->makeMove(i, j);

						tempMin = search(cloneState, depth-1, blackTurn);

						if(tempMin < min)
						{
							min = tempMin;
						}
					}
				}
			}
			return min;
		}
	}
	return -1;
}
// Need a strategy
int ronac1::MyOthelloAI::eval(std::unique_ptr<OthelloGameState>& clone, bool blackTurn)
{
	if(blackTurn)
	{
		return clone->blackScore()-clone->whiteScore();
	}
	else
	{
		return clone->whiteScore()-clone->blackScore();
	}
}
