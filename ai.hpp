#ifndef _AI_HPP
#define _AI_HPP

#include "mapIO.hpp"
#include "playerBehaviour.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ai_listen (string type, int room, int info, game_data & game);
ai_memory make_ai (int playerIndex, int arrows, int mapSize);
void ai_move (game_data & game);

#endif /* _AI_HPP */