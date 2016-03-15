// Lab4.cpp : Defines the entry point for the console application.
// Andrew Sgarro and Ethan Glassman
// andrew.sgarro@wustl.edu	ethan.glassman@wustl.edu

#include "stdafx.h"
#include "IO.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
bool autoplay;

int main(int argc, char * argv[])
{
	build_errors_map(argv[programName]);
	try{
		BaseGame::game_type(argc, argv); //identifies the gametype 
	}
	catch (invalid_argument a) { //catch errors and print appropriate usage message
		return usagemessage(argv[programName], a.what());
	}
	catch (bad_alloc e) {
		return usagemessage(argv[programName], error_message_string(fail_to_create_new));
	}
	catch (...) {
		return usagemessage(argv[programName], error_message_string(unknownerror));
	}
	shared_ptr<BaseGame> gamePointer = BaseGame::instance();

	build_pieces_map();
	build_player_map_tictactoe();
	build_player_map_gomoku();

	if (gamePointer == nullptr){
		return usagemessage(argv[programName], error_message_string(program_name_wrong));
	}
	else{
		gamePointer->play(); //play the game specified by game_type
	}
}

