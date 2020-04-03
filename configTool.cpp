#include "mapIO.hpp"
#include "mapMaker.hpp"
#include <iostream>
using namespace std;


int main(){

    vector<room> map = gen_dodecahedron();
    player_data player = {1, 5};
    
    map = randomize_hazards(map, 2, 2);
    map = randomize_wumpus(map, 1);

    player = randomize_player_position(player, map);

    game_data game = make_game_obj(map, player);

    write_config(game);
}