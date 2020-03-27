#ifndef _PLAYERBEHAVIOUR_HPP
#define _PLAYERBEHAVIOUR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "mapIO.hpp"
#include "printEffect.hpp"
using namespace std;

game_data player_move(game_data game);
game_data player_shoot(game_data game);
game_data move_or_shoot(game_data game);


#endif /* _PLAYERBEHAVIOUR_HPP */


