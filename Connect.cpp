#include <iostream>
#include <cstring>
#include <stdlib.h>

#include "ConnectGame.h"

void PrintUsage() {
	std::cout << "Fix me!" << std::endl;
}

int main(int argc, char* argv[])
{

	int numCol = 8;
	int numRow = 8;
	int numToWin = 4;

	if (argc == 1) {
		std::cout << "numToWin: " << numToWin << std::endl;
		ConnectGame Game();
	}

	for (int i = 1; i < argc; i = i + 2) {

		if (strcmp(argv[i], "-c") == 0) {
			numCol = atoi(argv[i + 1]);
			std::cout << "numCol: " << numCol << std::endl;
		}
		else if (strcmp(argv[i], "-r") == 0) {
			numRow = atoi(argv[i + 1]);
			std::cout << "numRow: " << numRow << std::endl;
		}
		else if (strcmp(argv[i], "-w") == 0) {
			numToWin = atoi(argv[i + 1]);
			std::cout << "numToWin: " << numToWin << std::endl;
		}
		else {
			PrintUsage();
			return 1;
		}

	}

	ConnectGame Game(numRow, numCol, numToWin);

	while (true) {
		Game.DrawBoard();
		
		Game.PlayerTurn(ConnectGame::Player::First);

		if (Game.GameWon(ConnectGame::Player::First)) {
			Game.DrawBoard();
			std::cout << "Player 1 wins!!!" << std::endl;
			break;
		}

		Game.DrawBoard();
		
		Game.PlayerTurn(ConnectGame::Player::Second);

		if (Game.GameWon(ConnectGame::Player::Second)) {
			Game.DrawBoard();
			std::cout << "Player 2 wins!!!" << std::endl;
			break;
		}
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
