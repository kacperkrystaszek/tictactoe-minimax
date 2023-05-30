#include "MainGame.h"


void MainGame::_handleMenu() 
{
	char userInputGameType;

	printf("Wpisz: \n'm' - jesli chcesz grac z druga osoba\n's' - jesli chcesz grac z komputerem\n'e' - jesli chcesz wyjsc\n");
	std::cin >> userInputGameType;

	while(userInputGameType != 'e' && userInputGameType != 's' && userInputGameType != 'm') 
	{
		std::cout << "Niepoprawna wartosc\nSprobuj jeszcze raz\n";
		std::cin >> userInputGameType;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
	
	switch (userInputGameType)
	{
	case 'm':
		_gameType = GameType::MULTIPLAYER;
		break;
	case 's':
		_gameType = GameType::SINGLEPLAYER;
		break;
	case 'e':
		exit(0);
	}

	printf("Podaj rozmiar planszy i liczbe znakow w ciagu, ktora wygrywa w formacie: rozmiar ciag ");
	std::cin >> _size >> _inARow;

	while (_size < 3 || _size > 9)
	{
		std::cout << "Niepoprawna wartosc\nSprobuj jeszcze raz\n";
		std::cin >> _size >> _inARow;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
	

	char userChoice;

	printf("\nChcesz byc X czy O? (O rozpoczyna) ");
	std::cin >> userChoice;
	do
	{
		if (userChoice == 'X' || userChoice == 'x') 
		{
			_playerA = X_MARK;
			_playerB = O_MARK;
			_currentPlayer = _playerB;
		}
		else if(userChoice == 'O' || userChoice == 'o')
		{
			_playerA = O_MARK;
			_playerB = X_MARK;
			_currentPlayer = _playerA;
		}
		else
		{
			printf("Niepoprawna wartosc\n");
			std::cin >> userChoice;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (userChoice != 'X' && userChoice != 'O' && userChoice != 'x' && userChoice != 'o');
}

void MainGame::_changePlayer() 
{
	if (_currentPlayer == _playerA) 
	{
		_currentPlayer = _playerB;
	} 
	else 
	{
		_currentPlayer = _playerA;
	}
}

void MainGame::_displayresult(int gameEnd)
{
	if (gameEnd == WON_GAME) 
	{
		if (_currentPlayer == _playerA) 
		{
			printf("Wygrales!\n\n");
		} 
		else 
		{
			printf("Przegrales\n\n");
		}
	} 
	else 
	{
		printf("Remis\n\n");
	}
}

void MainGame::_humanMove() 
{
	bool moveMade = false;
	while (moveMade == false) 
	{
		int x, y;
		printf("Podaj wspolrzedne w kolejnosci w sposob: wiersz kolumna\n ");
		
		std::cin >> x >> y;

		x--;
		y--;
		
		if (_board.getVal(y, x) == EMPTY) 
		{
			_board.setVal(y, x, _currentPlayer);
			moveMade = true;
		} 
		else 
		{
			printf("Niepoprawne pole\n");
		}
	} 
	
}

void MainGame::_pcMove()
{
	_ai.makeMove(_board, _playerB);
}

void MainGame::run() 
{
	while(true)
	{
		_handleMenu();
		_board.init(_size, _inARow);
		while (true)
		{		
			_board.print();

			if (_gameType == GameType::SINGLEPLAYER) 
			{
				if (_currentPlayer == _playerA) 
				{
					_humanMove();
				} 
				else 
				{
					_pcMove();
				}
			} 
			else if (_gameType== GameType::MULTIPLAYER) 
			{
				_humanMove();
			}
			int gameEnd = _board.checkVictory();

			if (gameEnd == WON_GAME || gameEnd == TIE_GAME) 
			{
				_board.print();
				_displayresult(gameEnd);
				break;
			} 
			else 
			{
				_changePlayer();
			}
		}
	}
}

MainGame::MainGame() {}


MainGame::~MainGame() {}
