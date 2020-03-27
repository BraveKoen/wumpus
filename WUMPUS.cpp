#include <iostream>
#include <vector>
#include <string>
#include "mapIO.hpp"
#include "playerBehaviour.hpp"
using namespace std;





int main(){
    string restart = "y";
    do{
        //temp map
        //vector<room> map = {
        //    {1,{2,5,8}, false, false, false},
        //    {2,{1,3,10}, false, false, false},
        //    {3,{2,4,12}, false, false, false},
        //    {4,{3,5,14},false, false, false},
        //    {5,{1,4,6}, false, false, false},
        //    {6,{5,7,15}, false, false, false},
        //    {7,{6,8,17}, false, false, false},
        //    {8,{1,7,9}, false, false, false},
        //    {9,{8,10,18}, false, false, false},
        //    {10,{9,11,2}, false, false, true},
        //    {11,{10,12,19}, false, false, false},
        //    {12,{11,13,3}, false, false, false},
        //    {13,{12,14,20}, false, false, false},
        //    {14,{13,15,4}, false, false, false},
        //    {15,{14,16,6}, false, false, false},
        //    {16,{15,17,20}, false, false, false},
        //    {17,{16,18,7}, false, false, false},
        //    {18,{17,19,9}, false, false, false},
        //    {19,{18,20,11}, false, false, false},
        //    {20,{13,16,19}, false, false, false},
        //};
        //temp playerdata
        //player_data player = {0, 5};
        game_data game = read_config();
        int safety = 0;
        while(true || safety < 999999999){
            game = move_or_shoot(game);
            safety++;
        }
    }
    while(restart == "y");
}