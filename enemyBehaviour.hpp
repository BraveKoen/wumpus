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
using namespace std;

game_data gameOver(game_data game);
game_data restart(game_data game);
game_data move_wumpus(game_data game);
game_data move_bat(game_data game);

#endif /* _ENEMYBEHAVIOUR_HPP */
