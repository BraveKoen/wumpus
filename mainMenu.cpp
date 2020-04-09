#include "mainMenu.hpp"
using namespace std;

//Used to start the game, view rules and statistics, generate a new cave or let the computer play for you
void mainMenu(game_data & game){
    cout << endl;
    string playerInput = game.menuOption;
    //Skips the printing of main menu options if game.menuOption is already set, which should only be 'rp' or 'rc' if the yes option is selected in the restart menu, by either player or computer (which will do so automatically).
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
        // this part runs the game
        game = read_config();
        game.player.score = 500; //sets the base score to 500
        game.ai = make_ai(game.player.index, game.player.arrows, game.map.size()); //Purely exists to counter errors if functions are called that need an ai to exist
        game.menuOption = "rp";
        game.res = "";
        while(game.running == true) {
            move_or_shoot(game, "", "");
        }
    }else if(playerInput == "rp"){
        //this part is activated once someone wants to replay the game after they've died, this way it skips the main menu
        game = read_config();
        game.menuOption = "rp";
        game.res = "";
        game.player.score = 500;
        game.ai = make_ai(game.player.index, game.player.arrows, game.map.size()); //Purely exists to counter errors if functions are called that need an ai to exist
        while(game.running == true) {
            move_or_shoot(game, "", "");
        }
    }else if(playerInput == "q" || playerInput == "Q"|| playerInput == "quit"|| playerInput == "Quit"){
        // exits the entire program
        exit(0);
    }else if(playerInput == "r" || playerInput == "R"|| playerInput == "rules"|| playerInput == "Rules"){
        // opens and reads a text file with the rules of the game
        rules();
    }else if(playerInput == "g" || playerInput == "G"|| playerInput == "generate"|| playerInput == "Generate"){
        // this generates a new map with the same amount of rooms but put in different positions
        vector<room> map = gen_dodecahedron();
        player_data player = {1, 5};
        
        map = randomize_hazards(map, 2, 2);
        map = randomize_wumpus(map, 1);

        player = randomize_player_position(player, map);

        game = make_game_obj(map, player);

        write_config(game);
        printEffect("New cave generated!", true);
    }else if(playerInput == "c" || playerInput == "C"|| playerInput == "computer"|| playerInput == "Computer"){
        // this runs the game, but also runs the ai do the computer will play the game for you
        game = read_config();
        game.player.score = 500; //sets the base score to 500
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
        // this will show the current highest scoring player there is
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
     // if someone decides to put something else in, it will give an error and will ask for another input
    printEffect("invalid input", true);
    playerInput = "";
    }
}