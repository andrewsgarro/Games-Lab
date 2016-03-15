//Autoplayer.h
//Andrew Sgarro and Ethan Glassman
//andrew.sgarro@wustl.edu ethan.glassman@wustl.edu
//This file has the code for running the autoplayer for the gomoku game

#include "stdafx.h"
#include "Autoplayer.h"
#include <stdlib.h>
#include <time.h>
#include "errors.h"

using namespace std;

int play_counter;
int first_x;
int first_y;

void setup_autoplay(){
	srand((unsigned)time(0));
	first_x = (rand() % 14) + 1;
	first_y = (rand() % 14) + 1;
}

string autoplay_function(int counter, playerNum player, vector<Game_Piece> gameBoard, string auto_type){
	if (play_counter == 0){
		setup_autoplay();
	}
	string play;
	if (play_counter < 15){
		if (auto_type == "horizontal" || auto_type == "rows"){
			//Horizontal
			if (player == player1){
				play += to_string(first_x + counter);
				play += ",";
				play += to_string(first_y);
			}
			else{
				int other_x = (rand() % 14) + 1;
				int other_y = (rand() % 14) + 1;
				play += to_string(other_x + 5 + counter);
				play += ",";
				play += to_string(other_y + counter);
			}
			cout << play << endl;
		}

		else  if (auto_type == "vertical" || auto_type == "collumns"){
			//Vertical
			if (player == player1){
				play += to_string(first_x);
				play += ",";
				play += to_string(first_y + counter);
			}
			else{
				int other_x = (rand() % 14) + 1;
				int other_y = (rand() % 14) + 1;
				play += to_string(other_x + 5 + counter);
				play += ",";
				play += to_string(other_y + counter);
			}
			cout << play << endl;
		}

		else if (auto_type == "diagonal_up"){
			//Diagonal up
			if (player == player1){
				play += to_string(first_x + counter);
				play += ",";
				play += to_string(first_y + counter);
			}
			else{
				int other_x = (rand() % 14) + 1;
				int other_y = (rand() % 14) +1;
				play += to_string(other_x + 5 + counter);
				play += ",";
				play += to_string(other_y + counter);
			}
			cout << play << endl;
		}

		else if (auto_type == "diagonal_down"){
			//Diagonal down
			if (player == player1){
				play += to_string(first_x + counter);
				play += ",";
				play += to_string(first_y + 5 - counter);
			}
			else{
				int other_x = (rand() % 14) + 1;
				int other_y = (rand() % 14) + 1;
				play += to_string(other_x + 5 + counter);
				play += ",";
				play += to_string(other_y + 5 + counter);
			}
			cout << play << endl;
		}

		else if (auto_type == "random"){
			//Random
			play_counter = 0;
			if (player == player1){
				int other_x = rand() % 19 + 1;
				int other_y = rand() % 19 + 1;
				play += to_string(other_x);
				play += ",";
				play += to_string(other_y);
			}
			else{
				int other_x = rand() % 19 + 1;
				int other_y = rand() % 19 + 1;
				play += to_string(other_x);
				play += ",";
				play += to_string(other_y);
			}
			cout << play << endl;
		}

		//Stalemate
		else if (auto_type == "stalemate" || auto_type == "draw"){
			play_counter = 0;
			//Want to break it up into big 4x2 blocks
			if (player == player1){
				int x_block_counter = 0;
				int x_offset = 0;
				int y_block_counter = 0;
				int x_move_counter = 1;
				int y_move_counter = 1;
				int x = 1;
				int y = 1;
				while (gameBoard[21 * y + x].piecePlayer != invalid_num) {
					if ((x_block_counter + y_block_counter) % 2 != 0){
						x_offset = 4;
					}
					else{
						x_offset = 0;
					}y = y_block_counter * 2 + y_move_counter;
					if (y_move_counter > 2){
						y_move_counter = 1;
						y_block_counter += 2;
						x_move_counter = 1;
					}
					if (y > 19){
						y_block_counter = 1;
						y_move_counter = 1;
						y = y_block_counter * 2 + y_move_counter;
					}
					x = x_block_counter * 4 + x_move_counter + x_offset;
					++x_move_counter;
					if (x_move_counter > 4){
						x_move_counter = 1;
						x_block_counter += 1;
					}
					if (x > 19){
						x_block_counter = 0;
						x_move_counter = 1;
						++y_move_counter;
						if ((x_block_counter + y_block_counter) % 2 != 0){
							x_offset = 4;
						}
						else{
							x_offset = 0;
						}
						x = x_block_counter * 4 + x_move_counter + x_offset;
					}

				}
				play += to_string(x);
				play += ",";
				play += to_string(y);
			}
			else{
				int x_block_counter = 0;
				int x_offset = 0;
				int y_block_counter = 0;
				int x_move_counter = 1;
				int y_move_counter = 1;
				int x = 1;
				int y = 1;
				int play2_count = 0;
				while (gameBoard[21 * y + x].piecePlayer != invalid_num) {
					if (play2_count <= (19 * 19) - 3){
						if ((x_block_counter + y_block_counter) % 2 != 0){
							x_offset = 4;
						}
						else{
							x_offset = 0;
						}
						y = y_block_counter * 2 + y_move_counter;
						if (y_move_counter > 2){
							y_move_counter = 1;
							y_block_counter += 1;
							x_move_counter = 1;
						}
						if (y > 19){
							y_block_counter = 1;
							y_move_counter = 1;
							y = y_block_counter * 2 + y_move_counter;
						}
						x = x_block_counter * 4 + x_move_counter + 4 - x_offset;
						++x_move_counter;
						if (x_move_counter > 4){
							x_move_counter = 1;
							x_block_counter += 1;
						}
						if (x > 19){
							x_block_counter = 0;
							x_move_counter = 1;
							++y_move_counter;
							if ((x_block_counter + y_block_counter) % 2 != 0){
								x_offset = 4;
							}
							else{
								x_offset = 0;
							}
							x = x_block_counter * 4 + x_move_counter + 4 - x_offset;
						}
						++play2_count;
					}

					else{
						//We have a special case near the end, Otherwise we would freeze :(
						x = 16;
						y = 19; 
					}
				}
				play += to_string(x);
				play += ",";
				play += to_string(y);
			}
			cout << play << endl;
		}

		else{
			cout << error_message_string(auto_not_specified) << endl;
			return "quit";
		}
	}

	else{
		play = "quit";
		cout << play << endl;
	}
	++play_counter;
	return play;
}
