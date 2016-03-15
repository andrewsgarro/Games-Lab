//Gomoku.source
//Andrew Sgarro and Ethan Glassman
//andrew.sgarro@wustl.edu ethan.glassman@wustl.edu
//This file has all the particulars for the Gomoku game

//Expected file format
//Gomoku
//19 19
//color display x y
//EXAMPLE
//black b 1 1

#include "stdafx.h"
#include "Game.h"
#include "Autoplayer.h"
#include "IO.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <regex>
using namespace std;

int autoplay_counter = 1;

//overloads the << operator to print the game
ostream & operator << (ostream & o, const Gomoku &g) {
	vector<Game_Piece> gb = g.gameBoard;
	unsigned int current_longest = g.longest_name;

	for (int i = 20; i >= 0; i--) {
		for (unsigned int j = 0; j <= 21; j++) {
			if (j == 0) {
				string buffer = " ";
				string second_buffer = " ";
				
				if (i < 9){
					buffer = "  ";
				}
				
				if (i == 0) { o << buffer << " " << second_buffer << setw(current_longest); }
				else { o << buffer << i << second_buffer << setw(current_longest); }
			}
			else if (j == 1) { o << gb[i * 21 + (j - 1)].printOut; } //these are just different for the spacing
			else { 
				string third_buffer = "";
				if (j > 9){
					third_buffer = " ";
				}
				if (j == 9) { o << third_buffer << gb[i * 21 + (j - 1)].printOut; }
				else { o << third_buffer << gb[i * 21 + (j - 1)].printOut << " "; }
			}
		}
		o << endl;
	}
	o << "   ";

	//print the x-value axis
	for (int i = 0; i <= 20; i++) {
		if (i == 0) { o << " " << " " << setw(current_longest); }
		else { o << i << " " << setw(current_longest); }
	}
	return o;
}

//checks if someone has won
bool Gomoku::done() {

	int checkVal = 1;

	//check rows (1-20 are the playable squares)
	for (unsigned int i = 1; i < (Gomoku::right_x); i++) {  
		string temp = gameBoard[i * (Gomoku::right_x + 1) + 1].printOut;
		string nextTemp = gameBoard[i * (Gomoku::right_x + 1) + 2].printOut;
		for (unsigned int k = 2; k < (Gomoku::right_x + 1); k++) {
			if (temp != " " && temp == nextTemp) {
				checkVal++;
				if (checkVal == 5) { //in this case there are 5 pieces of the same type in a row, so someone has won
					if (temp == player1Name) { winner = 1; }
					else { winner = 2; }
					return true;
				}
			}
			else {
				checkVal = 1; //reset checkValue
			}
			temp = gameBoard[i * (Gomoku::right_x + 1) + k].printOut;
			nextTemp = gameBoard[i * (Gomoku::right_x + 1) + k + 1].printOut;
		}
	}

	checkVal = 1;

	//check columns
	for (unsigned int i = 1; i < (Gomoku::top_y); i++) {  
		string temp = gameBoard[(Gomoku::right_x + 1) + i].printOut;	
		string nextTemp = gameBoard[2 * (Gomoku::right_x + 1) + i].printOut;
		for (unsigned int k = 2; k < (Gomoku::top_y); k++) {
			if (temp != " " && temp == nextTemp) {
				checkVal++;
				if (checkVal == 5) {
					if (temp == player1Name) { winner = 1; }
					else { winner = 2; }
					return true;
				}
			}
			else {
				checkVal = 1;
			}
			temp = gameBoard[k * (Gomoku::right_x + 1) + i].printOut;
			nextTemp = gameBoard[(k + 1) * (Gomoku::right_x + 1) + i].printOut;
		}
	}
	
	checkVal = 1;

	//check diagonal: down & right
	for (unsigned int y_index = 5; y_index <= 20; ++y_index) {	//y values
		for (unsigned int x_index = 1; x_index <= 15; ++x_index) {
			string temp = gameBoard[y_index * 21 + x_index].printOut;
			string nextTemp = gameBoard[(y_index - 1) * 21 + x_index + 1].printOut;
			checkVal = 1;
			x = x_index;
			y = y_index;
			while (temp != " " && temp == nextTemp) {
				checkVal++;
				if (checkVal == 5) {
					if (temp == player1Name) { winner = 1; }
					else { winner = 2; }
					return true;
				}
				temp = gameBoard[(y - 1) * 21 + (x + 1)].printOut;
				nextTemp = gameBoard[(y - 2) * 21 + x + 2].printOut;
				y--;
				x++;
			}
		}
	}

	checkVal = 1;

	//check diagonal: up & right
	for (unsigned int y_index = 1; y_index <= 15; ++y_index) {	//y values
		for (unsigned int x_index = 1;  x_index <= 15; ++x_index) {
			string temp = gameBoard[y_index * 21 + x_index].printOut;
			string nextTemp = gameBoard[(y_index + 1) * 21 + x_index+1].printOut;
			checkVal = 1;
			x = x_index;
			y = y_index;
			while (temp != " " && temp == nextTemp) {
				checkVal++;
				if (checkVal == 5) {
					if (temp == player1Name) { winner = 1; }
					else { winner = 2; }
					return true;
				}
				temp = gameBoard[(y+1) * 21 + (x+1)].printOut;
				nextTemp = gameBoard[(y + 2) * 21 + x + 2].printOut;
				y++;
				x++;
			}
		}
	}

	return false;
}

