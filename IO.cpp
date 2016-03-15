// IO.cpp
// Ethan Glassman and Andrew Sgarro
// ethan.glassman@wustl.edu andrew.sgarro@wustl.edu
// Lab 4 
// buildboard to extract board dimensions
// buildpieces to extract piece details
// print_board to output the pieces to terminal

#include "stdafx.h"
#include "IO.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

set<string> games = { "Gomoku","TicTacToe", "Sudoku" }; //valid gametype inputs

//checks for gameType
int gameType(ifstream & ifs, string& game_type){
	string line;
	//Error if no line exists
	if (!getline(ifs, line)){
		throw game_name_extract_error;
	}

	game_type = line;
	if (games.find(game_type) == games.end()){
		throw game_name_extract_error;
	}

	return success;
}

//Expected format of files
//Game name
//width height
//color display x y

//adds the pieces from the input stream into the board
int buildpieces(ifstream & ifs, vector<Game_Piece> & pieces_vector, unsigned int & board_horiz_dim, unsigned int & board_vert_dim, 
	string &game_type, unsigned int & player1_pieces, unsigned int & player2_pieces){
	string line;
	int num_pieces = 0;
	while (getline(ifs, line)){
		istringstream issline(line);

		string piece_color_string;
		issline >> piece_color_string;  //Example Black, White
		piece_color piece_color_def = piececolor_enum(piece_color_string);

		//Skip to next line if piece color is not enumerated
		if (piece_color_def == invalid_color){
			continue;
		}
		
		playerNum player_num = invalid_num;

		string piece_display; //Example X, O
		issline >> piece_display;
		

		if (game_type == "Gomoku"){
			
			if (piece_display == lowercase(Gomoku::player1Name)){
				piece_display = Gomoku::player1Name;
			}
			if (piece_display == lowercase(Gomoku::player2Name)){
				piece_display = Gomoku::player2Name;
			}
			player_num = playernum_enum_gomoku(piece_display);
			if (player_num == player1 && piece_color_def != Gomoku::player1Color){
				continue;
			}
			else if (player_num == player2 && piece_color_def != Gomoku::player2Color){
				continue;
			}
		}

		else if (game_type == "TicTacToe"){
			if (piece_display == lowercase(TicTacToe::player1Name)){
				piece_display = TicTacToe::player1Name;
			}
			if (piece_display == lowercase(TicTacToe::player2Name)){
				piece_display = TicTacToe::player2Name;
			}
			player_num = playernum_enum_tictactoe(piece_display);

			if (player_num == player1 && piece_color_def != TicTacToe::player1Color){
				continue;
			}
			else if (player_num == player2 && piece_color_def != TicTacToe::player2Color){
				continue;
			}
		}

		else if (game_type == "Sudoku"){
			player_num = player1;
		}
		else{
			continue;
		}

		

		unsigned int horiz_position;
		issline >> horiz_position;
		unsigned int vert_position;
		issline >> vert_position;

		if (game_type != "Sudoku"){
			//Skip any pieces outside of the board dimensions
			if (!(horiz_position <= board_horiz_dim - 1) || !(horiz_position > 0) || !(vert_position < board_vert_dim) || !(vert_position > 0)){
				continue;
			}
		}
		else{
			//Skip any pieces outside of the board dimensions
			if (!(horiz_position < board_horiz_dim) || !(horiz_position >= 0) || !(vert_position < board_vert_dim) || !(vert_position >= 0)){
				continue;
			}
		}

		if (pieces_vector[(board_horiz_dim)*vert_position + horiz_position].printOut != " "){
			continue;
		}

		if (player_num == player1){
			++player1_pieces;
			BaseGame::player1Moves += (to_string(horiz_position) + "," + to_string(vert_position) + "; ");
		}
		else{
			++player2_pieces;
			BaseGame::player2Moves += (to_string(horiz_position) + "," + to_string(vert_position) + "; ");
		}

		Game_Piece piece;
		piece.pieceColor = piece_color_def;
		piece.printOut = piece_display;
		piece.piecePlayer = player_num;

		//Store well-formed piece in pieces_vector in a known location based on piece position
		pieces_vector[(board_horiz_dim)*vert_position + horiz_position] = piece;
		++num_pieces;

	}
	return success;
}

//Expected format of files
//Game name
//color display x y

