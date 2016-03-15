//errors.cpp
//Andrew Sgarro and Ethan Glassman
//andrew.sgarro@wustl.edu ethan.glassman@wustl.edu
// Lab 4
// errors.cpp contains lots of functions for error handling
// usagemessage for outputting to the command line
// build_errors_map to build a map allowing error codes and the corresponding string messages to be related
// error_message_string to return the correct string error message given a error message int
// error_message_int to return the correct error message int given a string error message

#include "stdafx.h"
#include "errors.h"
#include <map>
#include "Game.h"
#include <string>
#include <iostream>

using namespace std;

//prints out error messages to terminal and returns error code
int usagemessage(string programname, string messagestring){
	int error_enum = error_message_int(messagestring); //Given string, find associated integer error code
	cout << "Usage Error: " << programname << messagestring << endl; //Print error code
	return error_enum;
}

//map allowing error codes and the corresponding string messages to be related
map<error_messages, string> error_messages_map;

//Relate error_messages values and the corresponding string error messages
void build_errors_map(string input_file_name){
	error_messages_map.insert({ success, " was sucessful." });
	error_messages_map.insert({ program_name_wrong, " the game type was not properly specified.\n  You must pick a game type from Gomoku, Sudoku, or TicTacToe." });
	error_messages_map.insert({ failToParse, " please input a valid string, in the format(int, int)" });		
	error_messages_map.insert({ not_enough_arguements, " requires exactly two inputs.\n  " + exe_name + " and a game type from Gomoku, Sudoku, or TicTacToe." });
	error_messages_map.insert({ auto_not_specified, "Error starting autoplayer\n Please enter an autoplay type:\n vertical, horizontal, diagonal_up, and diagonal_down will play (and win!)\n automatically from a random position\n random will randomly put pieces down until either the game is won\n or all the positions are filled\n stalemate will intentionally bring the game to a draw." });
	error_messages_map.insert({ tooManyInputs, " you entered too many integers.  Please input a valid string, in the format(int, int)" });
	error_messages_map.insert({ tooFewInputs, " you did not enter enough inputs. Please enter (int, int, int) for Sudoku or (int, int) for TicTacToe or Gomoku" });
	error_messages_map.insert({ quit, " the user has quit." });
	error_messages_map.insert({ spaceOccupied, " this space is already occupied, please choose an empty space." });
	error_messages_map.insert({ draw, " and now no winning moves remain :( " });
	error_messages_map.insert({ playLoopError, " had an error with the play loop. " });
	error_messages_map.insert({ outOfBounds, " this space is out of bounds, please choose a valid space." });
	error_messages_map.insert({ unknownerror, " had an unknown error.  Please double check your inputs." });
	error_messages_map.insert({ fail_to_create_new, " had an error creating a new BaseGame." });
	error_messages_map.insert({ nofile, " had an error opening the requested file." });
}

//return the correct string error message given a error message int
string error_message_string(error_messages message){
	return error_messages_map[message];
}

//return the correct error message int given a string error message
int error_message_int(string message){
	for (map<error_messages, string>::iterator i = error_messages_map.begin(); i != error_messages_map.end(); ++i){
		if (i->second == message){
			return i->first;
		}
	}
	return unknownerror;
}

//converts given string to lowercase
string lowercase(string toLowerCase){
	string lowercase;
	string::iterator it;
	for (it = toLowerCase.begin(); it < toLowerCase.end(); ++it){
		char check = *it;
		if (check<'Z' && check>'A'){ //If uppercase char exists
			check = check - ('Z' - 'z'); //Use char math to turn it to lowercase
		}
		lowercase += check; //Build up new string char by char
	}
	return lowercase;
}