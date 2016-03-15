// Ethan Glassman and Andrew Sgarro
// ethan.glassman@wustl.edu andrew.sgarro@wustl.edu
// Lab 4
// gamepieces.cpp contains functions 
// build_pieces_map to build a map allowing piece_color values and the corresponding string names to be related
// piececolor_string to output string name given a piece_color
// piececolor_enum to give piece_color value given a string

#include "stdafx.h"
#include "GamePieces.h"
#include <string>
#include "errors.h"

#include <map>

using namespace std;

//Map of enums, string values
map<piece_color, string> string_color_map;

//Relate piece_color values and the corresponding string names
void build_pieces_map(){
	string_color_map.insert({ red, "red" });
	string_color_map.insert({ blue, "blue" });
	string_color_map.insert({ black, "black" });
	string_color_map.insert({ white, "white" });
	string_color_map.insert({ sudoku, "sudoku" });
	string_color_map.insert({ invalid_color, "invalid" });
	string_color_map.insert({ empty_color, " " });
}

//Return string in lowercase given corresponding piece_color in constant time
string piececolor_string(piece_color piece){
	return lowercase(string_color_map[piece]);
}

//Return piece_color value given corresponding string
piece_color piececolor_enum(string piece){
	//Look through map of piece_color and strings in linear time
	for (map<piece_color, string>::iterator i = string_color_map.begin(); i != string_color_map.end(); ++i){
		//If string, or corresponding lowercase string given is in map
		if (i->second == lowercase(piece)){
			//Corresponding piece_color
			return i->first;
		}
	}
	//Invalid if string given is not in map
	return invalid_color;
}

//Map of enums, string values
map<piece_display, string> string_display_map;

//Relate piece_color values and the corresponding string names
void build_piece_display_map(){
	string_display_map.insert({ X, "X" });
	string_display_map.insert({ O, "O" });
	string_display_map.insert({ B, "W" });
	string_display_map.insert({ W, "B" });
	string_display_map.insert({ invalid_display, "invalid" });
	string_display_map.insert({ empty_display, " " });
}

//Return string in lowercase given corresponding piece_color in constant time
string piecedisplay_string(piece_display piece){
	return string_display_map[piece];
}

//Return piece_color value given corresponding string
piece_display piece_display_enum(string piece){
	//Look through map of piece_color and strings in linear time
	for (map<piece_display, string>::iterator i = string_display_map.begin(); i != string_display_map.end(); ++i){
		//If string, or corresponding lowercase string given is in map
		if (i->second == lowercase(piece)){
			//Corresponding piece_color
			return i->first;
		}
	}
	//Invalid if string given is not in map
	return invalid_display;
}

//Map of enums, string values
map<playerNum, string> string_player_map_tictactoe;
map<playerNum, string> string_player_map_gomoku;

void build_player_map_tictactoe(){
	string_player_map_tictactoe.insert({ player1, "X" });
	string_player_map_tictactoe.insert({ player2, "O" });
}

playerNum playernum_enum_tictactoe(string player_string){
	//Look through map of piece_color and strings in linear time
	for (map<playerNum, string>::iterator j = string_player_map_tictactoe.begin(); j != string_player_map_tictactoe.end(); ++j){
		//If string, or corresponding lowercase string given is in map
		if (j->second == (player_string)){
			//Corresponding piece_color
			return j->first;
		}
	}
	//Invalid if string given is not in map
	return invalid_num;
}

string player_string_tictactoe(playerNum player_num){
	return string_player_map_tictactoe[player_num];
}

void build_player_map_gomoku(){
	string_player_map_gomoku.insert({ player1, "B" });
	string_player_map_gomoku.insert({ player2, "W" });
}

playerNum playernum_enum_gomoku(string player_string){
	//Look through map of piece_color and strings in linear time
	for (map<playerNum, string>::iterator j = string_player_map_gomoku.begin(); j != string_player_map_gomoku.end(); ++j){
		//If string, or corresponding lowercase string given is in map
		if (j->second == (player_string)){
			//Corresponding piece_color
			return j->first;
		}
	}
	//Invalid if string given is not in map
	return invalid_num;
}

string player_string_gomoku(playerNum player_num){
	return string_player_map_gomoku[player_num];
}

