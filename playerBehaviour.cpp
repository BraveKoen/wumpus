#include "playerBehaviour.hpp"
#include "noise.hpp"

//This function will ask the user if they wish to restart.
void restart(){
    string res = "";
    printEffect("Do you wish to restart? Y/N: ", false);
    cin >> res;
    if(res == "n" ||res == "N" ||res == "no"||res == "No" ||res == "NO"){
        exit(0);
     }
    if(res == "y" ||res == "Y" ||res == "yes" ||res == "Yes" ||res == "YES"){
        exit(0);
    } 
}

//this function checks if the player has died.
void GameOver(game_data game){
    if(game.map[game.player.index].wumpus == true){
        printEffect("Oh no, you walked into the lair of the Wumpus, you are now it's meal. \nYou have died.", true);  
        restart();
    }
    else if(game.map[game.player.index].pit == true){
        printEffect("you fell into a bottomless pit aaaaaaaaaaaaaaaaah.... \nyou have died.", true);     
        restart();
    }
    else if(game.player.arrows == 0){
        printEffect("You are out of arrows, the wumpus will find you... eventually. \nyou have died.", true);
        restart();
    }
}

//this function removes the current wumpus and places anotherone in a random room.
game_data move_wumpus(game_data game){
    srand (time(NULL));
    int random_number = rand() % game.map.size() + 1;
    for(unsigned int i=0; i<game.map.size(); i++){
        if(game.map[i].wumpus == true){
            game.map[i].wumpus = false;
            break;
        }
    }
    game.map[random_number].wumpus = true;
    GameOver(game);
    return game;
}

//this function ask the player wich room they want to move to.
game_data player_move(game_data game){
    printEffect("Wich room would you like to move to: ", false);
    string new_room = "";
    cin >> new_room;
    int room2;
    for(unsigned int i=0; i < new_room.size();i++){
        if (new_room[i] == '0' ||new_room[i] == '1' || new_room[i] == '2' || new_room[i] == '3' || new_room[i] == '4' || new_room[i] == '5' || new_room[i] == '6' || new_room[i] == '7' || new_room[i] == '8' || new_room[i] == '9'){
            room2 = stoi(new_room);
        }
    }

    for(unsigned int i=0; i<game.map[game.player.index].neighbour.size(); i++){
        if(room2 == game.map[game.player.index].neighbour[i]){
            game.player.index = room2-1;
            //functiecall that checks for gameover or noises.
            GameOver(game);
            makeNoise(game);
            
        }
    }
    printEffect("you cannot move here.", true);
    return player_move(game);
}

//this function lets the player shoot at 1 of the neighbouring rooms and checks if the player has won or not.
game_data player_shoot(game_data game){
    printEffect("You have ", false);  cout << game.player.arrows; printEffect(" arrows left.", true);
    printEffect("Wich room would you like to shoot at? ", false);
    int room_to_shoot;
    cin >> room_to_shoot;
    for(unsigned int i=0; i<game.map[game.player.index].neighbour.size(); i++){
        if(room_to_shoot == game.map[game.player.index].neighbour[i] && game.map[room_to_shoot-1].wumpus == true){
            game.player.arrows--;
            printEffect("You shot the wumpus, you win!\n Press enter to close.", true);
            //!!! should go back to main menu
            exit(0);
        }
        else if(room_to_shoot == game.map[game.player.index].neighbour[i] && game.map[room_to_shoot-1].wumpus == false){
            game.player.arrows--;
            GameOver(game);
            printEffect("You missed, the wumpus has now moved to a random location.", true);
            game = move_wumpus(game);
            GameOver(game);
            return game;
        }
    }
    printEffect("You cannot shoot here.", true);
    return player_shoot(game);
}

//this function gives the player a choice if they want to move to a neighbouring room or if they wish to shoot an arrow.
game_data move_or_shoot(game_data game){
    printEffect("You are currently in room ", false); cout << game.map[game.player.index].number; printEffect(". The neighbouring rooms are: ", false);
    for(unsigned int i=0; i<game.map[game.player.index].neighbour.size(); i++){
        cout << game.map[game.player.index].neighbour[i];
        Sleep(50);   
        if(i < game.map[game.player.index].neighbour.size()-1){
            printEffect(", ", false);
        }
    }
    printEffect("\nDo you wish to Move or Shoot M/S: ", false);
    string choice = "";
    cin >> choice;
    
    if(choice == "m" || choice == "M"|| choice == "move"|| choice == "Move"){
        return player_move(game);
    }
    else if(choice == "s" || choice == "S"|| choice == "shoot"|| choice == "Shoot"){
        return player_shoot(game);
    }else{
        return move_or_shoot(game);
    }
}