// Game.cpp : Defines the entry point for the console application.
// Andrew Sgarro and Ethan Glassman
// andrew.sgarro@wustl.edu	ethan.glassman@wustl.edu
// here we define the constructor for the baseclass BaseGame, and also its method that determines which game a user is requesting
// and then creates a game of that type, and a smartpointer pointing to it

#include "stdafx.h"
#include "Game.h"
#include <set>

shared_ptr<BaseGame> BaseGame::game = nullptr;
//We need these to prevent corruption of the files with accidental lowercase
string Gomoku::player1Name = "B";
string Gomoku::player2Name = "W";
piece_color Gomoku::player1Color = black;
piece_color Gomoku::player2Color = white;
string TicTacToe::player1Name = "X";
string TicTacToe::player2Name = "O";
piece_color TicTacToe::player1Color = red;
piece_color TicTacToe::player2Color = blue;

string BaseGame::player1Moves;
string BaseGame::player2Moves;

BaseGame::BaseGame(int xval, int yval, int turnsval, int longestnameval, int p1movesval, int p2movesval, playerNum playerval, int winnerval) {
	x = xval;
	y = yval;
	turns = turnsval;
	longest_name = longestnameval;
	player1Moves = p1movesval;
	player2Moves = p2movesval;
	player = playerval;
	winner = winnerval;
}

set<string> autoplay_options = { "vertical", "collumns", "horizontal", "rows", "diagonal_up","diagonal_down","random","stalemate","draw"};

//deciphers which game the user wants to play based on command line arguments
void BaseGame::game_type(int argc, char * argv[]){
	if (game != nullptr){
		throw not_null_ptr;
	}
	else{
		if (argc >= arrayIndex::numArgs){
			exe_name = argv[arrayIndex::programName];
			string name = argv[arrayIndex::game_name]; //determine input name from input arguments
			if (lowercase(name) == "tictactoe") {
				try {
					TicTacToe *t = new TicTacToe();
					auto tic_tac_toe_ptr = make_shared<TicTacToe>(*t);
					game = tic_tac_toe_ptr;
				}
				catch (...) {
					throw;
				}
			}
			else if (lowercase(name) == "sudoku") {
				try {
					Sudoku *s = new Sudoku();
					auto sudoku_ptr = make_shared<Sudoku>(*s);
					game = sudoku_ptr;
				}
				catch (...) {
					throw;
				}
			}
			else if (lowercase(name) == "gomoku") {
				try {
					Gomoku *g = new Gomoku();
					if (argc > arrayIndex::autoplay_type){
						string play_type = argv[arrayIndex::autoplay_type - 1];
						if (lowercase(play_type) == "autoplay" || lowercase(play_type) == "autoplayer"){
							string autoplay_name = lowercase(argv[arrayIndex::autoplay_type]);
							if (autoplay_options.find(autoplay_name) != autoplay_options.end()){
								g->autoplay = autoplay_name;
							}
							else{
								cout << error_message_string(auto_not_specified) << endl;
								g->autoplay = "false";
							}
						}
					}
					else{
						g->autoplay = "false";
					}
					auto gomoku_ptr = make_shared<Gomoku>(*g);
					game = gomoku_ptr;
				}
				catch (...) {
					throw;
				}
			}
			else{
				throw invalid_argument(error_message_string(program_name_wrong));
			}
		}
		else{
			throw invalid_argument(error_message_string(not_enough_arguements));
		}
	}
}