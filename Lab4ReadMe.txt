Andrew Sgarro (419823) and Ethan Glassman (431461)
CSE 332
Lab 4

	DESGIN DECISIONS
The game will always try to load a previously saved game file.  When the previous game was either won, or the players chose not to save, the IO.cpp file with throw an exception, which each game's source file will catch, and cause a fresh game board to be built.  This prevents having to build special game cases for save files that are corrupted.

IO.cpp checks to see if the game has a name at the top, and then uses the display name of the piece as the defining characteristic to choose which player's piece is being extracted.  In this way, we can save a fairly compact, consistent file with each piece saved to a single line in the format:
color display x y
IO.cpp will skip any line that does not have all of these elements, or where these elements describe an impossible piece.  Game.cpp stores the expected display and color for player1 and player2 and will skip any corrupted piece because we don't know which piece of information to believe in the possibility of a corrupted file.

	TESTING

Lab3.exe TicTacToe opens and begins a TicTacToe game (regardless of capitalization)
Playing valid moves returns the gameboard, displays the player’s moves so far, and then prompts the next user to input their coordinates for their move.

Entering an invalid input (anything other than the form (int, int)) gives: Lab3.exe this space is out of bounds, please choose a valid space. 
And then re-prompts the user for another move.

Attempting to play an invalid move that is out of obounds(such as 4,4) results in the game telling the: And then it re-prompts the user for a valid move

Attempting to play in an already occupied space returns a statement telling the player that “this space is occupied”, and re-prompting them to input a move.

Inputting an invalid input (such as “5, “ or “3, 2, 1” or “ab”; anything other than (int, int)) results in the game telling the user to Usage Error: Lab3.exe please input a valid string, in the format(int, int) and then re-prompts them to input coordinates. 

When a player wins (either horizontally, vertically, or diagonally), the program shows their moves so far and then says who won. For example, if player 1 wins horizontally it will output: 
Player 1’s moves so far: 2,2; 2,3; 2,1
Player 1 (X) Won the game!
(Other example test cases: Player 2 wins with 1,1; 2,2; 3,3; Player 1 wins with 1,2; 2,2; 3,3)
If either player inputs ‘quit’ the program prints: Usage Error: Lab3.exe the user has quit and then closes.

(We will talk about Saving and Loading for every game together after these initial synopses)

Lab3.exe Gomoku opens and begins a Gomoku game
Playing valid moves returns the gameboard, displays the player’s moves so far, and then prompts the next user to input their coordinates for their move.

Attempting to play an invalid move (such as 0,21) results in the game telling the Usage Error: Lab3.exe this space is out of bounds, please choose a valid space and then re-prompting the user, asking for a valid move.

Attempting to play in an already occupied space returns a statement telling the player that “this space is occupied”, and re-prompting them to input a move.
Attempting to play in an already occupied space returns a statement telling the player that “this space is occupied”, and re-prompting them to input a move.

Inputting an invalid input (such as “5, “ or “3, 2, 1” or “ab”) results in the game telling the user to Usage Error: Lab3.exe please input a valid string, in the format(int, int)and then re-prompts them to input coordinates. 

When a player wins (either horizontally, vertically, or diagonally), the program shows their moves so far and then says who won. For example, if player 1 wins horizontally it will output: 
Player 1’s moves so far: 2,2; 2,3; 2,1; 2,4; 2,5 
Player 1 (X) Won the game!

If either player inputs ‘quit’ the program closes
Starting the program returns a usage value if the user to does not type exactly Lab3.exe TicTacToe or Lab3.exe Gomoku: 
For example, typing only Lab3.exe returns: 
Usage Error: Lab3.exe the game type was not properly specified 
This same output is given when the user types too many command line arguments (Ex; Lab3.exe Gomoku TicTacToe) or incorrect arguments (Ex; Lab3.exe Gomuk).

We also developed an autoplay tester which allowed us to test many cases for Gomoku quickly:
Examples:
Correct usage:
>Lab3.exe Gomoku autoplayer horizontal
20
 19
 18
 17                              W
 16
 15                                                   W
 14                                       W
 13                  B  B  B  B  B
 12
 11
 10
  9                                          W
  8
  7
  6
  5
  4
  3
  2
  1
  0
0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
Player 1's moves so far 3,14; 4,15; 5,16; 6,17; 7,18;
Player 1 (B) won the game!