//loads the file saved at the last quit
vector<Game_Piece> load_file(string input_file,playerNum & first_player){
	//Open inputstring as a file in an ifstream
	ifstream ifs;
	ifs.open(input_file);

	if (!ifs.is_open()){ //Error if the file cannot be opened
		throw usagemessage(exe_name, error_message_string(error_messages(nofile)));
	}

	string game_type;
	try{
		int name = gameType(ifs, game_type);
	}
	catch(...){  //If we don't have a good game name we're just going to give up on loading the file
		throw game_name;
	}

	unsigned int board_horiz_dim;
	unsigned int board_vert_dim;

	//It's silly to error check these dimensions, we might as well just define them
	if (game_type == "Gomoku"){
		board_horiz_dim = Gomoku::horiz; 
		board_vert_dim = Gomoku::vert;
	}

	if (game_type == "TicTacToe"){
		board_horiz_dim = TicTacToe::horiz;
		board_vert_dim = TicTacToe::vert;
	}

	if (game_type == "Sudoku"){
		board_horiz_dim = Sudoku::horiz;
		board_vert_dim = Sudoku::vert;
	}

	//Generate a vector with a null piecs for every possible spot on the board
	vector<Game_Piece> game_pieces;
	int numpieces = board_horiz_dim*board_vert_dim;
	Game_Piece null;
	null.printOut = ' ';
	null.piecePlayer = invalid_num;
	null.pieceColor = empty_color;

	while (numpieces != 0){
		game_pieces.push_back(null);
		--numpieces;
	}

	//Extract real pieces from the file and put them into the vector
	unsigned int player1_pieces = 0;
	unsigned int player2_pieces = 0;
	int pieces = buildpieces(ifs, game_pieces, board_horiz_dim, board_vert_dim, game_type,player1_pieces,player2_pieces);

	//Pick player based on how many pieces each player has on the board, to ensure that the play count will stay the same
	first_player = player1;
	if (abs(int(player1_pieces) - int(player2_pieces)) > 1 || abs(int(player2_pieces) - int(player1_pieces)) > 1){
		if (game_type != "Sudoku"){ //Throw an error if one player has 2+ more pieces than the other and we're not playing sudoku
			cout << "Too many pieces for one player, probably a corrupted file, we're going to build a new board" << endl;
			throw(wrong_piece_count);
		}
	}
	else {
		if (player1_pieces > player2_pieces){
			first_player = player2;
		}
		else{
			first_player = player1;
		}
	}
	if (pieces != success){ //Error if there are no pieces 
		throw usagemessage(exe_name, error_message_string(error_messages(pieces)));
	}

	return game_pieces;
}

//saves a file if the game is not over and the user wants to save
void save_file(string output_name, vector<Game_Piece> piece_vector, bool save){
	ofstream myfile;
	string piece_display;
	myfile.open(output_name+".txt", ios::out);
	if (!myfile.is_open()){
		throw cant_open_out;
	}
	else{
		myfile << output_name << "\n";
	}
	if (games.find(output_name) == games.end()){
		myfile << "BAD DATA" << endl;	//signals a wrong filename
		myfile.close();
		throw bad_save;
	}
	
	if (save == true){
		unsigned int board_horiz_dim;
		unsigned int board_vert_dim;
		if (output_name == "Gomoku"){
			board_horiz_dim = Gomoku::horiz - 2;
			board_vert_dim = Gomoku::vert - 2;
		}

		if (output_name == "TicTacToe"){
			board_horiz_dim = TicTacToe::horiz - 2;
			board_vert_dim = TicTacToe::vert - 2;
		}

		if (output_name == "Sudoku"){
			board_horiz_dim = Sudoku::horiz - 2;
			board_vert_dim = Sudoku::vert - 2;
		}
		for (unsigned int i = 0; i <= board_horiz_dim + 1; i++) { //X
			for (unsigned int j = 0; j <= board_vert_dim + 1; j++) { //Y 
				if (piece_vector[i * (board_horiz_dim + 2) + j].printOut != " "){
					if (!myfile.is_open()){
						throw cant_open_out;
					}
					else{
						//write piece to appropriate game file
						if (output_name == "TicTacToe"){
							piece_display = player_string_tictactoe(piece_vector[i * (board_horiz_dim + 2) + j].piecePlayer);
						}
						else if (output_name == "Gomoku"){
							piece_display = player_string_gomoku(piece_vector[i * (board_horiz_dim + 2) + j].piecePlayer);
						}
						else if (output_name == "Sudoku"){
							piece_display = (piece_vector[i * (board_horiz_dim + 2) + j]).printOut;
						}
						myfile << piececolor_string(piece_vector[i * (board_horiz_dim + 2) + j].pieceColor) << " "
							<< piece_vector[i * (board_horiz_dim + 2) + j].printOut << " "
							<< j << " " << i << endl;
					}
				}
			}
		}
	}
	else{
		myfile << "BAD DATA" << endl;
	}

}