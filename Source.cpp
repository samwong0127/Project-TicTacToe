#include <iostream>
#include <vector>
#include <string>
#include <cctype>

/*

	 
	A Game class that supports both Tic Tac Toe and Gomoku (Five-in-a-row)
	by initializing the game object with different board sizes and winning matches.

	Both of them are supproted beacause they share common characteristics
	such as the way of checking if a player wins: He forms an unbroken chain of N stones horizontally, vertically, or diagonally.
	And the fact that winning condition is not checked by hard codes e.g. board[0][0] == board[0][1] = board[0][2]
	But by locating the new moves to reduce time complexity of matching


*/

#define BOARD_SIZE 15
#define WINNING_MATCHES 5
using namespace std;

enum Player {X='X', O='O'};

// Game class are designed for two players only
class Game {
private:
	char gameBoard[BOARD_SIZE][BOARD_SIZE];
	int gameBoardSize = BOARD_SIZE;
	bool gameTie;
	Player currentPlayer;
	int maxMoves;
	int winningMatches = WINNING_MATCHES;
	string borders;

public:
	Game() {
		currentPlayer = X;
		
		//cout << currentPlayer << endl;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				gameBoard[i][j] = ' ';
			}
		}
		maxMoves = BOARD_SIZE * BOARD_SIZE;
		
		gameTie = false;

		borders = "";
		for (int i = 0; i < BOARD_SIZE; i++) {
			borders += "- - ";
		}

		
	}

	
	Game(int board_size, int winMatches) {
		this->currentPlayer = X;

		//cout << currentPlayer << endl;
		for (int i = 0; i < board_size; i++) {
			for (int j = 0; j < board_size; j++) {
				this->gameBoard[i][j] = ' ';
			}
		}
		this->maxMoves = board_size * board_size;
		this->gameBoardSize = board_size;
		this->gameTie = false;

		this->borders = "";
		for (int i = 0; i < board_size; i++) {
			this->borders += "- - ";
		}

		this->winningMatches = winMatches;
		
	}
	

	void printBoard() {
		int board_size = getGameBoardSize();
		cout << "\n    ";
		for (int i = 0; i < board_size; i++) {
			//cout << i << "   ";
			printf("%2d  ", i);
		}
		cout << "\n   " << borders << "-\n";
		//cout << "- - - - - - -\n";
		
		for (int i = 0; i < board_size; i++) {
			//cout << i << " | ";
			printf("%2d | ", i);
			for (int j = 0; j < board_size; j++) {
				// Color changing; Needs <windows.h>
				/* 
				if (gameBoard[i][j] == 'X') {
					system("Color 0C");
				}
				if (gameBoard[i][j] == 'O') {
					system("Color 0A");
				}
				else {
					system("Color 07");
				}
				*/
				cout << gameBoard[i][j] << " | ";
			}
			cout << "\n   " << borders << "-\n";
			
		}
		cout << endl;
	}

	// Place the moves
	void playMove(int row, int col) {
		if (currentPlayer == X) {
			gameBoard[row][col] = 'X';
		}
		else {
			gameBoard[row][col] = 'O';
		}
		//lastRow = row;
		//lastCol = col;
		maxMoves--;
		switchPlayer();
	}

	// Vertical checking with input row & column
	bool verticalMatching(int row, int col) {
		// Check Upwards
		
		int upperMatches = 0, lowerMatches = 0;
		int temp_row = row;
		char marker = gameBoard[row][col];
		int board_size = getGameBoardSize();

		//cout << "Upward:\n";
		while (temp_row >= 0) {
			
			if (gameBoard[temp_row][col] == marker) {
				//cout << "row/col: " << temp_row << "/" << col << " matched\n";
				upperMatches++;
			}
			else {
				if (upperMatches >= winningMatches) {
					return true;
				}
				else {
					break;
				}
			}
			if (upperMatches >= winningMatches) {
				return true;
			}
			temp_row--;
		}

		//cout << "Downward:\n";
		temp_row = row;
		// Check Downwards
		while (temp_row < board_size) {
			
			if (gameBoard[temp_row][col] == marker) {
				//cout << "row/col: " << temp_row << "/" << col << "matched\n";
				lowerMatches++;
			}
			else {
				if (lowerMatches >= winningMatches) {
					return true;
				}
				else {
					break;
				}
			}
			if (lowerMatches >= winningMatches) {
				return true;
			}
			temp_row++;
		}

		if (lowerMatches + upperMatches - 1 >= winningMatches) 
		{
			return true;
		}
		
		
		return false;

	}
	
	// Horizontal checking with input row & column
	bool horizontalMatching(int row, int col) {
		
		int leftMatches = 0, rightMatches = 0;
		int temp_col = col;
		char marker = gameBoard[row][col];
		int board_size = getGameBoardSize();

		// Check the left
		while (temp_col >= 0) {
			if (gameBoard[row][temp_col] == marker) {
				leftMatches++;
			}
			else {
				if (leftMatches >= winningMatches) {
					return true;
				}
				else {
					break;
				}
			}
			if (leftMatches >= winningMatches) {
				return true;
			}
			temp_col--;
		}

		temp_col = col;
		// Check the right
		while (temp_col < board_size) {
			if (gameBoard[row][temp_col] == marker) {
				rightMatches++;
			}
			else {
				if (rightMatches >= winningMatches) {
					return true;
				}
				else {
					break;
				}
			}
			if (rightMatches >= winningMatches) {
				return true;
			}
			temp_col++;
		}

		if (leftMatches + rightMatches - 1 >= winningMatches)
		{
			return true;
		}
		

		return false;

	}

	// Diagonal (From top-left to bottom-right) checking with input row & column
	bool diagonalMatchingNeg(int row, int col) 
	{
		int upleftMatches = 0, downrightMatches = 0;
		int temp_col = col, temp_row = row;
		char marker = gameBoard[row][col];
		
		// Check up and left
		while (temp_col >= 0 && temp_row >= 0) {
			if (gameBoard[temp_row][temp_col] == marker) {
				upleftMatches++;
			}
			else {
				if (upleftMatches >= winningMatches) {
					return true;
				}
				else {
					break;
				}
			}
			if (upleftMatches >= winningMatches) {
				return true;
			}

			temp_row--;
			temp_col--;
		}

		temp_col = col; 
		temp_row = row;
		int board_size = getGameBoardSize();
		// Check down and right
		while (temp_col < board_size && temp_row < board_size) {
			if (gameBoard[temp_row][temp_col] == marker) {
				downrightMatches++;
			}
			else {
				if (downrightMatches >= winningMatches) {
					return true;
				}
				else {
					break;
				}
			}
			if (downrightMatches >= winningMatches) {
				return true;
			}

			temp_row++;
			temp_col++;
		}

		if (downrightMatches + upleftMatches - 1 >= winningMatches) {
			return true;
		}

		return false;
	}

	// Diagonal (From top-right to bottom-left) checking with input row & column
	bool diagonalMatchingPos(int row, int col)
	{
		int uprightMatches = 0, downleftMatches = 0;
		int temp_col = col, temp_row = row;
		char marker = gameBoard[row][col];
		int board_size = getGameBoardSize();

		// Check up and right
		//cout << "Up Right:\n";
		while (temp_col < board_size && temp_row >= 0) {
			if (gameBoard[temp_row][temp_col] == marker) {
				//cout << "row/col: " << temp_row << "/" << temp_col << " matched\n";
				uprightMatches++;
			}
			else {
				if (uprightMatches >= winningMatches) {
					return true;
				}
				else {
					break;
				}
			}
			if (uprightMatches >= winningMatches) {
				return true;
			}

			temp_row--;
			temp_col++;
		}

		//cout << "Down left:\n";
		temp_col = col; temp_row = row;
		// Check down and left
		while (temp_col >= 0 && temp_row < board_size) {
			if (gameBoard[temp_row][temp_col] == marker) {
				//cout << "row/col: " << temp_row << "/" << temp_col << " matched\n";
				downleftMatches++;
			}
			else {
				if (downleftMatches >= winningMatches) {
					return true;
				}
				else {
					break;
				}
			}
			if (downleftMatches >= winningMatches) {
				return true;
			}

			temp_row++;
			temp_col--;
		}

		if (downleftMatches + uprightMatches - 1 >= winningMatches) {
			return true;
		}

		return false;
	}
	
	// Check whether the game is over or not
	bool gameOver(int row, int col) {
		/*
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// do something;
			}
		}
		*/
		if (verticalMatching(row, col) || 
			horizontalMatching(row, col) || 
			diagonalMatchingPos(row, col) ||
			diagonalMatchingNeg(row, col) )
		{
			return true;
		}
		

		if (maxMoves == 0) {
			//currentPlayer = T;
			gameTie = true;
			return true;
		}

		
		return false;

	}

	Player getCurPlayer() {
		return currentPlayer;
	}

	void switchPlayer() {

		if (currentPlayer == X) {
			//cout << "Detected player X, switch to O\n";
			currentPlayer = O;
			return;
		}
		else{
			//cout << "Detected player O, switch to X\n";
			currentPlayer = X;
			return;
		}
	}

	bool validMove(int row, int col) {
		int board_size = getGameBoardSize();
		if (row >= board_size || col >= board_size || row < 0 || col < 0) {
			return false;
		}
		
		if (gameBoard[row][col] == ' ') {
			return true;
		}
		else {
			return false;
		}
		
	}

	bool getGameTie() {
		return gameTie;
	}

	int getGameBoardSize() {
		return gameBoardSize;
	}

	void resetGameBoard() {
		int board_size = getGameBoardSize();
		for (int i = 0; i < board_size; i++) {
			for (int j = 0; j < board_size; j++) {
				this->gameBoard[i][j] = ' ';
			}
		}
		this->gameTie = false;
		this->maxMoves = board_size * board_size;
		this->currentPlayer = X;
	}

	void startGame() {
		cout << "Game created\nNotes:\n";
		cout << "Entering the row and column index of the position separated by a space (e.g. the top left corner is 0 0).\n";
		cout << "Non-numerical input will crash the program.\n";
		printBoard();


		int n_moves = 0;
		int row, col;
		bool gameEnd;
		char curPlayer;
		int replay = 1;

		while (replay == 1) {
			curPlayer = getCurPlayer();
			//cout << x.getCurPlayer() << endl;
			cout << "Player " << curPlayer << ". Please place your move:\n";

			cin >> row;
			cin >> col;



			while (!validMove(row, col))
			{
				cout << "Your input is invalid. Please check the indexes and enter again.\n";
				cin >> row;
				cin >> col;
			}


			playMove(row, col);
			printBoard();
			gameEnd = gameOver(row, col);
			if (gameEnd) {
				if (getGameTie()) {
					cout << "A Tied Game!\n";
				}
				else {
					cout << "Player " << curPlayer << " wins with " << n_moves + 1 << " moves\n";
				}


				cout << "Enter 1 to replay and 0 to exit:\n";
				cin >> replay;
				if (replay == 0) {
					break;
				}
				else {
					resetGameBoard();
					n_moves = 0;
					printBoard();
				}
			}


			n_moves++;


		}
	}

};


class TicTacToe: public Game {
private:
	char gameBoard[3][3];
	int winningMatches = 3;
public:
	TicTacToe() {
		Game tictactoe = Game(3, 3);

		
	}
};


int main() {
	
	
	//startGame();

	//TicTacToe ttt = TicTacToe();
	//ttt.printBoard();

	Game ttt = Game(3, 3);
	Game gomoku = Game(15, 5);
	
	ttt.startGame();
	return 0;
}