>Lab3.exe Gomoku autoplayer vertical
 20
 19
 18
 17
 16
 15                                       W
 14                                          W
 13                                                      W
 12
 11
 10
  9
  8
  7
  6               B
  5               B
  4               B              W
  3               B
  2               B
  1
  0
0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
Player 1's moves so far 5,2; 5,3; 5,4; 5,5; 5,6;
Player 1 (B) won the game!
>Lab3.exe Gomoku autoplayer diagonal_up
 20
 19
 18                     B
 17                  B                    W
 16               B
 15            B
 14         B
 13
 12
 11                                       W
 10
  9
  8                                                            W
  7                                                W
  6
  5
  4
  3
  2
  1
  0
0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
Player 1's moves so far 6,13; 7,13; 8,13; 9,13; 10,13;
Player 1 (B) won the game!

>Lab3.exe Gomoku autoplayer diagonal_down
20
 19
 18
 17                                                      W
 16                                                   W
 15
 14
 13                  B                    W
 12                     B
 11                        B     W
 10                           B
  9                              B
  8
  7
  6
  5
  4
  3
  2
  1
  0
   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
Player 1's moves so far 6,13; 7,12; 8,11; 9,10; 10,9;
Player 1 (B) won the game!

>Lab3.exe Gomoku autoplayer random

20
 19   W           W  W        B        B  B  B     W  W     W
 18   B  B     W           B     B  B     W  W     B
 17      B        W  B     W        B  W  B        W  W  B  B
 16   W        B  W     B  B     W     W     W           W  W
 15      W  B           B     B     W           B  B        W
 14            W  W        B        W        B  B  W  W     W
 13      B     B                 W     B     W        B  B  B
 12            B           W           B     W     W
 11      B  B  W  B        W  B              W  B        B  W
 10   W     W        B  W     W     B  W        W  W
  9   W     W        B     B  W  W                 B     B
  8            W  B        W  B  B  B  B     W  W  B     B  B
  7      B     B  B  W  W     W        W     B     W  B
  6   W  B  W     B  W           W  B  B        W  W  B     B
  5                     W                 W     W        W  W
  4         B     W           B           B              B
  3   B  W  W  B  W  W     B  B  W     W  W  W  W  W  B
  2            B  B     W  W     W        B  B        W     B
  1   B  B     B  B           W                 B           B
  0
   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20

Player 2's moves so far 17,14; 1,19; 9,10; 8,2; 12,16; 16,10; 12,17; 14,18; 9,9;
 18,16; 15,3; 13,5; 14,8; 5,3; 1,6; 15,6; 16,12; 12,3; 1,16; 4,8; 17,17; 6,6; 7,
2; 3,6; 14,11; 7,10; 19,19; 4,11; 18,5; 15,8; 13,18; 9,1; 5,16; 10,6; 6,3; 3,9;
16,7; 8,8; 19,11; 14,13; 5,14; 3,10; 11,15; 4,14; 6,19; 8,11; 16,14; 16,17; 19,1
5; 4,18; 5,19; 16,3; 16,6; 8,17; 1,10; 7,7; 11,14; 12,10; 5,17; 19,14; 19,5; 9,7
; 19,16; 14,16; 17,19; 17,2; 16,19; 7,5; 6,7; 10,2; 2,15; 10,3; 10,9; 10,16; 2,3
; 10,13; 1,9; 14,12; 3,3; 15,10; 15,5; 5,4; 12,7; 14,3; 8,12; 13,3;

Player 2 (W) won the game!

>Lab3.exe Gomoku autoplayer stalemate
20
 19   B  W  W  W  W  B  B  B  W  W  W  W  B  B  B  W  W  W  W
 18   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
 17   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
 16   W  W  W  W  B  B  B  B  W  W  W  W  B  B  B  B  W  W  W
 15   B  W  W  W  W  B  B  B  W  W  W  W  B  B  B  B  W  W  W
 14   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
 13   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
 12   W  W  W  W  B  B  B  B  W  W  W  W  B  B  B  B  W  W  W
 11   B  W  W  W  W  B  B  B  W  W  W  W  B  B  B  B  W  W  W
 10   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
  9   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
  8   W  W  W  W  B  B  B  B  W  W  W  W  B  B  B  B  W  W  W
  7   B  W  W  W  W  B  B  B  W  W  W  W  B  B  B  B  W  W  W
  6   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
  5   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
  4   W  W  W  W  B  B  B  B  W  W  W  W  B  B  B  B  W  W  W
  3   B  W  W  W  W  B  B  B  W  W  W  W  B  B  B  B  W  W  W
  2   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
  1   B  B  B  B  W  W  W  W  B  B  B  B  W  W  W  W  B  B  B
  0
   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20

