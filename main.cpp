#include <iostream>
#include <vector>
#include <string>
#include "mapIO.hpp"
#include "playerBehaviour.hpp"
#include "ai.hpp"
#include "mapMaker.hpp"
#include "mainMenu.hpp"
using namespace std;


int main(){
    //Checks if userData.txt exists, if not, makes one.
    string fullfile = "userData.txt";
    fstream newFile(fullfile);
    if (!newFile) {
        ofstream newFile(fullfile);
        newFile << "dummy\n";
        newFile << 0;
        
    }
    newFile.close();
    game_data game = {};
    //Run main menu untill application is closed.
    while (true) {
      mainMenu(game);
    }
}