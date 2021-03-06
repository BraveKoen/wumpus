#include "playerBehaviour.hpp"

//this function ask the player wich room they want to move to.
void player_move(game_data & game, string new_room){
    printEffect("Wich room would you like to move to: ", false);
    if(new_room == ""){//if the ai is playing, the user input will be given directly, so there will be no use for a cin.
        cin >> new_room;
    }else{
        cout << new_room<< endl;
    }
    int room2;
    for(unsigned int i=0; i < new_room.size();i++){//this loop checks if the user has given a valid input, a integer.
        if (new_room[i] == '0' ||new_room[i] == '1' || new_room[i] == '2' || new_room[i] == '3' || new_room[i] == '4' || new_room[i] == '5' || new_room[i] == '6' || new_room[i] == '7' || new_room[i] == '8' || new_room[i] == '9'){
            room2 = stoi(new_room);
        }
    }
    
    for(unsigned int i=0; i<game.map[game.player.index].neighbour.size(); i++){//this loop checks if the given room is a valid room to move to. if it is, the player will be put there
        if(room2 == game.map[game.player.index].neighbour[i]){
            game.player.index = room2-1;
            game.ai.player.index = room2-1;
            game.player.score = game.player.score -10; // lowers the score by 10
            gameOver(game);//these function calls check if the player has lost
            move_bat(game);
            return;
        }
    }
    printEffect("you cannot move here.", true);//if given an invalid input, the question will be asked aigan.
    player_move(game, "");
    return;
}

//this function lets the player shoot at 1 of the neighbouring rooms and checks if the player has won or not.
void player_shoot(game_data& game, string room_to_shoot){
    printEffect("You have ", false);  cout << game.player.arrows; printEffect(" arrows left.", true);
    printEffect("Wich room would you like to shoot at? ", false);

    if(room_to_shoot == ""){//if the ai is playing, the user input will be given directly, so there will be no use for a cin.
        cin >> room_to_shoot;
    }else{
        cout << room_to_shoot << endl;
    }
    int room2;
    for(unsigned int i=0; i < room_to_shoot.size();i++){//this loop checks if the user has given a valid input, a integer.
        if (room_to_shoot[i] == '0' ||room_to_shoot[i] == '1' || room_to_shoot[i] == '2' || room_to_shoot[i] == '3' || room_to_shoot[i] == '4' || room_to_shoot[i] == '5' || room_to_shoot[i] == '6' || room_to_shoot[i] == '7' || room_to_shoot[i] == '8' || room_to_shoot[i] == '9'){
            room2 = stoi(room_to_shoot);
        }
    }
    for(unsigned int i=0; i<game.map[game.player.index].neighbour.size(); i++){//this loop checks if the player has shot the wumpus. if they have, the score will be added to the database.
        if(room2 == game.map[game.player.index].neighbour[i] && game.map[room2-1].wumpus == true){
            game.player.arrows--;
            int score = game.player.score;
            if(score <0){
                score = 0;
            }
            string playername = "";
            printEffect("You shot the wumpus, you win!", true);
            printEffect("please enter your name (no spaces): ",false);
            cin >> playername;
            printEffect("your personal score is: ",false);
            cout << score << endl;
            statistics(game, playername); // will look if the current score is better than the high score and if so, will update it
            game.menuOption = "";
            game.running = false;//this call will send the player back to the main menu
            return;
        }
        
        else if(room2 == game.map[game.player.index].neighbour[i] && game.map[room2-1].wumpus == false){//if the player misses the wumpus, the wumpus will move to a random loaction, the player will also lose 1 arrow
            game.player.arrows--; // lowers the amount of arrows by 1
            game.player.score = game.player.score -25; // lowers the score by 25
            gameOver(game);
            printEffect("You missed, the wumpus has now moved to a random location.", true);
            move_wumpus(game);
            gameOver(game);
            return;
        }
    }
    printEffect("You cannot shoot here.", true);//if given an invalid input, the question will be given aigan.
    player_shoot(game, "");
    return;
}

