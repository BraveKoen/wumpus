#include "noise.hpp"
using namespace std;

//this function checks if there are noises nearby and lets the player know
void makeNoise(game_data & game) {
  bool wumpus = false;
  bool pit = false;
  bool bat = false;

  vector<int> neigh = game.map[game.player.index].neighbour;
  for (unsigned int i = 0; i < neigh.size(); i++) {
    vector<int> neigh_second = game.map[neigh[i] - 1].neighbour;
    if (game.map[neigh[i] - 1].wumpus == true) {
      wumpus = true;
    } else {
      for (unsigned int j = 0; j < neigh_second.size(); j++) {
        if (game.map[neigh_second[j] - 1].wumpus == true && wumpus) {
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
    ai_listen("draft",game.player.index + 1, pit, game);
  }
  if(bat){
    printEffect("I hear the flapping of wings.", true);
    ai_listen("flapping",game.player.index + 1, bat, game);
  }
  if(wumpus){
    printEffect("I smell somethings foul.",true);
    ai_listen("smell",game.player.index + 1, wumpus, game);
  }
  return;
}
