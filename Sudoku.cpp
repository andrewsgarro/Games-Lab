//Sudoku.cpp
// Ethan Glassman and Andrew Sgarro
// ethan.glassman@wustl.edu andrew.sgarro@wustl.edu
// Lab 4 
//defines the play, stalemate, done, prompt and turn methods for Sudoku. Overloads the << operator to print its gameboard

#include "stdafx.h"
#include "IO.h"
#include "errors.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>
using namespace std;

//overloading the << operator to print the Sudoku gameboard
ostream & operator << (ostream &o, const Sudoku &s) {

	vector<Game_Piece> gb = s.gameBoard;
	unsigned int current_longest = s.longest_name; //this isn't really necessary because its always just a 1-digit number, so we can consider deleting?

	for (int i = 8; i >= 0; i--) {

		for (unsigned int j = 0; j <= 9; j++) {
			if (j == 0) { o << i; }
			else if (gb[i * 9 + (j - 1)].printOut == " ") { o << " "; } //we will use 10 as code for empty
			else { o << gb[i * 9 + (j - 1)].printOut << setw(current_longest); }

			//vertical border
			if (j == 0 || j == 3 || j == 6 || j == 9) { o << "||"; }
			else { o << "|"; }
		}

		//horizontal border
		o << endl;
		if (i == 6 || i == 3 || i == 0) {
			for (int g = 0; g <= 9; g++) {
				if (g == 0 || g == 3 || g == 6 || g == 9) { o << "=||"; }
				else { o << "=|"; }
			}
		}
		else {
			for (int d = 0; d <= 9; d++) {
				if (d == 0 || d == 3 || d == 6 || d == 9) { o << "-||"; }
				else { o << "-|"; }
			}

		}
		o << endl;
	}

	o << "#||"; 
	//print labels of x axis
	for (int k = 0; k < 9; k++) {
		o << k;
		if (k == 2 || k == 5 || k == 8) { o << "||"; }
		else { o << "|"; }
	}
	return o;
}

//checks if the player has won,.
bool Sudoku::done() {

	int checker[11]; 	 //goes up to 11 because 10 is the empty value

	//check columns 
	for (int c = 0; c < 9; c++) {	//cols
		for (int j = 0; j < 11; j++) {
			checker[j] = 0;
		}
		for (int r = 0; r < 9; r++) { //rows
			if (gameBoard[r * 9 + c].printOut != " "){
				int a = stoi(gameBoard[r * 9 + c].printOut);
				checker[stoi(gameBoard[r * 9 + c].printOut)]++;
			}
		}
		for (int m = 1; m <10; m++) {
			if (checker[m] != 1) { return false; }
		}
	}

	//check rows
	for (int r = 0; r < 9; r++) {	//rows
		for (int j = 0; j < 11; j++) {
			checker[j] = 0;
		}
		for (int c = 0; c < 9; c++) { //cols
			checker[stoi(gameBoard[r * 9 + c].printOut)]++;
		}
		for (int m = 1; m < 10; m++) {
			if (checker[m] != 1) { return false; }
		}
	}

	//check all 9 squares 
	for (int y = 0; y < 9; y += 3) {
		for (int x = 0; x < 9; x += 3) {
			for (int j = 0; j < 11; j++) {
				checker[j] = 0;
			}
			for (int r = 0; r < 3; r++) {
				for (int c = 0; c < 3; c++) {
					checker[stoi(gameBoard[((y + r) * 9) + (x + c)].printOut)]++;
				}
			}
			for (int m = 1; m < 10; m++) {
				if (checker[m] != 1) { return false; }
			}
		}
	}
	return true;
}

//puts a piece on the Sudoku gameboard
void Sudoku::setPiece(int s, unsigned int x, unsigned int y) {
	Game_Piece g;
	g.pieceColor = sudoku;
	g.printOut = to_string(s);
	gameBoard[9 * y + x] = g;
}

//it seemed like they wanted this to be a sort of combo of prompt/turn from the others -- so this asks for input, evaluates it and quits or places a  piece on the board accordingly
void Sudoku::prompt(unsigned int & x, unsigned int & y, unsigned int &s){
	cout << "Type coordinates (x, y, s) to play a piece of value s in position (x,y). Or type quit to end the game" << endl;
	cout << "" << endl;
	string user_input;
	getline(cin, user_input);
	if (user_input == "quit"){
		while (true){
			cout << "Would you like to save your game?" << endl;
			cout << "Please enter yes or no" << endl;
			getline(cin, user_input);
			if (lowercase(user_input) == "yes"){
				save_file("Sudoku", this->gameBoard, true);
				throw error_messages::quit;
			}
			else if(lowercase(user_input) == "no"){
				gameBoard = load_file("sudoku0.txt", player);
				save_file("Sudoku", this->gameBoard, true); //We need to load the original file :/
				throw error_messages::quit;
			}
		}
	}
	else{
		//Replace comma with space
		replace(user_input.begin(), user_input.end(), ',', ' ');
		//Wrap input in an isstringstream, and convert to int
		istringstream iss(user_input);
		//Check that there are the correct number of inputs
		int too_many;

		if (!(iss >> x) || !(iss >> y) || !(iss >> s)){
			cout << endl <<  "This import is improperly formatted, please try again." << endl << endl;
			throw error_messages::tooFewInputs;
		} else if (iss >> too_many){
			cout << endl <<  "These are too many inputs. There should be 3 numbers: x, y and c." << endl << endl;
			throw error_messages::tooManyInputs;
		} else if (!((this->left_x) <= x && x <= (this->right_x) && (this->bottom_y) <= y  && y <= (this->top_y))){
			cout << endl << "This is out of bounds. Please keep x and y within 0 - 8 (inclusive)." << endl << endl;
			throw error_messages::outOfBounds;
		} else{
			setPiece(s, x, y);
			BaseGame::player1Moves += (to_string(x) + "," + to_string(y) + ":" + to_string(s) + "  ");
			cout << endl;
			cout << *this << endl;
			cout << endl;
			cout << "moves so far: " << player1Moves;
			cout << endl;
			cout << endl;
		}
	}
}

//this keeps track of how many moves the player has made
int Sudoku::turn() {
	player = player1;
	turns++;
	return 1;
}

//stalemate returns true if the player has filled the gameboard but not won.
bool Sudoku::stalemate() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (gameBoard[i * 9 + j].printOut == " ") {
				return false;
			}
		}
	}
	return true;
}

//plays the sudoku game: loads the starting gameboard, asks the player for moves, checks for wins & stalemates
int Sudoku::play() {
	try{
		gameBoard = load_file("Sudoku.txt", player);
	}
	catch (...){
		gameBoard = load_file("sudoku0.txt", player);
	}
	
	print();
	cout << "" << endl;
	cout << "" << endl;

	while (true) {
		unsigned int x, y, s;
		try {
			prompt(x, y, s);
			turn();
			setPiece(s, x, y);
		} catch (error_messages e) { //game simpy re-prompts after most errors, except for quit
			if (e == quit) {
				return usagemessage("Bye.", error_message_string(quit));
			}
		}

		if (done()) {
			gameBoard = load_file("sudoku0.txt", player);
			save_file("Sudoku", this->gameBoard, true); //We need to load the original file :/
			cout << "You have won the game!" << endl;
			return success;
		}

		if (stalemate()) {
			cout << "No more moves; you can't win it's all over sorry bye. Number of turns played: " << turns << endl;
			return usagemessage(exe_name, error_message_string(draw));
		}
	}

	return usagemessage(exe_name, error_message_string(playLoopError)); // should never get here

}