//this function will apear if the player decides to give up. The player can choose to reveal the location of the wumpus, bats and pits.
void give_up(game_data& game, string choice = ""){
    printEffect("You decided to give up.\nWould you like to reveal the location of the Wumpus, Bats or Pits? W/B/P/NO: ", false);
    if(choice == ""){//if the ai is playing, the user input will be given directly, so there will be no use for a cin.
        cin >> choice;
    }else{
        cout << choice<< endl;
    }
    if(choice == "w" || choice == "W"|| choice == "wumpus"|| choice == "Wumpus"){//if the player wishes to reveal the location of the wumpus, the location will be printed
        for(unsigned int i=0; i<game.map.size();i++){
            if(game.map[i].wumpus == true){
                printEffect("there is a wumpus hidden in room ", false); cout << game.map[i].number; printEffect(".", true);
            }
        }
        give_up(game);
        return;
    } 
    else if(choice == "b" || choice == "B"|| choice == "bats"|| choice == "Bats"){//if the player wishes to reveal the location of the bats, the location will be printed
        for(unsigned int i=0; i<game.map.size();i++){
            if(game.map[i].bat == true){
                printEffect("there is a bat hidden in room ", false); cout << game.map[i].number; printEffect(".", true);
            }
        }
        give_up(game);
        return;
    }
    else if(choice == "p" || choice == "P"|| choice == "pits"|| choice == "Pits"){//if the player wishes to reveal the location of the pits, the location will be printed
        for(unsigned int i=0; i<game.map.size();i++){
            if(game.map[i].pit == true){
                printEffect("there is a pit in room ", false); cout << game.map[i].number; printEffect(".", true);
            }
        }
        give_up(game);
        return;
    }
    else if(choice == "n" || choice == "N"|| choice == "no"|| choice == "NO"){//if the player wishes to give up completeley they will go back to the main menu
        game.menuOption = "";
        game.running = false;
        return;
    }else{
        printEffect("invalid input", true);//if given an invalid input, the question will be asked aigan.
        give_up(game);
        return;
    }
}

//this function gives the player a choice if they want to move to a neighbouring room or if they wish to shoot an arrow.
void move_or_shoot(game_data & game, string choice, string choice_room){
    printEffect("You are currently in room ", false); cout << game.map[game.player.index].number; printEffect(". The neighbouring rooms are: ", false); 
    for(unsigned int i=0; i<game.map[game.player.index].neighbour.size(); i++){//this forloop couts the neighbouring rooms to the room the player is in.
        cout << game.map[game.player.index].neighbour[i];
        Sleep(50);
        ai_listen("neighbour", game.player.index, game.map[game.player.index].neighbour[i], game);   
        if(i < game.map[game.player.index].neighbour.size()-1){
            printEffect(", ", false);
        }
    }
    cout << endl;
    makeNoise(game);
    printEffect("Do you wish to Move, Shoot or Quit? M/S/Q: ", false);
    if(choice == ""){//if the ai is playing, the user input will be given directly, so there will be no use for a cin.
        cin >> choice;
    }else{
        cout << choice<< endl;
    }
    if(choice == "m" || choice == "M"|| choice == "move"|| choice == "Move"){//if the player wishes to move, the corresponding function will be called
      player_move(game, choice_room);
      return;
    }
    else if(choice == "s" || choice == "S"|| choice == "shoot"|| choice == "Shoot"){//if the player wishes to shoot, the corresponding function will be called
        player_shoot(game, choice_room);
        return;
    }
    else if(choice == "q" || choice == "Q"|| choice == "quit"|| choice == "Quit"){//if the player wishes to give up, the corresponding function will be called
        give_up(game);
        return;
    }else{
        printEffect("invalid input", true);//if given an invalid input, the question will be asked aigan.
        move_or_shoot(game, "", "");
        return;
    }
}