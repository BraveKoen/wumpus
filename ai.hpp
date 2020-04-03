#ifndef _AI_HPP
#define _AI_HPP

#include "mapIO.hpp"

game_data ai_listen (string type, int room, int info, game_data game);
ai_memory make_ai (int playerIndex, int arrows, int mapSize);

#endif /* _AI_HPP */