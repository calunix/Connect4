#include "ConnectGame.h"
#include <iostream>
#include <windows.h>

ConnectGame::ConnectGame() {
	numCols = 8;
	numRows = 8;
	numToWin = 4;

	this->gameBoard.resize(this->numRows);
	for (auto& row : this->gameBoard) {
		row.resize(this->numCols);
	}
}

ConnectGame::ConnectGame(int numCols, int numRows, int numToWin) {
	this->numCols = numCols;
	this->numRows = numRows;
	this->numToWin = numToWin;

	this->gameBoard.resize(this->numRows);
	for (auto& row : this->gameBoard) {
		row.resize(this->numCols);
	}
}

void ConnectGame::DrawBoard() {
	
	system("cls");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "Connect4 v. " << VERSION << std::endl << std::endl;

	std::cout << "        ";
	for (int i = 0; i < this->numCols; ++i) {
		std::cout << i << "  ";
	}
	std::cout << std::endl;

	std::cout << "        ";
	std::cout << "-";
	for (int i = 0; i < this->numCols - 1; ++i) {
		std::cout << "---";
	}
	std::cout << std::endl;

	for (int i = 0; i < this->numRows; ++i) {
		if (i < 10) {
			std::cout << "    " << i << " | ";
		}
		else if (i > 9 && i < 100) {
			std::cout << "   " << i << " | ";
		}
		for (int j = 0; j < this->numCols; ++j) {
			if (this->gameBoard.at(i).at(j) == 0) {
				std::cout << "*" << "  ";;
			}
			else if (this->gameBoard.at(i).at(j) == 1) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << this->gameBoard.at(i).at(j) << "  ";
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else if (this->gameBoard.at(i).at(j) == 2) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << this->gameBoard.at(i).at(j) << "  ";
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void ConnectGame::PlayerTurn(ConnectGame::Player player) {
	std::cout << "Player " << player << "'s turn." << std::endl;
	std::string userInput;

	do {
		std::cout << "Select a column: " << std::endl;
		getline(std::cin, userInput);
	} while (false == PlacePiece(userInput, player));
}

bool ConnectGame::GameWon(ConnectGame::Player player) {

	bool sequenceFound = false;
	int i, j;

	if (player == ConnectGame::Player::None) {
		return sequenceFound;
	}

	for (i = this->numRows - 1; i > -1; --i) {
		for (j = 0; j < this->numCols; ++j) {
			if (this->gameBoard.at(i).at(j) == player) {

				if (CheckRow(player, i, j)) {
					sequenceFound = true;
					return sequenceFound;
				}

				if (CheckColumn(player, i, j)) {
					sequenceFound = true;
					return sequenceFound;
				}

				if (CheckDiagonal(player, i, j)) {
					sequenceFound = true;
					return sequenceFound;
				}
			}
		}
	}

	return sequenceFound;
}

bool ConnectGame::PlacePiece(std::string userInput, ConnectGame::Player player) {

	for (int i = 0; i < userInput.size(); ++i) {
		if (isalpha(userInput.at(i))) {
			return false;
		}
	}
	
	int columnChoice = stoi(userInput);

	if (columnChoice < 0 || columnChoice > this->numCols - 1) {
		std::cout << "Please select a column between [0," << this->numCols - 1 << "]" << std::endl;
		return false;
	}

	int emptyRow = -1;
	for (int r = this->numRows - 1; r > -1; --r) {
		if (this->gameBoard.at(r).at(columnChoice) == ConnectGame::Player::None) {
			emptyRow = r;
			break;
		}
	}

	if (emptyRow == -1) {
		std::cout << "Column is full!" << std::endl;
		return false;
	}

	this->gameBoard.at(emptyRow).at(columnChoice) = player;
	return true;
}

bool ConnectGame::CheckDiagonal(ConnectGame::Player player) {
	bool diagonalFound = false;

	int i, j, k;
	int rightDiag = 0;
	int leftDiag = 0;
	int maxRightDiag = 1;
	int maxLeftDiag = 1;

	for (i = this->numRows - 1; i > -1; --i) {
		for (j = 0; j < this->numCols; ++j) {
			if (this->gameBoard.at(i).at(j) == player) {

				int rightDiag = 1;
				int leftDiag = 1;

				for (k = 1; (i - k > -1) && (j + k < this->numCols); ++k) {
					if (this->gameBoard.at(i - k).at(j + k) == player) {
						++rightDiag;
						if (maxRightDiag < rightDiag) {
							maxRightDiag = rightDiag;
						}
					}
					else {
						rightDiag = 0;
					}
					if (maxRightDiag == this->numToWin) {
						diagonalFound = true;
						return diagonalFound;
					}
				}

				for (k = 1; (i - k > -1) && (j - k > -1); ++k) {
					if (this->gameBoard.at(i - k).at(j - k) == player) {
						++leftDiag;
						if (maxLeftDiag < leftDiag) {
							maxLeftDiag = leftDiag;
						}
					}
					else {
						leftDiag = 0;
					}
					if (maxLeftDiag == this->numToWin) {
						diagonalFound = true;
						return diagonalFound;
					}
				}

			}
		}
	}
	
	return diagonalFound;
}

bool ConnectGame::CheckRow(ConnectGame::Player player) {
	
	bool rowFound = false;
	int rowsConsec = 0;

	for (int c = 0; c < this->numCols; ++c) {
		for (int r = this->numRows - 1; r > -1; --r) {
			if (gameBoard[r][c] == player) {
				++rowsConsec;
			}
			if (rowsConsec == this->numToWin) {
				rowFound = true;
				break;
			}
			if (gameBoard[r][c] != player) {
				rowsConsec = 0;
			}
		}
	}
	
	return rowFound;
}

bool ConnectGame::CheckColumn(ConnectGame::Player player) {
	
	bool columnFound = false;
	int colsConsec = 0;

	for (int r = numRows - 1; r > -1; --r) {
		for (int c = 0; c < numCols; ++c) {
			if (gameBoard[r][c] == player) {
				++colsConsec;
			}
			if (colsConsec == numToWin) {
				columnFound = true;
				return columnFound;
			}
			if (gameBoard[r][c] != player) {
				colsConsec = 0;
			}
		}
	}
	
	return columnFound;
}