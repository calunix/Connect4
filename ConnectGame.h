#include <vector>
#include <string>

#define VERSION "1.0.1"

class ConnectGame {
	public:
		enum Player {
			None,
			First,
			Second
		};
		void DrawBoard();
		void PlayerTurn(ConnectGame::Player player);
		bool GameWon(ConnectGame::Player player);
		ConnectGame();
		ConnectGame(int numCol, int numRow, int numToWin);
	private:
		int numRows;
		int numCols;
		int numToWin;
		bool PlacePiece(std::string userInput, ConnectGame::Player player);
		std::vector<std::vector<int>> gameBoard;
		bool CheckDiagonal(ConnectGame::Player player, int row, int column);
		bool CheckRow(ConnectGame::Player player, int row, int column);
		bool CheckColumn(ConnectGame::Player player, int row, int column);
};
