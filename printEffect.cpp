using namespace std;
#include "printEffect.hpp"


void printEffect(string text, bool line, int speed){ //if line is set to true printEffect will add a enter.
    for (unsigned int i = 0; i < text.size(); i++){
        cout << text[i];
        Sleep(speed);   
    }
    if(line == true){
        cout << endl;
    }
}

void rules(){
  string line;
  ifstream myfile("rulesWumpus.txt");
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      printEffect(line,true,15);
    }
    myfile.close();
  }

  else
    cout << "Unable to open file";
}

void statistics(game_data& game ,string name) {
  vector<string> highscore;
  string line;
  ifstream myfile("userData.txt"); // opens the file in read mode
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      highscore.push_back(line); // All lines will be pushed in the vector
    }
    myfile.close();
  }
  int score = stoi(highscore[1]); //To compare the score they both have to be inters
  printEffect("The highscore is ",false);
  cout << score << endl;
  if(game.player.score > score){    // if the current player has a higer score then the record, the changeHighscore function will be called
    printEffect("You have beaten the highscore! ", true);
    changeHighscore(name, game.player.score);
  }else{
    printEffect("The highscore has not been bested!", true);
  }
}

void changeHighscore(string name, int score) {
  ofstream newFile("userData.txt"); //opens the file in write mode so it will override the current score
  newFile << name << endl;
  newFile << score;
  newFile.close();
}