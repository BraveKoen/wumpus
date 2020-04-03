#include "enemyBehaviour.hpp"

// This function will ask the user if they wish to restart.
void restart(game_data & game) {
  string res = "";
  printEffect("Do you wish to restart? Y/N: ", false);
  cin >> res;
  if (res == "n" || res == "N" || res == "no" || res == "No" || res == "NO") {
    game.running = false;
    return;
  } else if (res == "y" || res == "Y" || res == "yes" || res == "Yes" || res == "YES") {
    game.running = false;
    return;
  } else {
    printEffect("that is not a valid answer", true);
    restart(game);
  }
}

// this function checks if the player has died.
void gameOver(game_data & game) {
  if (game.map[game.player.index].wumpus == true) {
    printEffect(
      "Oh no, you walked into the lair of the Wumpus, you are now it's meal.\nYou have died.", true);
      ai_listen("wumpus",game.player.index + 1, true, game);
    restart(game);
  } else if (game.map[game.player.index].pit == true) {
    printEffect(
        "you fell into a bottomless pit aaaaaaaaaaaaaaaaah.... \nyou have died.", true);
        ai_listen("pit",game.player.index + 1, true, game);
    restart(game);
  } else if (game.player.arrows == 0) {
    printEffect(
        "You are out of arrows, the wumpus will find you... eventually. \nyou have died.", true);
    restart(game);
  }
  return;
}

// this function removes the current wumpus and places anotherone in a random
// room.
void move_wumpus(game_data & game) {
  srand(time(NULL));
  int random_number = rand() % game.map.size() - 1;
  for (unsigned int i = 0; i < game.map.size(); i++) {
    if (game.map[i].wumpus == true) {
      game.map[i].wumpus = false;
      break;
    }
  }
  game.map[random_number].wumpus = true;
  gameOver(game);
  return;
}

void move_bat(game_data & game){
  if(game.map[game.player.index].bat){
    srand(time(NULL));
    //game = ai_listen("bat",game.player.index + 1, true, game);
    int random_number = rand() % game.map.size() - 1;
    game.player.index = random_number;
    printEffect("Flap Flap away!",true);
  }
  return;
}