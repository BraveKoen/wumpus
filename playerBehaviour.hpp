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

void player_move(game_data & game, string new_room);
void player_shoot(game_data & game, string room_to_shoot);
void move_or_shoot(game_data & game, string choice, string choice_room);
void give_up(game_data & game, string choice);

#endif /* _PLAYERBEHAVIOUR_HPP */