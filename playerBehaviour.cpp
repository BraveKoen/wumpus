#include "playerBehaviour.hpp"

//this function ask the player wich room they want to move to.
game_data player_move(game_data game, string new_room = ""){
    printEffect("Wich room would you like to move to: ", false);
    if(new_room == ""){
        cin >> new_room;
    }
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
            gameOver(game);
            game = move_bat(game);
            return game;
        }
    }
    printEffect("you cannot move here.", true);
    return player_move(game);
}

//this function lets the player shoot at 1 of the neighbouring rooms and checks if the player has won or not.
game_data player_shoot(game_data game, int room_to_shoot = 0){
    printEffect("You have ", false);  cout << game.player.arrows; printEffect(" arrows left.", true);
    printEffect("Wich room would you like to shoot at? ", false);
    if (room_to_shoot == 0){
        cin >> room_to_shoot;
    }
    for(unsigned int i=0; i<game.map[game.player.index].neighbour.size(); i++){
        if(room_to_shoot == game.map[game.player.index].neighbour[i] && game.map[room_to_shoot-1].wumpus == true){
            game.player.arrows--;
            printEffect("You shot the wumpus, you win!\n Press enter to go back to main menu.", true);
            game.running = false;
            return game;
        }
        else if(room_to_shoot == game.map[game.player.index].neighbour[i] && game.map[room_to_shoot-1].wumpus == false){
            game.player.arrows--;
            gameOver(game);
            printEffect("You missed, the wumpus has now moved to a random location.", true);
            game = move_wumpus(game);
            gameOver(game);
            return game;
        }
    }
    printEffect("You cannot shoot here.", true);
    return player_shoot(game);
}

//this function will apear if the player decides to give up. The player can choose to reveal the location of the wumpus, bats and pits.
game_data give_up(game_data game, string choice = ""){
    printEffect("You decided to give up.\nWould you like to reveal the location of the Wumpus, Bats or Pits? W/B/P/NO: ", false);
    if(choice == ""){
        cin >> choice;
    }
    if(choice == "w" || choice == "W"|| choice == "wumpus"|| choice == "Wumpus"){
        for(unsigned int i=0; i<game.map.size();i++){
            if(game.map[i].wumpus == true){
                printEffect("there is a wumpus hidden in room ", false); cout << game.map[i].number; printEffect(".", true);
            }
        }
        give_up(game);
    }
    else if(choice == "b" || choice == "B"|| choice == "bats"|| choice == "Bats"){
        for(unsigned int i=0; i<game.map.size();i++){
            if(game.map[i].bat == true){
                printEffect("there is a bat hidden in room ", false); cout << game.map[i].number; printEffect(".", true);
            }
        }
        give_up(game);
    }
    else if(choice == "p" || choice == "P"|| choice == "pits"|| choice == "Pits"){
        for(unsigned int i=0; i<game.map.size();i++){
            if(game.map[i].pit == true){
                printEffect("there is a pit in room ", false); cout << game.map[i].number; printEffect(".", true);
            }
        }
        give_up(game);
    }
    else if(choice == "n" || choice == "N"|| choice == "no"|| choice == "NO"){
        game.running = false;
        return game;
    }else{
        printEffect("invalid input", true);
        return give_up(game);
    }
}

//this function gives the player a choice if they want to move to a neighbouring room or if they wish to shoot an arrow.
game_data move_or_shoot(game_data game, string choice){
    printEffect("You are currently in room ", false); cout << game.map[game.player.index].number; printEffect(". The neighbouring rooms are: ", false); 
    for(unsigned int i=0; i<game.map[game.player.index].neighbour.size(); i++){
        cout << game.map[game.player.index].neighbour[i];
        Sleep(50);
        game = ai_listen("neighbour", game.map[game.player.index].number, game.map[game.player.index].neighbour[i], game);   
        if(i < game.map[game.player.index].neighbour.size()-1){
            printEffect(", ", false);
        }
    }
    cout << endl;
    game = makeNoise(game);
    printEffect("Do you wish to Move, Shoot or Quit? M/S/Q: ", false);
    if(choice == ""){
        cin >> choice;
    }
    if(choice == "m" || choice == "M"|| choice == "move"|| choice == "Move"){
        return player_move(game);
    }
    else if(choice == "s" || choice == "S"|| choice == "shoot"|| choice == "Shoot"){
        return player_shoot(game);
    }
    else if(choice == "q" || choice == "Q"|| choice == "quit"|| choice == "Quit"){
        return give_up(game);
    }else{
        printEffect("invalid input", true);
        return move_or_shoot(game, "");
    }
}