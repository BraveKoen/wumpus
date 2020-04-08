#include "mainMenu.hpp"
using namespace std;

void mainMenu(game_data & game){
    cout << endl;
    string playerInput = game.menuOption;
    if(playerInput == ""){
        printEffect("HUNT THE WUMPUS\n", true);
        printEffect("welcome, what would you like to do: ",true);
        printEffect("p: play the game",true);
        printEffect("r: rules of the game", true);
        printEffect("s: see player statistics", true);
        printEffect("g: generate a new cave",true);
        printEffect("c: let the computer play for you",true);
        printEffect("q, quit the game",true);
        cin >> playerInput;
    }

    if(playerInput == "p" || playerInput == "P"|| playerInput == "play"|| playerInput == "Play"){
        game = read_config();
        game.player.score = 500;
        game.ai = make_ai(game.player.index, game.player.arrows, game.map.size()); //Purely exists to counter errors if functions are called that need an ai to exist
        game.menuOption = "rp";
        game.res = "";
        while(game.running == true) {
            move_or_shoot(game, "", "");
        }
    }else if(playerInput == "rp"){
        game = read_config();
        game.menuOption = "rp";
        game.res = "";
        game.player.score = 500;
        game.ai = make_ai(game.player.index, game.player.arrows, game.map.size()); //Purely exists to counter errors if functions are called that need an ai to exist
        while(game.running == true) {
            move_or_shoot(game, "", "");
        }
    }else if(playerInput == "q" || playerInput == "Q"|| playerInput == "quit"|| playerInput == "Quit"){
        exit(0);
    }else if(playerInput == "r" || playerInput == "R"|| playerInput == "rules"|| playerInput == "Rules"){
        rules();
    }else if(playerInput == "g" || playerInput == "G"|| playerInput == "generate"|| playerInput == "Generate"){
        vector<room> map = gen_dodecahedron();
        player_data player = {1, 5};
        
        map = randomize_hazards(map, 2, 2);
        map = randomize_wumpus(map, 1);

        player = randomize_player_position(player, map);

        game = make_game_obj(map, player);

        write_config(game);
        printEffect("New cave generated!", true);
    }else if(playerInput == "c" || playerInput == "C"|| playerInput == "computer"|| playerInput == "Computer"){
        game = read_config();
        game.player.score = 500;
        game.ai = make_ai(game.player.index, game.player.arrows, game.map.size());
        game.res = "y";
        game.menuOption = "rc";
        while(game.running == true) {
                ai_move(game);
            }
    }else if(playerInput == "rc"){
        game_data aiBackup = game;
        game = read_config();
        game.player.score = 500;
        game.ai = aiBackup.ai;
        game.res = "y";
        game.menuOption = "rc";
        game.ai.player.index = game.player.index;
        while(game.running == true) {
                ai_move(game);
            }
    }else if(playerInput == "s" || playerInput == "S"|| playerInput == "score"|| playerInput == "Score"){
        printEffect("the current highscore is: ",true);
        string line;
        vector<string> lines;
        ifstream myfile("userData.txt");
        if (myfile.is_open()) {
          while (getline(myfile, line)) {
            lines.push_back(line);
          }
          myfile.close();
        }
        printEffect(lines[0], true);
        printEffect("With ", false);
        printEffect(lines[1], false);
        printEffect(" points",true);
    }
    else{
    printEffect("invalid input", true);
    playerInput = "";
    }
}