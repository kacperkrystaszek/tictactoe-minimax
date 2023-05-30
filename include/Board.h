#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <math.h>
#include <string>

const int EMPTY = 0;
const int X_MARK = 1;
const int O_MARK = 2;

const int TIE_GAME = -1;
const int WON_GAME = 10;

const char GLYPHS[3][3][3] = 
{
	{
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' }
	},
	{
		{ '\\', ' ', '/' },
		{ ' ', 'x', ' ' },
		{ '/', ' ', '\\' }
	},
	{
		{ '/', '-', '\\' },
		{ '|', ' ', '|' },
		{ '\\', '-', '/' }
	}
};

class Board {
public:
	Board();
	~Board();

	void init(int size, int inARow);
	void clear();
	void print();

	int checkVictory();

	void setVal(int x, int y, int cellState);
	int getVal(int x, int y);

	int size;
	int inARow;
private:
	void _addHorizontalLine(std::string& s);
	void _addGuide(std::string& s);

	std::vector<std::vector<int>> _board;
};

#endif