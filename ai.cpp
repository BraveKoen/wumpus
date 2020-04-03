#include "ai.hpp"
using namespace std;

game_data ai_move (game_data game){

}

game_data adjust_rank(game_data game, int room, int n){    
    for (unsigned int i=0; i < game.ai.map[room].neighbour.size(); i++){
        game.ai.map[game.ai.map[room].neighbour[i]].rank + n;
    }
    return game;
}

game_data ai_listen (string type, int room, int info, game_data game){
    //neighbour
    if (type == "neighbour"){
        for(unsigned int i=0; i < game.ai.map[room].neighbour.size(); i++){
            if (game.ai.map[room].neighbour[i] == info){
                return game;
            }
        }
        game.ai.map[room].neighbour.push_back(info);
        return game;
    }
    //draft
    else if (type == "draft"){
        if(game.ai.map[room].draft == false){
           game = adjust_rank(game, room, -1);
        }
        game.ai.map[room].draft = info;
        return game;
    }
    //flapping
    else if (type == "flapping"){
        if(game.ai.map[room].flapping == false){
           game = adjust_rank(game,room, -1);
        }
        game.ai.map[room].flapping = info;
        return game;
    }
    //smell
    else if (type == "smell"){
        if(game.ai.map[room].smell == false){
           game = adjust_rank(game,room , -1);
        }
        game.ai.map[room].smell = info;
        return game;
    }
    //pit
    else if (type == "pit"){
        if(game.ai.map[room].pit == false){
           game = adjust_rank(game, room, -1);
        }
        game.ai.map[room].pit = info;
        return game;
    }
    //bat
    else if (type == "bat"){
        if(game.ai.map[room].bat == false){
           game = adjust_rank(game, room, -1);
        }    
        game.ai.map[room].bat = info;
        return game;
    }
    //wumpus
    else if (type == "wumpus"){
        if(game.ai.map[room].wumpus == false){
           game = adjust_rank(game, room, -1);
        }
        game.ai.map[room].wumpus = info;
        return game;
    }else{
        cout <<"error" << endl;
        game.running = false;
        return game;
    }
}

//Creates mostly empty map for ai to fill in.
vector<ai_room> ai_draw_map (int len){
    vector<ai_room> map;
    for (int i=0; i<len; i++){
        map.push_back({i+1, {}, false,false,false,false,false,false, 0});
    }
    return map;
}

//Makes empty ai
ai_memory make_ai (int playerIndex, int arrows, int mapSize){
    vector<ai_room> map = ai_draw_map(mapSize);
    player_data player = {playerIndex, arrows};
    return {map, player};
}