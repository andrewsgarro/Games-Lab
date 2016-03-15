//GamePieces.h
//Andrew Sgarro and Ethan Glassman
//andrew.sgarro@wustl.edu ethan.glassman@wustl.edu
//this header stores the colors for game pieces, the functions to derive the enum value from a color and to return a lowercase string from a color.
//it also defines a game_piece struct which is how we create individual game pieces, and game piece string for each individual game

#ifndef GAMEPIECES_H
#define GAMEPIECES_H

#include  "stdafx.h"
#include <vector>
#include <iostream>
#include "Header.h"
using namespace std;

//Types of pieces
enum piece_display { X, O, B, W , invalid_display, empty_display};
enum piece_color { black, white, red, blue, sudoku, invalid_color, empty_color };

//Players who could be in the game
enum playerNum{player1, player2, invalid_num};

//Features of the game piece
struct Game_Piece {
	piece_color pieceColor;
	playerNum piecePlayer;
	string printOut;
};

enum pieceType getPieceType(Game_Piece); 

void build_player_map_tictactoe();
void build_pieces_map();
void build_player_map_gomoku();
void build_piece_display_map();

//return string given corresponding piece_color
string piececolor_string(piece_color piece);

//return piece_color value given corresponding string
piece_color piececolor_enum(string piece);

//return string given corresponding player_num
string player_string_gomoku(playerNum player_num);
string player_string_tictactoe(playerNum player_num);

//return player_num value given corresponding string
playerNum playernum_enum_gomoku(string player_display_string);
playerNum playernum_enum_tictactoe(string player_display_string);

//Return string in lowercase given corresponding piece_color in constant time
string piecedisplay_string(piece_display piece);

//Return piece_color value given corresponding string
piece_display piece_display_enum(string piece);


#endif