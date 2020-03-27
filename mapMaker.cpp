#include "mapMaker.hpp"
//temporary:
#include <iostream>
using namespace std;

//Returns a random sequence of all unique ints in range 1 through n
vector<int> gen_rand_unique (const int & n){
    srand (time(NULL));
    vector<int> result;
    int rNumber;
    bool unique;
    while (result.size() < n){
        unique = true;
        rNumber = rand() % n + 1;
        for (unsigned int i=0; i<result.size(); i++){
            if (rNumber == result[i]){
                unique = false;
                break;
            }
        }
        if (unique){
            result.push_back(rNumber);
        }
    }
    return result;
}

//Randomizes wumpus location
vector<room> randomize_wumpus (vector<room> map, unsigned int nWumpus){
    srand (time(NULL));
    for (unsigned int i=0; i<nWumpus; i++){
        int rnumber = rand() % map.size() + 1;
        map[rnumber].wumpus = true;
    }
    return map;
}

//Randomizes pit and bat locations
vector<room> randomize_hazards (vector<room> map, unsigned int nPits, unsigned int nBats){
    srand (time(NULL));
    for (unsigned int i=0; i<nPits; i++){
        int rnumber = rand() % map.size() + 1;
        map[rnumber].pit = true;
    }
    return map;
}

//Randomizes player position
player_data randomize_player_position(player_data player, vector<room> map){
    srand (time(NULL));
    player.index = rand() % map.size() + 1;
    return player;
}

//Returns game_data variable from 'map' and 'player'
game_data make_game_obj (const vector<room> & map, const player_data & player){
    game_data game = {map, player};
    return game;
}

//Sorts the vector<room> map so that the room numbers are at index room number -1, making it easy to call them using their index
vector<room> sort_rooms (vector<room> map){
    room swapVar;
    for (unsigned int i=0; i<map.size(); i++){
        for (unsigned int j=i; j>0; j--){
            if (map[j].number < map[j-1].number){
                swapVar = map[j];
                map[j] = map[j-1];
                map[j-1] = swapVar;
            }
        }
    }
    return map;
}

//Generates dodecahedron map with random room numbers
vector<room> gen_dodecahedron(){
    //Below is a template with the right room connections for a dodecahedron, this function will change every x to a different y, but keep x=x
    vector<room> map = {
            {1,{2,5,8}, false, false, false},
            {2,{1,3,10}, false, false, false},
            {3,{2,4,12}, false, false, false},
            {4,{3,5,14}, false, false, false},
            {5,{1,4,6}, false, false, false},
            {6,{5,7,15}, false, false, false},
            {7,{6,8,17}, false, false, false},
            {8,{1,7,9}, false, false, false},
            {9,{8,10,18}, false, false, false},
            {10,{9,11,2}, false, false, false},
            {11,{10,12,19}, false, false, false},
            {12,{11,13,3}, false, false, false},
            {13,{12,14,20}, false, false, false},
            {14,{13,15,4}, false, false, false},
            {15,{14,16,6}, false, false, false},
            {16,{15,17,20}, false, false, false},
            {17,{16,18,7}, false, false, false},
            {18,{17,19,9}, false, false, false},
            {19,{18,20,11}, false, false, false},
            {20,{13,16,19}, false, false, false},
    };
    vector<int> randomUniqueInts = gen_rand_unique(20);
    //We use indexes in our random number list to make sure every, say, 12 in our map is replaced with, say, 3. To make sure the right connections are maintained.
    for (unsigned int i=0; i<map.size(); i++){
        map[i].number = randomUniqueInts[i];
        for (unsigned int j=0; j<map[i].neighbour.size(); j++){
            map[i].neighbour[j] = randomUniqueInts[map[i].neighbour[j]-1];
        }
    }
    return sort_rooms(map);
}
