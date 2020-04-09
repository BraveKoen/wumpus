#include "mapIO.hpp"
using namespace std;

//Writes map and player data to file in arbitrary format.
void write_config(const game_data & game){
    ofstream configFile;
    configFile.open("gameConfig.txt");
    configFile << "start" << endl;
    configFile << "game" << endl << "map" << endl;
    for (unsigned int i=0; i<game.map.size(); i++){
        configFile << "room" << endl << game.map[i].number << endl;
        for (unsigned int j=0; j<game.map[i].neighbour.size(); j++){
            configFile << game.map[i].neighbour[j] << endl;
        }
        configFile << game.map[i].pit << endl << game.map[i].bat << endl << game.map[i].wumpus << endl;
    }
    configFile << "player" << endl << game.player.index << endl << game.player.arrows << endl;
    configFile << "end";
    configFile.close();
}

//Reads map and player data from file in arbitrary format. Returns game_data struct. Structs are defined in mapIO.hpp.
game_data read_config(){
    room tempRoom;
    vector<room> map;
    player_data player;
    game_data game;
    string line;
    vector<string> lines;
    ifstream configFile ("gameConfig.txt");
    if (configFile.is_open()){
        while (getline(configFile, line)){
            lines.push_back(line);
        }
        if (lines[0] == "start"){
            for (unsigned int i=1; i<lines.size(); i++){
                tempRoom = {0,{},false,false,false};
                if (lines[i]=="room"){
                    tempRoom.number = stoi(lines[i+1]);
                    tempRoom.neighbour = {stoi(lines[i+2]), stoi(lines[i+3]), stoi(lines[i+4])};
                    tempRoom.pit = stoi(lines[i+5]);
                    tempRoom.bat = stoi(lines[i+6]);
                    tempRoom.wumpus = stoi(lines[i+7]);
                    map.emplace_back(tempRoom);
                    i += 7;
                    continue;
                }
                if (lines[i]=="player"){
                player.index = stoi(lines[i+1]);
                player.arrows = stoi(lines[i+2]);  
                }
            }
            game_data game = {map, player};
            return game;
        }else{
            cout << "Incorrect file syntax, manually review, or choose generate new cave in main menu.";
        }
        configFile.close();
    }else{
        cout << "Unable to open gameConfig.txt, check if file exists, otherwise make one with configTool.exe" << endl;
    }
}