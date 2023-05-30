#include "Board.h"

Board::Board() {}


Board::~Board() {}

void Board::init(int s, int iAR) 
{
	size = s;
	inARow = iAR;
	_board.resize(size, std::vector<int>(size, EMPTY));
	clear();
}

void Board::clear() 
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			_board[i][j] = EMPTY;
		}
	}
}

void Board::print() 
{
	std::string text = "";
	text.reserve(size * size * 4);

	_addGuide(text);

	for (int y = size-1; y >=0; y--) {
		_addHorizontalLine(text);
		for (int gy = 0; gy < 3; gy++) 
		{
			if (gy == 1) 
			{
				text += std::to_string(1+y);
			} 
			else 
			{
				text += " ";
			}
			for (int x = 0; x <size; x++) 
			{
				text += "|";
				for (int gx = 0; gx < 3; gx++) 
				{
					text += GLYPHS[getVal(x, y)][gy][gx];
				}
			}
			text += "|";
			if (gy == 1) 
			{
				text += std::to_string(y+1) + "\n";
			} 
			else 
			{
				text += "\n";
			}
		}
	}
	_addHorizontalLine(text);
	_addGuide(text);

	printf("%s\n", text.c_str());
}

int Board::checkVictory()
{
	int counter = 1;
	// sprawdzenie w linii poziomej
	for (int i = 0; i < size; i++) 
	{
		counter = 1;
		for (int j = 0; j < size-1; j++) 
		{
			if ((getVal(i,j) == getVal(i,j+1)) && (getVal(i,j) != EMPTY))
			{
				counter++;
				if (counter == inARow) 
				{
					return WON_GAME;
				}
			} 
			else 
			{
				counter = 1;
			}
		}
	}

	// sprawdzenie w linii pionowej
	for (int i = 0; i < size; i++) 
	{
		counter = 1;
		for (int j = 0; j < size-1; j++) 
		{
			if ((getVal(j, i) == getVal(j+1, i)) && (getVal(j, i) != EMPTY)) 
			{
				counter++;
				if (counter == inARow) 
				{
					return WON_GAME;
				}
			} 
			else 
			{
				counter = 1;
			}
		}
	}

	for (int i = 1; i < size-inARow+1; i++)
	{
		counter = 1;
		for (int k = 0; k < (size-i-1); k++) 
		{
			if ((getVal(k, i+k) == getVal(k+1, i + k+1)) && (getVal(k, i+k) != EMPTY)) 
			{
				counter++;
				if (counter == inARow) 
				{
					return WON_GAME;
				}
			}
			else 
			{
			counter = 1;
			}
		}
	}

	for (int i = 0; i < size - inARow + 1; i++) 
	{
		counter = 1;
		for (int k = 0; k < (size - i-1); k++) 
		{
			if ((getVal(i+k, k) == getVal(i+k + 1, k + 1)) && (getVal(i+k, k) != EMPTY)) 
			{
				counter++;
				if (counter == inARow) 
				{
					return WON_GAME;
				} 
			} 
			else 
			{
			counter = 1;
			}
		}
	}

	for (int i = 0; i < size - inARow + 1; i++) 
	{
		counter = 1;
		for (int k = 0; k < (size - i-1); k++) 
		{
			if ((getVal(size-1-k,i + k) == getVal(size-1-(k + 1), i + k + 1)) && (getVal(size-1-k, i + k) != EMPTY)) 
			{
				counter++;
				if (counter == inARow) 
				{
					return WON_GAME;
				} 
			} 
			else 
			{
				counter = 1;
			}
		}
	}

	for (int i = 1; i < size - inARow + 1; i++) 
	{
		counter = 1;
		for (int k = 0; k < (size - i-1); k++) 
		{
			if ((getVal(size-1-i - k, k) == getVal(size-i - k- 2, k + 1)) && (getVal(size -1 - i - k, k) != EMPTY)) 
			{
				counter++;
				if (counter == inARow) 
				{
					return WON_GAME;
				}
			} 
			else 
			{
				counter = 1;
			}
		}
	}

	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++) 
		{
			if (_board[i][j] == EMPTY) 
			{
				return EMPTY;
			}
		}
	}
	return TIE_GAME;


}

void Board::_addHorizontalLine(std::string& s)  
{
	s += "-";
	for (int x = 0; x < size; x++) {
		s += "----";
	}
	s += "--\n";
}

void Board::_addGuide(std::string& s) 
{
	s += " ";
	for (int i = 1; i <= size; i++) {
		s += "| " + std::to_string(i) + " ";
	}
	s += "|\n";
}


void Board::setVal(int x, int y, int cellState) {
	_board[x][y] = cellState;
}

int Board::getVal(int x, int y){
	return _board[x][y];
}