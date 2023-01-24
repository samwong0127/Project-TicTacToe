# Project-TicTacToe
 
 
This project is to develop a Tic-Tac-Toe game that can be transformed into a Gomoku game because they share similar characteristics. E.g. Two players in a game; Two kinds of pieces;Play in a square gameboard etc. The game is designed in object-oriented and a practice of my software design skills.

A Game class that supports both *Tic-Tac-Toe* and *Gomoku (Five-in-a-row)* and will be the base class of other **two-player-two-chess games** e.g. Reversi
by initializing the game object with different board sizes and winning matches.

Both of them are supproted beacause they share common characteristics
such as the way of checking if a player wins: He forms an unbroken chain of N stones horizontally, vertically, or diagonally.
And the fact that winning condition is not checked by hard codes 

e.g. `board[0][0] == board[0][1] = board[0][2]`,

But by locating the new moves and checking it's eight directions to reduce time complexity of matching the whole board.



## Future plan
Feature:
- Let player selects which game to player
System:
- Dynamically allocate memory for the game board