Player 1's moves so far 1,1; 2,1; 3,1; 4,1; 9,1; 10,1; 11,1; 12,1; 17,1; 18,1; 1
9,1; 1,2; 2,2; 3,2; 4,2; 9,2; 10,2; 11,2; 12,2; 17,2; 18,2; 19,2; 1,3; 2,5; 3,5;
 4,5; 9,5; 10,5; 11,5; 12,5; 17,5; 18,5; 19,5; 1,5; 1,6; 2,6; 3,6; 4,6; 9,6; 10,
6; 11,6; 12,6; 17,6; 18,6; 19,6; 1,7; 2,9; 3,9; 4,9; 9,9; 10,9; 11,9; 12,9; 17,9
; 18,9; 19,9; 1,9; 1,10; 2,10; 3,10; 4,10; 9,10; 10,10; 11,10; 12,10; 17,10; 18,
10; 19,10; 1,11; 2,13; 3,13; 4,13; 9,13; 10,13; 11,13; 12,13; 17,13; 18,13; 19,1
3; 1,13; 1,14; 2,14; 3,14; 4,14; 9,14; 10,14; 11,14; 12,14; 17,14; 18,14; 19,14;
 1,15; 2,17; 3,17; 4,17; 9,17; 10,17; 11,17; 12,17; 17,17; 18,17; 19,17; 1,17; 1
,18; 2,18; 3,18; 4,18; 9,18; 10,18; 11,18; 12,18; 17,18; 18,18; 19,18; 1,19; 7,3
; 8,3; 6,3; 13,3; 14,3; 15,3; 16,3; 5,4; 6,4; 7,4; 8,4; 13,4; 14,4; 15,4; 16,4;
6,7; 7,7; 8,7; 13,7; 14,7; 15,7; 16,7; 5,8; 6,8; 7,8; 8,8; 13,8; 14,8; 15,8; 16,
8; 6,11; 7,11; 8,11; 13,11; 14,11; 15,11; 16,11; 5,12; 6,12; 7,12; 8,12; 13,12;
14,12; 15,12; 16,12; 6,15; 7,15; 8,15; 13,15; 14,15; 15,15; 16,15; 5,16; 6,16; 7
,16; 8,16; 13,16; 14,16; 15,16; 16,16; 6,19; 7,19; 8,19; 13,19; 14,19; 15,19;

