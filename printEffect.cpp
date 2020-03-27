using namespace std;
#include "printEffect.hpp"


void printEffect(string text, bool line){
    for (unsigned int i = 0; i < text.size(); i++){
        cout << text[i];
        Sleep(50);   
    }
    if(line == true){
        cout << endl;
    }
}
