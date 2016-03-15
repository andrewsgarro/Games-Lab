//TicTacToeSource.cpp
//Andrew Sgarro and Ethan Glassman
//andrew.sgarro@wustl.edu ethan.glassman@wustl.edu
//This file has all the particulars for the tictactoe game

#include "stdafx.h"
#include "IO.h"
#include "errors.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <regex>
using namespace std;

//overload the << operator to print a TicTacToe object
ostream & operator << (ostream & o, const TicTacToe &t) {
	
	vector<Game_Piece> gb = t.gameBoard;
	unsigned int current_longest = t.longest_name;

	for (int i = 4; i >= 0; i--) {
		for (unsigned int j = 0; j <= 5; j++) {
			if (j == 0) {
				o << i << " " << setw(current_longest);
			} else if (j == 1) { o << gb[i*5 + (j-1)].printOut; } //these are just different for the spacing
			else {o << gb[i*5 + (j-1)].printOut << " "; }
		}
		o << endl;
	}
	o << " ";
	for (int i = 0; i <= 4; i++) {
		o << i << " " << setw(current_longest);
	}
	return o;
}

//checks if someone has won
bool TicTacToe::done() {

	//check rows w/ y value 1 to 3, to see if any of the x slots 1-3 are non-" " and the same
	for (int i = 1; i < 4; i++) {  
		string temp = gameBoard[i*5 + 1].printOut;
		if ((temp != " ") && (temp == gameBoard[i*5 + 2].printOut) &&  (temp == gameBoard[i*5 + 3].printOut)) { 
			if (temp == player1Name) { winner = 1; }
			else { winner = 2; }
			return true;
		}
	}

	//check columns
	for (int i = 1; i < 4; i++) {  
		string temp = gameBoard[5 + i].printOut;
		if ((temp != " ") && (temp == gameBoard[10 + i].printOut) && (temp == gameBoard[15 + i].printOut)) {
			if (temp == player1Name) { winner = 1; }
			else { winner = 2; }
			return true;
		}
	}

	//check diagonals; only two options so we do it manually
	string diagOne = gameBoard[16].printOut;
	if ((diagOne != " ") && (diagOne == gameBoard[12].printOut) && (diagOne == gameBoard[8].printOut)) {
		if (diagOne == player1Name) { winner = 1; }
		else { winner = 2; }
		return true;
	}

	string diagTwo = gameBoard[18].printOut;
	if ((diagTwo != " ") && (diagTwo == gameBoard[12].printOut) && (diagTwo == gameBoard[6].printOut)) {
		if (diagTwo == player1Name) { winner = 1; }
		else { winner = 2; }
		return true;
	}

	//if there are no matches
	return false;

}

//stalemate checks if the game is over and no one has won
bool TicTacToe::stalemate() {

	for (int i = 1; i < 4; i++) {
		for (int k = 1; k < 4; k++) {
			if (gameBoard[i*5 + k].printOut == " ") {
				return false;
			}
		}
	}
	bool winner = done();
	if (winner) return false;
	return true;
}

//Prompt asks for user input and extracts x,y coordinates into the referenced ints
int TicTacToe::prompt(unsigned int & x, unsigned int & y){
	cout << "Type coordinates (x,y) to play a piece, or quit to end the game" << endl;
	cout << "" << endl;
	string user_input;
	getline(cin, user_input);
	if (user_input == "quit"){
		while (true){
			cout << "Would you like to save your game?" << endl;
			cout << "Please enter yes or no" << endl;
			getline(cin, user_input);
			if (lowercase(user_input) == "yes"){
				save_file("TicTacToe", this->gameBoard, true);
				return quit;
			}
			else if (lowercase(user_input) == "no"){
				save_file("TicTacToe", this->gameBoard, false);
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
		if (gameBoard[5 * y + x].printOut != " ") {
			return usagemessage(exe_name, error_message_string(spaceOccupied));
		}
		else{
			return success;
		}
		
	}
}

//turn  begins each players turn, and calls prompt within it
int TicTacToe::turn() {
	unsigned int a;
	unsigned int b;
	int moveResult; 
	bool validMove = false;

	//set player as 1 or 2
	if (player == playerNum::player1) {

		cout << "Player 1's turn (" << TicTacToe::player1Name << ")" << endl;

		moveResult = prompt(a, b);

		if (moveResult == quit) {
			return quit;
		}
		if (moveResult == success) {

			Game_Piece g;
			g.pieceColor = TicTacToe::player1Color;
			g.piecePlayer = playerNum::player1;
			g.printOut = TicTacToe::player1Name;
			if (g.printOut.length() > BaseGame::longest_name){
				BaseGame::longest_name = g.printOut.length();
			}
			
			setPiece(g, a, b); //add valid move to gameboard

			BaseGame::player1Moves += (to_string(a) + "," + to_string(b) + "; ");

			cout << endl;
			cout << *this << endl;
			cout << endl;
			cout << "Player 1's moves so far" << player1Moves << endl;
			cout << endl;

			player = playerNum::player2;
			turns++;

		}
	} else {

		cout << "Player 2's turn (" << TicTacToe::player2Name << ")" << endl;

		moveResult = prompt(a, b);

		if (moveResult == quit) {
			return quit;
		}
		if (moveResult == success) {
			Game_Piece g;
			g.pieceColor = TicTacToe::player2Color;
			g.piecePlayer = playerNum::player2;
			g.printOut = TicTacToe::player2Name;
			if (g.printOut.length() > BaseGame::longest_name){
				BaseGame::longest_name = g.printOut.length();
			}
			setPiece(g, a, b);

			BaseGame::player2Moves += (to_string(a) + "," + to_string(b) + "; ");

			cout << endl;
			cout << *this << endl;
			cout << endl;
			cout << "Player 2's moves so far" << player2Moves << endl;
			cout << endl;

			player = playerNum::player1;
			turns++;


		}
	}

	return success;

}

//sets a piece on the gameboard given x and y values (a and b)
void TicTacToe::setPiece(Game_Piece g, unsigned int a, unsigned int b) {
	gameBoard[5*b + a] = g;
}

//calling this method begins the TicTacToe game
int TicTacToe::play(){
	try{
		gameBoard = load_file("TicTacToe.txt", player);
	}
	catch(...){
		//start off by setting all the gameboard slots up with empty pieces
		for (unsigned int i = 0; i < 25; i++) {
			Game_Piece null;
			null.printOut = ' ';
			null.piecePlayer = invalid_num;
			null.pieceColor = empty_color;
			gameBoard.push_back(null);
		}
	}

	//start out by printing the gameboard
	print();
	cout << "" << endl; 
	cout << "" << endl;

	while (true) {

		int t = turn();

		if (done()) {
			save_file("TicTacToe", this->gameBoard, false);
			if (winner == 1) {
				cout << "Player 1 (X) won the game!" << endl;
			} else {
				cout << "Player 2(O) won the game!" << endl;
			}
			return success;
		}

		if (stalemate()) {
			cout << "DRAW: number of turns played: " << turns << endl;
			return usagemessage(exe_name, error_message_string(draw));
		}

		if (t == quit) return usagemessage(exe_name, error_message_string(quit));
	}

	return usagemessage(exe_name, error_message_string(playLoopError)); // should never get here
}