//checks if there are no more plays available (and nobody has won)
bool Gomoku::stalemate() {

	for (int i = 1; i < 20; i++) {
		for (int k = 1; k < 20; k++) {
			if (gameBoard[i * 21 + k].printOut == " ") {
				return false;
			}
		}
	}
	bool winner = done();
	if (winner) return false;

	return true;
}

//Prompt asks for user input and extracts x,y coordinates into the referenced ints
int Gomoku::prompt(unsigned int & x, unsigned int & y){
	cout << "Type coordinates (x,y) to play a piece, or quit to end the game" << endl;
	cout << "" << endl;
	
	string user_input;
	if (autoplay!="false"){ //Testing code.  Computer performs all the inputs
		user_input = autoplay_function(autoplay_counter, player,gameBoard,autoplay);
		if (player == playerNum::player1){
			++autoplay_counter;
		}
	}
	else{ //Otherwise, the humans do all the input
		getline(cin, user_input);
	}

	if (user_input == "quit"){
		while (true){
			cout << "Would you like to save your game?" << endl;
			cout << "Please enter yes or no" << endl;
			getline(cin, user_input);
			if (lowercase(user_input) == "yes"){
				save_file("Gomoku", this->gameBoard, true);
				return quit;
			}
			else if(lowercase(user_input) == "no"){
				save_file("Gomoku", this->gameBoard, false);
				return quit;
			}
		}
	}
	else{
		//Replace comma with space
		replace(user_input.begin(), user_input.end(), ',', ' ');
		//Wrap input in an isstringstream, and convert to int
		istringstream iss(user_input);
		//Check that there are the correct number of inputs
		if (!(iss >> x) || !(iss >> y)){
			return usagemessage(exe_name, error_message_string(failToParse));
		}
		int too_many;
		if (iss >> too_many){
			return usagemessage(exe_name, error_message_string(tooManyInputs));
		}
		if (!((this->left_x) <= x && x <= (this->right_x) && (this->bottom_y) <= y  && y <= (this->top_y))){
			return usagemessage(exe_name, error_message_string(outOfBounds));
		}
		if (gameBoard[21 * y + x].printOut != " ") {
			return usagemessage(exe_name, error_message_string(spaceOccupied));
		}
		else{
			return success;
		}

	}
}

//this handles switching turns between player 1 and 2
int Gomoku::turn() {
	unsigned int a;
	unsigned int b;
	int moveResult;
	bool validMove = false;
	if (player == playerNum::player1) {

		cout << "Player 1's turn (" << Gomoku::player1Name << ")" << endl;

		moveResult = prompt(a, b);

		if (moveResult == quit) {
			return quit;
		}
		if (moveResult == success) {
			Game_Piece g;
			g.piecePlayer = playerNum::player1;
			g.printOut = Gomoku::player1Name;
			g.pieceColor = Gomoku::player1Color;
			if (g.printOut.length() > BaseGame::longest_name){
				BaseGame::longest_name = g.printOut.length();
			}
			setPiece(g, a, b); //set valid move on gameboard

			BaseGame::player1Moves += (to_string(a) + "," + to_string(b) + "; ");

			cout << endl;
			if (this->autoplay == "false" || done()){
				cout << *this << endl; //print gameboard
				cout << endl;
				cout << "Player 1's moves so far" << player1Moves << endl;
				cout << endl;
			}
			
			player = playerNum::player2;
			turns++;
		}
	}
	else {
		cout << "Player 2's turn (" << Gomoku::player2Name << ")" << endl;

		moveResult = prompt(a, b);

		if (moveResult == quit) {
			return quit;
		}
		if (moveResult == success) {
			Game_Piece g;
			g.piecePlayer = playerNum::player2;
			g.printOut = Gomoku::player2Name;
			g.pieceColor = Gomoku::player2Color;
			if (g.printOut.length() > BaseGame::longest_name){
				BaseGame::longest_name = g.printOut.length();
			}
			setPiece(g, a, b);

			BaseGame::player2Moves += (to_string(a) + "," + to_string(b) + "; ");

			cout << endl;
			if (this->autoplay == "false" || done()){
				cout << *this << endl; //print gameboard
				cout << endl;
				cout << "Player 2's moves so far" << player2Moves << endl;
				cout << endl;
			}

			player = playerNum::player1;
			turns++;
		}
	}
	return success;
}

//this method allows us to set pieces on the gameboard
void Gomoku::setPiece(Game_Piece g, unsigned int a, unsigned int b) {
	gameBoard[21 * b + a] = g;
}

//this method allows us to play the Gomoku game with a Gomoku object
int Gomoku::play(){
	try{
		gameBoard = load_file("Gomoku.txt", player);
	}
	catch (...){
		for (unsigned int i = 0; i < (21 * 21); i++) {
			Game_Piece null;
			null.printOut = ' ';
			null.piecePlayer = invalid_num;
			null.pieceColor = empty_color;
			gameBoard.push_back(null);
		}
	}

	print(); //prints the gameboard
	cout << "" << endl; 
	cout << "" << endl;

	while (true) {
		int t = turn();

		if (done()) {
			save_file("Gomoku", this->gameBoard, false); //Write empty game after win
			if (winner == 1) {
				cout << "Player 1 (" << Gomoku::player1Name << ") won the game!" << endl;
			}
			else {
				cout << "Player 2 (" << Gomoku::player2Name << ") won the game!" << endl;
			}
			return success;
		}

		if (stalemate()) {
			cout << "DRAW: number of turns played: " << turns;
			return usagemessage(exe_name, error_message_string(draw));
		}

		if (t == quit) return usagemessage(exe_name, error_message_string(quit));
	}

	return usagemessage(exe_name, error_message_string(playLoopError)); // should never get here
}