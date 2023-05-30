#include "AI.h"


void AI::init(int playerType) 
{
	_aiPlayer = playerType;
	if (_aiPlayer == X_MARK) 
	{
		_humanPlayer = O_MARK;
	} 
	else 
	{
		_humanPlayer = X_MARK;
	}
}

void AI::makeMove(Board & board, int playerType) 
{
	AI::init(playerType);

	Move bestMove = _getBestMove(board, _aiPlayer);
	board.setVal(bestMove.x, bestMove.y, _aiPlayer);
}

AI::AI() {}


AI::~AI() {}

Move AI::_getBestMove(Board & board, int player)
{
	int bestScore = INT_MIN;
	int score;
	Move bestMove;
	int size = board.size;
	int alpha = INT_MIN;
	int beta = INT_MAX;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if(board.getVal(i, j) == EMPTY)
			{
				board.setVal(i, j, _aiPlayer);
				score = _minimax(board, 20, false, alpha, beta);
				board.setVal(i, j, EMPTY);

				if (score > bestScore)
				{
					bestScore = score;
					bestMove.x = i;
					bestMove.y = j;
				}
				
			}
		}
		
	}
	return bestMove;	
}

int AI::_minimax(Board & board, int depth, bool isMaximizing, int alpha, int beta) 
{
	int rv = board.checkVictory();
	if (depth <= 0)
	{
		return rv;
	}
	
	if(rv == WON_GAME && isMaximizing)
	{
		return -WON_GAME;
	}
	if(!isMaximizing && rv == WON_GAME)
	{
		return WON_GAME;
	}
	if(rv == TIE_GAME)
	{
		return TIE_GAME;
	}

	if(isMaximizing)
	{
		int bestScore = INT_MIN;
		int size = board.size;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if(board.getVal(i, j) == EMPTY)
				{
					board.setVal(i, j, _aiPlayer);
					int score = _minimax(board, --depth, false, alpha, beta);
					board.setVal(i, j, EMPTY);
					bestScore = std::max(score, bestScore);
					alpha = std::max(alpha, bestScore);
					if(beta <= alpha)
					{
						break;
					}
				}
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = INT_MAX;
		int size = board.size;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if(board.getVal(i, j) == EMPTY)
				{
					board.setVal(i, j, _humanPlayer);
					int score = _minimax(board, --depth, true, alpha, beta);
					board.setVal(i, j, EMPTY);
					bestScore = std::min(score, bestScore);
					beta = std::min(beta, bestScore);
					if(beta <= alpha)
					{
						break;
					}
				}
			}
		}
		return bestScore;
	}
}
