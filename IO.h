// Ethan Glassman
// ethan.glassman@wustl.edu
// This stores information relevant to saving and loading files, so that players have the option of saving a game when quitting midway through and then returning to it later 

#ifndef IO_H
#define IO_H


#include "stdafx.h"
#include <vector>
#include "Game.h"

using namespace std;

int gameType(ifstream & ifs, string & game_type);
int current_player(ifstream & ifs, string & player);

int buildboard(ifstream & ifs, unsigned int & board_horiz_dim, unsigned int & board_vert_dim); //Extracts board dimensions

int buildpieces(ifstream & ifs, vector<Game_Piece> & pieces_vector, unsigned int & board_horiz_dim, unsigned int & board_vert_dim, string & game_name, unsigned int & player1_pieces, unsigned int & player2_pieces); //Extracts piece details

void print_board(vector<Game_Piece> & pieces_vector, unsigned int & board_horiz_dim, unsigned int & board_vert_dim); //Displays pieces to command line

vector<Game_Piece> load_file(string input_file, playerNum & first_player); //loads pieces from given file

void save_file(string output_file, vector<Game_Piece> piece_vector, bool save); //saves pieces to specified output file

#endif