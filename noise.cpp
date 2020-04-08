#include "noise.hpp"
using namespace std;

//this function checks if there are noises nearby and lets the player know
void makeNoise(game_data & game) {
  bool wumpus = false;
  bool pit = false;
  bool bat = false;

  vector<int> neigh = game.map[game.player.index].neighbour; //grab all neighbours from the current room
  for (unsigned int i = 0; i < neigh.size(); i++) {          // loop through all neigbour roomes for a wumpus, bat or pit
    vector<int> neigh_second = game.map[neigh[i] - 1].neighbour;
    if (game.map[neigh[i] - 1].wumpus == true) {
      wumpus = true;
    } else {  // because we need to tell if the wumpus is 2 rooms away there is
              // a second for loop, this forloop will loop through all the neigbours from the first neigbour
      for (unsigned int j = 0; j < neigh_second.size(); j++) {
        if (game.map[neigh_second[j] - 1].wumpus == true) {
          wumpus = true;
        }
      }
    }
    if (game.map[neigh[i] - 1].pit == true) {
      pit = true;
    }
    if (game.map[neigh[i] - 1].bat == true) {
      bat = true;
    }
  }
  if(pit){
    printEffect("I feel a draft.", true);
    ai_listen("draft",game.player.index, pit, game);
  }
  if(bat){
    printEffect("I hear the flapping of wings.", true);
    ai_listen("flapping",game.player.index, bat, game);
  }
  if(wumpus){
    printEffect("I smell somethings foul.",true);
    ai_listen("smell",game.player.index, wumpus, game);
  }
  return;
}
