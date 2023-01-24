# Project-TicTacToe
 
 
This project is to develop a Tic-Tac-Toe game that can be transformed into a Gomoku game because they share similar characteristics. E.g. Two players in a game; Two kinds of pieces;Play in a square gameboard etc. The game is designed in an object-oriented style and a practice of my software design.

*Game* class: A base class for TicTacToe and Gomoku
*TicTacToe* and *Gomoku* classes: A Derived class from *Game* class

*Tic-Tac-Toe* and *Gomoku (Five-in-a-row)* inherit the member functions from the base class.
The Game class can be the base class of other **two-player-two-chess games** e.g. Reversi


Both of them are supproted beacause they share common characteristics
such as the way of checking if a player wins: He forms an unbroken chain of N stones horizontally, vertically, or diagonally.
And the fact that winning condition is not checked by hard codes 

e.g. `board[0][0] == board[0][1] = board[0][2]`,

But by locating the new moves and checking it's eight directions to reduce time complexity of matching the whole board.



## Future plan
Feature:
- Let player selects which game to player (Finished on 23 Jan)
System:
- A Menu class for the main menu (where players choose a game)
