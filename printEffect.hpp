#ifndef _PRINTEFFECT_HPP
#define _PRINTEFFECT_HPP

#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "mapIO.hpp"
#include "printEffect.hpp"
using namespace std;
void printEffect(string text,bool line,int speed = 50);
void rules();
void statistics(game_data& game, string name);
void changeHighscore(string name, int score);

#endif /* _PRINTEFFECT_HPP */