#include "mapIO.hpp"
#include "mapMaker.hpp"
#include <iostream>
using namespace std;


int main(){
    //vector<int> result;
    //result = gen_rand_unique(20);
    //for (unsigned int i=0; i<result.size(); i++){
    //    cout << result[i] << " ";
    //}

    //cout << "Dodecahedron test #1: " << endl;
    //vector<room> map = gen_dodecahedron();
    //cout << "Mapsize: " << map.size() << endl;
    //for (unsigned int i=0; i<map.size(); i++){
    //    cout << "main: " << map[i].number << endl;
    //}

    vector<room> map = gen_dodecahedron();
    player_data player = {1, 5};
    player = randomize_player_position(player, map);
    map = randomize_hazards(map, 2, 2);
    map = randomize_wumpus(map, 1);
    game_data game = make_game_obj(map, player);
    //cout << "Mapsize: " << game.map.size() << endl;
    //for (unsigned int i=0; i<game.map.size(); i++){
    //    cout << "wumpus: " << game.map[i].wumpus << endl;
    //    cout << "pits: " << game.map[i].pit << endl;
    //}
    //cout << game.player.index;
    write_config(game);
    
    //game_data game = read_config();
    //cout << "Mapsize: " << game.map.size() << endl;
    //for (unsigned int i=0; i<game.map.size(); i++){
    //    cout << "wumpus: " << game.map[i].wumpus << endl;
    //    cout << "pits: " << game.map[i].pit << endl;
    //}
}