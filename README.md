# Project-TicTacToe
 
A Game class that supports both *Tic-Tac-Toe* and *Gomoku (Five-in-a-row)*
by initializing the game object with different board sizes and winning matches.

Both of them are supproted beacause they share common characteristics
such as the way of checking if a player wins: He forms an unbroken chain of N stones horizontally, vertically, or diagonally.
And the fact that winning condition is not checked by hard codes e.g. board[0][0] == board[0][1] = board[0][2],
But by locating the new moves to reduce time complexity of matching



## Future plan
Feature:
- Let player selects which game to player
System:
- Dynamically allocate memory for the game board
