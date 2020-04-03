#include <iostream>
#include <vector>
#include <string>
#include "mapIO.hpp"
#include "playerBehaviour.hpp"
#include "ai.hpp"
#include "mapMaker.hpp"
using namespace std;

void mainMenu(){
    string playerInput = "";
    printEffect("Hunt the Wumpus",true);
    printEffect("welcome, what would you like to do: ",true);
    printEffect("p: play the game",true);
    printEffect("r: rules of the game", true);
    printEffect("g: generate a new cave",true);
    printEffect("c: let the computer play for you",true);
    printEffect("q, quit the game",true);
    cin >> playerInput;

    if(playerInput == "p" || playerInput == "P"|| playerInput == "play"|| playerInput == "Play"){
        game_data game = read_config();
        while(game.running == true) {
            game.ai = make_ai(game.player.index, game.player.arrows, game.map.size());
            move_or_shoot(game, "");
        }
    }
    else if(playerInput == "q" || playerInput == "Q"|| playerInput == "quit"|| playerInput == "Quit"){
        exit(0);
    }else if(playerInput == "r" || playerInput == "R"|| playerInput == "rules"|| playerInput == "Rules"){
        rules();
    }else if(playerInput == "g" || playerInput == "G"|| playerInput == "generate"|| playerInput == "Generate"){
        vector<room> map = gen_dodecahedron();
        player_data player = {1, 5};
        
        map = randomize_hazards(map, 2, 2);
        map = randomize_wumpus(map, 1);

        player = randomize_player_position(player, map);

        game_data game = make_game_obj(map, player);

        write_config(game);
        printEffect("New cave generated!", true);
    }else if(playerInput == "c" || playerInput == "C"|| playerInput == "computer"|| playerInput == "Computer"){
        game_data game = read_config();
        while(game.running == true) {
            game.ai = make_ai(game.player.index, game.player.arrows, game.map.size());
            }
    }
    else{
    printEffect("invalid input", true);
    }
}


int main(){
    while (true){
        mainMenu();
    }
}