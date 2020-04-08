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
    string fullfile = "userData.txt";
    fstream newFile(fullfile);
    if (!newFile) {
        ofstream newFile(fullfile);

        newFile << "dummy\n";
        newFile << 0;
        
    }
    newFile.close();
    game_data game = {};
  while (true) {
    mainMenu(game);
    }
}