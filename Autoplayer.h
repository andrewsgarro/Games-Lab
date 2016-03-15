//Autplayer.h
//Andrew Sgarro and Ethan Glassman
//andrew.sgarro@wustl.edu ethan.glassman@wustl.edu
//This file defines the autoplayer for the gomoku game

#ifndef AUTOPLAYER_H
#define AUTOPLAYER_H

#include "stdafx.h"
#include "GamePieces.h"

void setup_autoplay();
string autoplay_function(int counter, playerNum player, vector<Game_Piece> gameBoard, string auto_type);

#endif