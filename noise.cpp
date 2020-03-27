#include "noise.hpp"
using namespace std;

//this function checks if there are noises nearby and lets the player know
void makeNoise(game_data game) {
  vector<int> neigh = game.map[game.player.index].neighbour;
  for (unsigned int i = 0; i < neigh.size(); i++) {
    vector<int> neigh_second = game.map[neigh[i] - 1].neighbour;
    if (game.map[neigh[i] - 1].wumpus == true) {
      printEffect("I smell something foul.", true);
    } else {
      for (unsigned int j = 0; j < neigh_second.size(); j++) {
        if (game.map[neigh_second[j] - 1].wumpus == true) {
          printEffect("I smell something foul.", true);
        }
      }
    }
    if (game.map[neigh[i] - 1].pit == true) {
      printEffect("I feel a draft.", true);
    }
    if (game.map[neigh[i] - 1].bat == true) {
      printEffect("Soon you will be relocated.", true);
    }
  }
}
