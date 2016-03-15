//Game.h
//Andrew Sgarro and Ethan Glassman
//andrew.sgarro@wustl.edu ethan.glassman@wustl.edu
//This header file declares the base class for each of the games, and then all 3 game classes: TicTacToe, Gomoku and Sudoku

#ifndef GAME_H
#define GAME_H

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include "GamePieces.h"
#include "errors.h"
#include <memory>
using namespace std;

static string exe_name;

//base class from which we will derive both TicTacToe and Gomoku
class BaseGame{
protected:
	//General constructor
	BaseGame(int xval, int yval, int turnsval, int longestnameval, int p1movesval, int p2movesval, playerNum playerval, int winnerval);
	int x;
	int y;
	int turns;
	unsigned int longest_name;
	vector<Game_Piece> gameBoard;
	
	enum playerNum player;
	int winner;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int turn() = 0;
	virtual void print() = 0;
	static shared_ptr<BaseGame> game;
public:
	int prompt(unsigned int& a, unsigned int& b);
	static void game_type(int argc, char * argv[]);
	virtual int play() = 0;
	static shared_ptr<BaseGame> instance(){
		if (BaseGame::game != nullptr){
			return BaseGame::game;
		}
		else{
			throw game_null_ptr;
		}
	}
	static string player1Moves;
	static string player2Moves;
};

//Gomoku class, derived from BaseGame
class Gomoku : public BaseGame {
	friend ostream & operator << (ostream &, const Gomoku &);
private:
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
	int prompt(unsigned int& a, unsigned int& b);
	virtual int play();
	bool done_stalemate();
	void setPiece(Game_Piece g, unsigned int a, unsigned int b);
	//The values for these will never change
	unsigned int left_x = 1;
	unsigned int right_x = 20;
	unsigned int bottom_y = 1;
	unsigned int top_y = 20;
public:
	const static int horiz = 21;
	const static int vert = 21;
	//Gomoku constructor
	Gomoku() : BaseGame(horiz, vert, 0, 0, 0, 0, playerNum::player1, 0) {};	//gameboard is 19x19, with buffer is 21x21
	void playMove(ifstream& ifs, playerNum, int, int);
	//Inherited methods redefined for each game
	virtual void print(){
		cout << *this;
	}
	string autoplay; //for autoplayer testing
	static string player1Name; //Centralized location for the name x and y so we can change easily based on game type
	static string player2Name;
	static piece_color player1Color; //Centralized location for the name x and y so we can change easily based on game type
	static piece_color player2Color;
};

//TicTacToe class, derived from BaseGame
class TicTacToe : public BaseGame {
private:
	friend ostream & operator << (ostream &, const TicTacToe &);
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
	virtual int prompt(unsigned int& a, unsigned int& b);
	virtual int play();
	void setPiece(Game_Piece g, unsigned int a, unsigned int b);
	//The values for these will never change
	unsigned int left_x = 1;
	unsigned int right_x = 3;
	unsigned int bottom_y = 1;
	unsigned int top_y = 3;
public:
	//TicTacToe constructor
	const static int horiz = 5;
	const static int vert = 5;
	TicTacToe() : BaseGame(horiz, vert, 0, 0, 0, 0, playerNum::player1, 0) {};	//gameboard is 3x3, with buffer is 5x5
	void playMove(ifstream& ifs, playerNum, int, int);
	//Inherited methods redefined for each game
	virtual void print(){
		cout << *this;
	}
	static string player1Name; //Centralized location for the name x and y so we can change easily based on game type
	static string player2Name;
	static piece_color player1Color; //Centralized location for the name x and y so we can change easily based on game type
	static piece_color player2Color;
};



//Sudoku class, derive from BaseGame
class Sudoku : public BaseGame {
private:
	friend ostream & operator << (ostream &, const Sudoku &);
	virtual bool stalemate();
	virtual int turn();
	virtual int play();
	void setPiece(int s, unsigned int y, unsigned int x);
	//The values for these will never change
	unsigned int left_x = 0;
	unsigned int right_x = 8;
	unsigned int bottom_y = 0;
	unsigned int top_y = 8;
public:
	const static int horiz = 9;
	const static int vert = 9;
	//constructor
	Sudoku() : BaseGame(horiz, vert, 0, 0, 0, 0, playerNum::player1, 0) {};	//9x9 gameboard, no border --asked TA they said we can decide if we want border
	void playMove(ifstream& ifs, int x, int y, int pieceVal);
	virtual bool done();
	void prompt(unsigned int& x, unsigned int& y, unsigned int& s);
	//Inherited methods redefined for each game
	virtual void print(){
		cout << *this;
	}
	string autoplay;
};

int printGameBoard(const vector<Game_Piece> & board, unsigned int a, unsigned b);

#endif