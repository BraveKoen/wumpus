#ifndef _ENEMYBEHAVIOUR_HPP
#define _ENEMYBEHAVIOUR_HPP

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <vector>

#include "mapIO.hpp"
#include "printEffect.hpp"
#include "ai.hpp"
#include "mainMenu.hpp"
using namespace std;

void gameOver(game_data & game);
void restart(game_data & game);
void move_wumpus(game_data & game);
void move_bat(game_data & game);

#endif /* _ENEMYBEHAVIOUR_HPP */