DRAW: number of turns played: 361
Usage Error: Lab3.exe and now no winning moves remain :(

>Lab3.exe Gomoku autoplayer
Error starting autoplayer
Please enter an autoplay type:
vertical, horizontal, diagonal_up, and diagonal_down will play (and win!)
automatically from a random position
random will randomly put pieces down until either the game is won
or all the positions are filled
stalemate will intentionally bring the game to a draw
Usage Error: Lab3.exe the game type was not properly specified

Sudoku has many of the same error messages/constraints.
Entering Lab4.exe Sudoku begins a Sudoku game regardless of capitalization. 
The player is then prompted to enter a 3 part move: x coordinate, y coordinate, square value
Entering this wrong, such as: "2,2" or "10" or   results in an error message:
This import is improperly formatted, please try again.
Entering too many inputs, such as "2, 2, 2, 2" gives: These are too many inputs. There should be 3 numbers: x, y and c. 
Entering an input that is out of bounds, such as "2, 10, 8" gives: These are too many inputs. There should be 3 numbers: x, y and c.
Entering a space that already has a value actually allows the player to change that value to whatever they input for S. This is because we thought that player would want the option of changing their moves rather than needing to start all over again. 

After all of these, the user is simply re-prompted to put in an input.

If the player has won, the game recognizes it and congratulates them and ends the game. Example: 

8||2|7|6||3|1|4||9|5|8||
-||-|-|-||-|-|-||-|-|-||
7||8|5|4||9|6|2||7|1|3||
-||-|-|-||-|-|-||-|-|-||
6||9|1|3||8|7|5||2|6|4||
=||=|=|=||=|=|=||=|=|=||
5||4|6|8||1|2|7||3|9|5||
-||-|-|-||-|-|-||-|-|-||
4||5|9|7||4|3|8||6|2|1||
-||-|-|-||-|-|-||-|-|-||
3||1|3|2||5|9|6||4|8|7||
=||=|=|=||=|=|=||=|=|=||
2||3|2|5||7|8|9||1|4|6||
-||-|-|-||-|-|-||-|-|-||
1||6|4|1||2|5|3||8|7|9||
-||-|-|-||-|-|-||-|-|-||
0||7|8|9||6|4|1||5|3|2||
=||=|=|=||=|=|=||=|=|=||
#||0|1|2||3|4|5||6|7|8||

moves so far:  0,5:4  1,5:6  2,5:8  3,5:1  5,5:7  8,5:5  0,6:9  4,6:7  5,6:5  7,
6:6  8,6:4  1,7:5  3,7:9  6,7:7  7,7:1  1,8:7  2,8:6  4,8:1  5,8:4  6,8:9  7,8:5
  8,8:8

You have won the game!

If the player has filled all the spaces but has not won, the mesage is the same but it indicates that they have finished but not won instead. 

-- Saving and Loading -- 

Expectd format of files
Game Name 
color display x y
color display x y

For all of these games, the player is only given the option to save if they are quitting midway through a game; if the someone has won or the game is a draw they are not given this option. But if they enter 'quit' while a game is still in progress, they are asked whether they want to save the game. If they say yes (if they say something other than "yes" or "no" they are re-prompted until they give one of those 2 answers), then we write all of the current gameboard pieces to an output file. We write the output file as follows; this is its expected format: 
Game Name 
color display x y
color display x y

...i.e. the name of the game and then a series of pieces.
If the player says no they do not want to save then, we write into the file NO DATA. 
Then when creating a new game, it works as follows for TicTacToe and Gomoku: 
We create a new game and pull in this outputted file; if we don't find any properly formatted pieces on that file (i.e. if the player chose not to save) then we simply create a new game which is blank. If we do find pieces, we create a gameboard and add those pieces.

Sudoku is a little more involved, because we never start with a blank gameboard, because that's not how Sudoku works. We need to start with some beginning inputs for the user to work around. So, if they chose not to save it, we simply upload this file of beginning inputs, which we have called sudokubackup. If they have saved, then their file should have the pieces stored in sudoku backup plus whichever plays the player made, so it loads that. 

	ERRORS
We did not deal with any especially large errors this time. Rather than getting stuck on any one thing, most of our difficulties came from more lower-level stuff, like checking indices, formatting error messages, etc.

	COPY CONTROL DESIGN DECISIONS
We did not use copy control features, because when we build our file, instead of constructing an empty vector of pieces we always try to load a saved game file when initializing a game, and we robustly fall back on a new empty vector if loading a game file fails. For us, this seemed to be the simplest and most efficient method of implementation.

Copy Constructor: constructor initializes an object by duplicating the const l-value that was passed to it by reference
It sets the new object's values from the parameter's. The parameter object is left unchanged. 
If we had implemented loadfile differently, this would be a way to make a new object of the gametype and then make a copy constructor and pass in the object that existed before the player quit and saved in the last round. 

Move Constructor: initializes an object by transferring the implementation from the r-value reference passed to it
This can be more efficient than copy construction; it just takes the implementation from the past object. If we had decided to implement our loadfile differently, we could have used a move constructor to create a new game from the old in an efficient manner (as it is, we only need to write the pieces). 

Copy-Assignment Operator: (re)sets an object’s value by duplicating the const l-value passed to it by reference. This could have been used for overwriting a tile in Sudoku. We made it so that players can simply overwrite by brute force -- if they enter x and y values where there is already a tile, their new S is moved into that file. For our project, this was a sustainable way of programming, so we did not need to use assignment operators. 


Move-Assignment Operator: (re)sets an object’s value by transferring the implementation from the r-value reference passed to it.
Since there is no allocation here, there are no exceptions to worry about. This could have been used for overwriting a tile in Sudoku. Again, we chose to implement overwrite differently. 

Destructor: A destructor manages the destruction of an object
These are useful for freeing up space if making a program that is discarding objects taking up a lot of memory space. 
Destructors run in the reverse order as constructors. 
