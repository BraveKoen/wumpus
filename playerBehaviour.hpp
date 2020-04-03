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
#include "noise.hpp"
#include "enemyBehaviour.hpp"
#include "ai.hpp"
using namespace std;

game_data player_move(game_data game, string new_room);
game_data player_shoot(game_data game, int room_to_shoot);
game_data move_or_shoot(game_data game, string choice);
game_data give_up(game_data game, string choice);

#endif /* _PLAYERBEHAVIOUR_HPP */