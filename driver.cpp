#include <ctime>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include <vector>

#include "game.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"



/*
typedef std::vector<MyObject> Array;
typedef std::vector<Array> TwoDArray;
*/

using namespace std;

//check if smaller than a 4x4
int check_cave_size(int cave_size);
int check_debug(string debug);
void printBoard(int cave_size);


int main(int argc, char**argv){
    int is_debug;
    int cave_size;
    if(argc != 3)
    {
        cout << "\n\nYou entered the incorrect amount of arguments." << endl;
        cave_size = check_cave_size(0);
        is_debug = check_debug("trash");

    }
    else
    {
        cave_size = atoi(argv[1]);
        is_debug = check_debug(argv[2]);
    }
    cave_size = check_cave_size(cave_size);
    //cout << "CAVE SIZE: " << cave_size << endl << endl;
    //cout << is_debug << endl << endl;

    Game game1 = Game(cave_size, is_debug);
    //game1.populate_board();
    //game1.test_print_vector();
    //game1.printBoard();
    //game1.check_game_state();


    game1.populate_board();
    int error = 2;
    while(error == 2)
    {
        game1.printBoard();
        game1.player_turn();
        game1.room_stuff();
        error = game1.check_game_state();
        if(error != 2)
        {
            game1.destroy_rooms();
        }
    }

    /*
    Gold g1;
    Gold *gold = &g1;
    Room room1;
    room1.set_room_event(gold);
    cout << room1.get_room_event()->get_encounter() << endl;
    */


    /*
    if (room1.get_room_event() == nullptr){
        cout << "IT IS NULL" << endl;
    }
    else{
        cout << "IT AINT NULL EVENT IS SOMETHING" << endl;
    }
    */
    return 0;
}


int check_cave_size(int cave_size)
{
    while(cave_size < 4)
    {
        if(cave_size < 4)
        {
            cout << "\n\nYour value for the cave size was too small." << endl << "Please enter a value greater than or equal to 4." << endl << "Input: ";
            cin >> cave_size;
        }
    }
    return cave_size;
}


int check_debug(string debug)
{
    while(debug != "true" && debug != "false")
    {
            cout << "\n\n"  << "Please enter 'true' if you want to run in debug mode, or 'false' to play normally" << endl << "Input: ";
            cin >> debug;
    }
    if(debug == "true")
    {
        return 1;
    }
    else if(debug == "false")
    {
        return 0;
    }
    else
    {
        return 69;
    }
}
