#ifndef _MAPIO_HPP
#define _MAPIO_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct room{
    int number;
    vector<int> neighbour;
    bool pit;
    bool bat;
    bool wumpus;
};

struct player_data{
    int index;
    int arrows;
};

struct ai_room{
    int number;
    vector<int> neighbour;
    bool pit;
    bool bat;
    bool wumpus;
    bool draft;
    bool flapping;
    bool smell;
    int rank;
};

struct ai_memory{
    vector<ai_room> map;
    player_data player;
};

struct game_data{
    vector<room> map;
    player_data player;
    bool running = true;
    ai_memory ai;
};

void write_config(const game_data & game);
game_data read_config();

#endif /* _MAPIO_HPP */
