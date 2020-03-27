#ifndef _MAPIMAKER_HPP
#define _MAPMAKER_HPP

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapIO.hpp"
using namespace std;

vector<int> gen_rand_unique (const int & n);
vector<room> randomize_wumpus (vector<room> map, unsigned int nWumpus);
vector<room> randomize_hazards (vector<room> map, unsigned int nPits, unsigned int nBats);
player_data randomize_player_position(player_data player, vector<room> map);
game_data make_game_obj (const vector<room> & map, const player_data & player);
vector<room> gen_dodecahedron();
vector<room> sort_rooms (vector<room> map);

#endif /* _MAPMAKER_HPP */