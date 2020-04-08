#include "ai.hpp"
using namespace std;

void adjust_rank(game_data & game, int room, int n){    
    for (unsigned int i=0; i < game.ai.map[room].neighbour.size(); i++){
        game.ai.map[game.ai.map[room].neighbour[i]].rank + n;
    }
    return;
}

void ai_listen (string type, int room, int info, game_data & game){
    //neighbour
    if (type == "neighbour"){
        if(game.ai.map[room].neighbour.size() != 0){
            for(unsigned int i=0; i < game.ai.map[room].neighbour.size(); i++){
                if (game.ai.map[room].neighbour[i] == info){
                    return;
                }
            }
        }
        game.ai.map[room].neighbour.push_back(info);
        return;
    }
    //draft
    else if (type == "draft"){
        if(game.ai.map[room].draft == false){
           adjust_rank(game, room, -1);
        }
        game.ai.map[room].draft = info;
        return;
    }
    //flapping
    else if (type == "flapping"){
        if(game.ai.map[room].flapping == false){
           adjust_rank(game,room, -1);
        }
        game.ai.map[room].flapping = info;
        return;
    }
    //smell
    else if (type == "smell"){
        if(game.ai.map[room].smell == false){
           adjust_rank(game,room , -1);
        }
        game.ai.map[room].smell = info;
        return;
    }
    //pit
    else if (type == "pit"){
        if(game.ai.map[room].pit == false){
           adjust_rank(game, room, -1);
        }
        game.ai.map[room].pit = info;
        return;
    }
    //bat
    else if (type == "bat"){
        if(game.ai.map[room].bat == false){
           adjust_rank(game, room, -1);
        }    
        game.ai.map[room].bat = info;
        return;
    }
    //wumpus
    else if (type == "wumpus"){
        if(game.ai.map[room].wumpus == false){
           adjust_rank(game, room, -1);
        }
        game.ai.map[room].wumpus = info;
        return;
    }else{
        cout <<"error" << endl;
        game.running = false;
        return;
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
//this function lets the ai move to rooms witch it has not been to yet. if it knows to find a wumpus, the ai will shoot it.
void ai_move (game_data & game){
    game.ai.map[game.ai.player.index].neighbour = game.map[game.player.index].neighbour;
    for(unsigned int i=0; i < game.ai.map[game.ai.player.index].neighbour.size(); i++){
        if(game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].wumpus){
            string room_number = to_string(game.ai.map[game.ai.player.index].neighbour[i]);
            move_or_shoot(game, "s", room_number);
            return;
        }
    }
    bool wumpusFound;
    for(unsigned int i=0; i<game.map.size(); i++){
        if(game.ai.map[i].wumpus){
            wumpusFound = true;
            break;
        }
    }

    vector<string> route;
    bool routeDone = false;
    if(wumpusFound == true){
        for(unsigned int i=0; i<game.ai.map[game.ai.player.index].neighbour.size(); i++){
            if(routeDone){
                break;
            }
            if(game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].bat == false && game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].pit == false){
                for(unsigned int j=0; j < game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour.size(); j++){

                    if(routeDone){
                        break;
                    }
                    if(game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].bat == false && game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].pit == false){
                        if(game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].wumpus){
                            route.push_back(to_string(game.ai.map[game.ai.player.index].neighbour[i]));
                            routeDone = true;
                        }else{
                            for(unsigned int k=0; k < game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour.size(); k++){
                                if(routeDone){
                                    break;
                                }
                                if(game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].bat == false && 
                                   game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].pit == false){
                                    if(game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].wumpus){
                                        route.push_back(to_string(game.ai.map[game.ai.player.index].neighbour[i]));
                                        route.push_back(to_string(game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]));
                                        routeDone = true;
                                    }else{
                                        for(unsigned int l=0; l < game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour.size(); l++){
                                            if(routeDone){
                                                break;
                                            }
                                            if(game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour[l]-1].bat == false && 
                                               game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour[l]-1].pit == false){
                                                if(game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour[l]-1].wumpus){
                                                    route.push_back(to_string(game.ai.map[game.ai.player.index].neighbour[i]));
                                                    route.push_back(to_string(game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]));
                                                    route.push_back(to_string(game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]));
                                                    routeDone = true;
                                                }else{
                                                    for(unsigned int m=0; m < game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour[l]-1].neighbour.size(); m++){
                                                        if(routeDone){
                                                            break;
                                                        }
                                                        if(game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour[l]-1].neighbour[m]-1].bat == false &&
                                                           game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour[l]-1].neighbour[m]-1].pit == false ){
                                                            if(game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour[l]-1].neighbour[m]-1].wumpus){
                                                                route.push_back(to_string(game.ai.map[game.ai.player.index].neighbour[i]));
                                                                route.push_back(to_string(game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]));
                                                                route.push_back(to_string(game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]));
                                                                route.push_back(to_string(game.ai.map[game.ai.map[game.ai.map[game.ai.map[game.ai.player.index].neighbour[i]-1].neighbour[j]-1].neighbour[k]-1].neighbour[l]));
                                                                routeDone = true;
        }   }   }   }   }   }   }   }   }   }   }   }   }   }
        
        for(unsigned int i=0; i<route.size(); i++){
        }
        if(wumpusFound && route.size() <= 0){ //Sometimes bats place us on the wumpus lair, but we cant find a route because he havent explored enough, in this case we get stuck in loop. So instead we pretend we dont know where it is.
            for(unsigned int i=0; i<game.map.size(); i++){
                if(game.ai.map[i].wumpus){
                    game.ai.map[i].wumpus = false;
                    wumpusFound = false;
                    break;
                }
            }
        }
        for(unsigned int i=0; i<route.size(); i++){
            move_or_shoot(game, "m", route[i]);
        }
        return;
    }
    
    srand (time(NULL));
    int rnumber = rand() % game.map[game.ai.player.index].neighbour.size();
    vector<bool> beenTo = {};
    int countBeenTo = 0;
    for(unsigned int i=0; i < game.map[game.ai.player.index].neighbour.size(); i++){
        if(game.ai.map[game.ai.player.index].neighbour.size() > 0){
            beenTo.push_back(true);
            countBeenTo++;
        }else{
            beenTo.push_back(false);
        }
    }
    
    int safety;
    if(countBeenTo == beenTo.size()){
        safety = 0;
        while(game.ai.map[game.ai.map[game.ai.player.index].neighbour[rnumber]-1].bat || game.ai.map[game.ai.map[game.ai.player.index].neighbour[rnumber]-1].pit || safety > 100){
            rnumber = rand() % game.ai.map[game.ai.player.index].neighbour.size();
            safety++;
        }
        string room_number = to_string(game.ai.map[game.ai.player.index].neighbour[rnumber]);
        move_or_shoot(game, "m", room_number);
    }else{
        safety = 0;
        while(beenTo[rnumber]==true){
            rnumber = rand() % game.ai.map[game.ai.player.index].neighbour.size();
            safety++;
        }
        string room_number = to_string(game.ai.map[game.ai.player.index].neighbour[rnumber]);
        move_or_shoot(game, "m", room_number);
    }
    return;
}
