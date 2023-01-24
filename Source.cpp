#include <iostream>
#include <vector>
#include <string>
#include <cctype>

/*

	Game class: A base class for TicTacToe and Gomoku
	TicTacToe and Gomoku classes: A Derived class from Game class
	

	TicTacToe and Gomoku are supproted beacause they share common characteristics
	such as the way of checking if a player wins: He forms an unbroken chain of N stones horizontally, vertically, or diagonally.
	And the fact that winning condition is not checked by hard codes e.g. board[0][0] == board[0][1] = board[0][2]
	But by locating the new moves to reduce time complexity of matching


*/

#define BOARD_SIZE 15 // Default game board size
#define WINNING_MATCHES 5 // Default number of stones that forms an unbroken chain and wins the game
using namespace std;

enum Player {X='X', O='O'};

// Game class are designed for two players only
class Game {
private:
	char gameBoard[BOARD_SIZE][BOARD_SIZE];
	int gameBoardSize = BOARD_SIZE;
	bool gameTie;
	Player currentPlayer = X;
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
		setGameBoard(board_size);

		this->maxMoves = board_size * board_size;
		this->gameBoardSize = board_size;
		this->gameTie = false;

		setBorders(board_size);

		this->winningMatches = winMatches;
		
	}
	
	void setGameBoard(int board_size) {
		for (int i = 0; i < board_size; i++) {
			for (int j = 0; j < board_size; j++) {
				this->gameBoard[i][j] = ' ';
			}
		}
	}

	void setBorders(int board_size) {
		this->borders = "";
		for (int i = 0; i < board_size; i++) {
			this->borders += "- - ";
		}
	}

	string getBorders() {
		return borders;
	}

	void printBoard() {
		int board_size = getGameBoardSize();
		string borders = getBorders();
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

	void setGameBoardSize(int size) {
		gameBoardSize = size;
		maxMoves = size * size;
	}

	int getGameBoardSize() {
		return gameBoardSize;
	}

	void setWinningMatches(int matches) {
		winningMatches = matches;
	}

	void setGameTie(bool tied) {
		gameTie = false;
	}

	void resetGame() {
		int board_size = getGameBoardSize();
		setGameBoard(board_size);
		setGameTie(false);
		this->maxMoves = board_size * board_size;
		this->currentPlayer = X;
	}

	void startGame() {
		cout << "\n\nGame created.\n\nNotes:\n";
		cout << "Entering the row and column index of the position separated by a space (e.g. the top left corner is 0 0).\n";
		cout << "Non-numerical input may crash the game.\n";
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


				cout << "Enter 1 to play again or -1 to go back to main menu:\n";
				cin >> replay;
				resetGame();
				if (replay == -1) {
					break;
				}
				else {
					n_moves = 0;
					printBoard();
				}
			}


			n_moves++;


		}
	}

};

// The TicTacToe class that will inherit Game class
class TicTacToe: public Game {
private:
	//char gameBoard[3][3];
	//int winningMatches = 3;
	string borders;
public:
	TicTacToe() {

		int board_size = 3;
		int winMatches = 3;

		//cout << currentPlayer << endl;
		setBorders(board_size);
		
		//this->gameTie = false;
		setGameTie(false);

		setGameBoardSize(board_size);
		//this->maxMoves = board_size * board_size;
		//this->gameBoardSize = board_size;
		setWinningMatches(winMatches);
		//this->winningMatches = winMatches;

		/*
		this->borders = "";
		for (int i = 0; i < board_size; i++) {
			this->borders += "- - ";
		}
		*/
		setBorders(board_size);
		

	}

};


// The Gomoku class that will also inherit Game class
class Gomoku : public Game {
private:
	//char gameBoard[15][15];
	//int winningMatches = 3;
	string borders;
public:
	Gomoku() {

		int board_size = 15;
		int winMatches = 5;


		
		setBorders(board_size); // Build the borders

		//this->gameTie = false;
		setGameTie(false);

		setGameBoardSize(board_size);
		//this->maxMoves = board_size * board_size;
		//this->gameBoardSize = board_size;
		setWinningMatches(winMatches);
		//this->winningMatches = winMatches;

		/*
		this->borders = "";
		for (int i = 0; i < board_size; i++) {
			this->borders += "- - ";
		}
		*/
		setBorders(board_size);


	}

};

int main() {
	
	

	//Game ttt = Game(3, 3);
	//Game gomoku = Game(15, 5);

	TicTacToe ttt_inherited1 = TicTacToe();

	Gomoku gomoku_inherited1 = Gomoku();
	//gomoku_inherited1.startGame();
	
	//ttt.startGame();
	cout << "######################################\n\n";
	cout << "# Welcome to Dual-Player-Chess game! #\n\n";
	cout << "######################################\n\n";
	
	int playMode = 0;
	
	while (playMode != -1) {

		cout << "\nEnter 1 to play TicTacToe or 2 to play Gomoku (Five-in-a-row)\n";
		cout << "Or enter -1 to exit\n";
		cin >> playMode;
		if (playMode == -1) { break; }
		else if (playMode == 1) {
			ttt_inherited1.startGame();
		}
		else if (playMode == 2) {
			gomoku_inherited1.startGame();
		}
		else {
			cout << "I don't understand. Please check your input.\n";
		}
	}
	


	return 0;
}