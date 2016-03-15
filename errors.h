//Andrew Sgarro and Ethan Glassman
//andrew.sgarro@wustl.edu ethan.glassman@wustl.edu
// Lab 4
// errors.h: single location for useful values to reside.
// and enum error_messages generating integer codes to return for sucessful or unsucessful program implementation
// Describes functions found in errors.cpp.
// usagemessage for outputting to the command line
// build_errors_map to build a map allowing error codes and the corresponding string messages to be related
// error_message_string to return the correct string error message given a error message int
// error_message_int to return the correct error message int given a string error message

#ifndef ERRORS_H
#define ERRORS_H

#include "stdafx.h"
#include <map>
#include <string>

using namespace std;

//integer codes to return for sucessful or unsucessful program implementation
enum error_messages {
	success, program_name_wrong,failToParse,not_enough_arguements,auto_not_specified,
	tooManyInputs, tooFewInputs,quit, spaceOccupied, draw, 
	playLoopError, outOfBounds, unknownerror,fail_to_create_new,nofile,
	game_null_ptr, not_null_ptr,cant_open_out, bad_save,
	game_name_extract_error,wrong_piece_count};

//prints out error messages to terminal and returns error code
// usagemessage for outputting to the command line
int usagemessage(string programname, string messagestring);

//build a map allowing error codes and the corresponding string messages to be related
void build_errors_map(string input_file_name);

//return the correct string error message given a error message int
string error_message_string(error_messages message);

//return the correct error message int given a string error message
int error_message_int(string message);

//converts given string to lowercase
string lowercase(string toLowerCase);

#endif