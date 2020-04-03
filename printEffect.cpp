using namespace std;
#include "printEffect.hpp"


void printEffect(string text, bool line, int speed){
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
      printEffect(line,true,25);
    }
    myfile.close();
  }

  else
    cout << "Unable to open file";
}