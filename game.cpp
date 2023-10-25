#include <ctime>
#include <string>
#include <stdio.h>      /* printf, nullptr */
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


using namespace std;


Game::Game()
{
    gold = new Gold();
    wumpus = new Wumpus();
    pit1 = new Pit();
    pit2 = new Pit();
    bats1 = new Bats();
    bats2 = new Bats();

    has_gold = 0;
    wumpus_slain = 0;
    num_arrows = 3;
    player_x = 0;
    player_y = 0;
    spawn_x = 0;
    spawn_y = 0;
    is_debug = 0;
    cave_size = 0;

}

Game::Game(int x, int y)
{
  /*  gold = new Gold();
    wumpus = new Wumpus();
    pit1 = new Pit();
    pit2 = new Pit();
    bats1 = new Bats();
    bats2 = new Bats(); */

    has_gold = 0;
    wumpus_slain = 0;
    player_dead = 0;
    num_arrows = 3;

    player_x = 0;
    player_y = 0;

    spawn_x = 0;
    spawn_y = 0;

    arrow_x = 0;
    arrow_y = 0;

    wumpus_x = 0;
    wumpus_y = 0;

    is_debug = y;
    cave_size = x ; //used to be just x

    vector <vector<Room>> temp(cave_size, vector<Room>(cave_size));
    cave = temp;
}


Game::Game(const Game &game2)
{
    cave_size = game2.cave_size;
}


Game::~Game()
{
  //delete gold;
  //delete wumpus;
  //delete pit1;
  //delete  pit2;
  //delete  bats1;
  //delete  bats2;
/*
  for (int i = 0; i < cave_size; ++i){
    for (int j = 0; j < cave_size; ++j){
        delete[] cave[i][j];
    }
    delete[] cave[i];
}*/
  cave.clear();
}


int Game::get_cave_size()
{
    return cave_size;
}


void Game::set_cave_size(int x)
{
    cave_size = x;
}


void Game::test_print_vector()
{
    int count = 1;
    for(int i = 0; i < cave_size; i++)
    {
        for(int j = 0; j < cave_size; j++)
        {
            cave[i][j].set_room_num(count);
            count ++;
        }
    }
    for(int i = 0; i < cave_size; i++)
    {
        for(int j = 0; j < cave_size; j++)
        {
            cout << cave[i][j].get_room_num() << "    ";
        }
        cout<< endl;
    }
}


void Game::printBoard()
{
  //cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\n\n Number of arrows: " << num_arrows << endl;
    if (is_debug == 0)
    {
        printBoard_normal();
    }
    else if(is_debug == 1)
    {
        printBoard_debug();
    }
}


void Game::printBoard_normal()
{
    for (int i = 0; i < cave_size; i++)
    {
        for (int j = 0; j < cave_size; j++)
            cout << "+________" ;
        cout << "+" << endl;
        for (int j = 0; j < cave_size; j++)
            cout << "|        " ;
        cout << "|" << endl;
        for (int j = 0; j < cave_size; j++)
        {
            if(i == player_x && j == player_y)
            {
                cout << "|    *   " ;
            }
            else
            {
                cout << "|        " ;
            }
        }
        cout << "|" << endl;
        for (int j = 0; j < cave_size; j++)
            cout << "|        " ;
        cout << "|" << endl;
        for (int j = 0; j < cave_size; j++)
            cout << "|        " ;
        cout << "|" << endl;
    }
    for (int j = 0; j < cave_size; j++)
        cout << "+________" ;
    cout << "+" << endl;
}


void Game::printBoard_debug()
{
    for (int i = 0; i < cave_size; i++)
    {
        for (int j = 0; j < cave_size; j++)
            cout << "+________" ;
        cout << "+" << endl;
        for (int j = 0; j < cave_size; j++)
            cout << "|        " ;
        cout << "|" << endl;
        for (int j = 0; j < cave_size; j++)
        {
            if(i == player_x && j == player_y)
            {
                cout << "|    *   " ;
            }
            else
            {
                cout << "|        " ;
            }
        }
        cout << "|" << endl;
        for (int j = 0; j < cave_size; j++)
        {
            //cout << "|     " << i << " " << j;
            cout << event_check(i, j);
        }
        cout << "|" << endl;
        for (int j = 0; j < cave_size; j++)
            cout << "|        " ;
        cout << "|" << endl;
    }
    for (int j = 0; j < cave_size; j++)
        cout << "+________" ;
    cout << "+" << endl;
}


void Game::populate_board()
{
    srand(time(NULL));
    player_x = (rand() % cave_size );
    //cout << "player x: " << player_x << endl;
    player_y = (rand() % cave_size );
    //cout << "player y: " << player_y << endl;
    spawn_x = player_x;
    //cout << "spawn x: " << spawn_x << endl;
    spawn_y = player_y;
    //cout << "spawn y: " << spawn_y << endl;
    populate_gold();
    populate_wumpus();
    populate_bats();
    populate_pits();
}


void Game::populate_gold()
{
    int error = 1;
    while(error != 0)
    {
        int randomizerx = (rand() % cave_size);
        int randomizery = (rand() % cave_size);
        if(cave[randomizerx][randomizery].get_room_event() == nullptr && !((randomizerx == spawn_x) && (randomizery == spawn_y)))
        {
            cave[randomizerx][randomizery].set_room_event(new Gold());
            //cout << cave[randomizerx][randomizery].get_room_event()->get_encounter() << endl;
            //cout << "x of gold: " << randomizerx << endl;
            //cout << "y of gold: " << randomizery << endl;
            error = 0;
        }
    }
}


void Game::populate_wumpus()
{
    int error = 1;
    while(error != 0)
    {
        int randomizerx = (rand() % cave_size);
        int randomizery = (rand() % cave_size);
        if(cave[randomizerx][randomizery].get_room_event() == nullptr && !((randomizerx == spawn_x) && (randomizery == spawn_y)))
        {
            cave[randomizerx][randomizery].set_room_event(new Wumpus());
            wumpus_x = randomizerx;
            wumpus_y = randomizery;
            //cout << cave[randomizerx][randomizery].get_room_event()->get_encounter() << endl;
            //cout << "x of wumpus: " << randomizerx << endl;
            //cout << "y of wumpus: " << randomizery << endl;
            error = 0;
        }
    }
}


void Game::populate_bats()
{
    int error = 1;
    while(error != 0)
    {
        int randomizerx = (rand() % cave_size);
        int randomizery = (rand() % cave_size);
        if(cave[randomizerx][randomizery].get_room_event() == nullptr && !((randomizerx == spawn_x) && (randomizery == spawn_y)))
        {
            cave[randomizerx][randomizery].set_room_event(new Bats());
            //cout << cave[randomizerx][randomizery].get_room_event()->get_encounter() << endl;
            //cout << "x of bats1: " << randomizerx << endl;
            //cout << "y of bats1: " << randomizery << endl;
            error = 0;
        }
    }
    int error2 = 1;
    while(error2 != 0)
    {
        int randomizerx = (rand() % cave_size);
        int randomizery = (rand() % cave_size);
        if(cave[randomizerx][randomizery].get_room_event() == nullptr && !((randomizerx == spawn_x) && (randomizery == spawn_y)))
        {
            cave[randomizerx][randomizery].set_room_event(new Bats());
            //cout << cave[randomizerx][randomizery].get_room_event()->get_encounter() << endl;
            //cout << "x of bats2: " << randomizerx << endl;
            //cout << "y of bats2: " << randomizery << endl;
            error2 = 0;
        }
    }
}


void Game::populate_pits()
{
    int error = 1;
    while(error != 0)
    {
        int randomizerx = (rand() % cave_size);
        int randomizery = (rand() % cave_size);
        if(cave[randomizerx][randomizery].get_room_event() == nullptr && !((randomizerx == spawn_x) && (randomizery == spawn_y)))
        {
            cave[randomizerx][randomizery].set_room_event(new Pit());
            //cout << cave[randomizerx][randomizery].get_room_event()->get_encounter() << endl;
            //cout << "x of pit1: " << randomizerx << endl;
            //cout << "y of pit1: " << randomizery << endl;
            error = 0;
        }
    }
    int error2 = 1;
    while(error2 != 0)
    {
        int randomizerx = (rand() % cave_size);
        int randomizery = (rand() % cave_size);
        if(cave[randomizerx][randomizery].get_room_event() == nullptr && !((randomizerx == spawn_x) && (randomizery == spawn_y)))
        {
            cave[randomizerx][randomizery].set_room_event(new Pit());
            //cout << cave[randomizerx][randomizery].get_room_event()->get_encounter() << endl;
            //cout << "x of pit2: " << randomizerx << endl;
            //cout << "y of pit2: " << randomizery << endl;
            error2 = 0;
        }
    }
}

string Game::event_check(int &i, int &j)
{
    //cout << "|     " << i << " " << j;
    string print;
    if(cave[i][j].get_room_event() == nullptr)
    {
        if(i == spawn_x && j == spawn_y)
        {
            print = "|    s   ";
            return print;
        }
        else
        {
            print = "|        ";
            return print;
        }
    }
    else
    {
      //cout << "|     " << i << " " << j;
/*
        if (!(i < cave_size && i > 0)){
          cout << "|     " << i << " " << j;
        }
        else if (!(j < cave_size && j > 0)){
          cout << "|     " << i << " " << j;
        } */
        if((cave[i][j].get_room_event()->get_eventID()) == 1)
        {
            print = "|    $   ";
            return print;
        }
        else if((cave[i][j].get_room_event()->get_eventID()) == 2)
        {
            print = "|   OwO  ";
            return print;
        }
        else if((cave[i][j].get_room_event()->get_eventID()) == 3)
        {
            print = "|    V   ";
            return print;
        }
        else if((cave[i][j].get_room_event()->get_eventID()) == 4)
        {
            print = "|    O   ";
            return print;
        }
        else
        {
            print = "|        ";
            return print;
        }
        //cout << "|     " << cave[i][j].get_room_event()->get_eventID() << "  ";
        //print = "|        ";
        //return print;
    }
}


int Game::check_game_state()
{
    if(has_gold == 1 && wumpus_slain == 1 && ((player_x == spawn_x) && (player_y == spawn_y)))
    {
        cout << "You escape with the gold and the wumpus being slain...\nYou won...\n\n";
        return 0;
    }
    else if(has_gold == 1 && wumpus_slain == 0 && ((player_x == spawn_x) && (player_y == spawn_y)))
    {
        cout << "You escape with the gold...\nYou won...\n\n";
        return 0;
    }
    else if(player_dead == 1)
    {
        cout << "You are dead...\nYou lost...\n\n";
        return 1;
    }
    else
    {
        return 2;
    }

}


/* Original function that would ininitly loop when the shoot input was not a number
void Game::player_turn()
{
    if (wumpus_slain == 0 && num_arrows > 0)
    {
        int shoot;
        cout << "Would you like to shoot an arrow?\nEnter ---> 1 <--- to shoot an arrow\nEnter ---> 0 <--- to SKIP shooting an arrow\nInput: ";
        cin >> shoot;
        if(shoot == 1)
        {
            player_shoot();
            player_move();
        }
        else
        {
            player_move();
        }
    }
    else
    {
        player_move();
    }
}
*/


void Game::player_turn()
{
    if (wumpus_slain == 0 && num_arrows > 0)
    {   int error = 1;
        while (error == 1)
            {
            string shoot;
            cout << "Would you like to shoot an arrow?\nEnter ---> 1 <--- to shoot an arrow\nEnter ---> 0 <--- to SKIP shooting an arrow\nInput: ";
            cin >> shoot;
            if(shoot == "1")
            {
                error = 0;
                player_shoot();
                player_move();
            }
            else if (shoot == "0")
            {
                error = 0;
                player_move();
            }
        }
    }
    else
    {
        player_move();
    }
}


void Game::player_shoot()
{
    arrow_x = player_x;
    arrow_y = player_y;
    int error = 1;
    string shot;
    while(error == 1)
    {
        cout << "\n\nPlease enter the direction in which you want to shoot your arrow\nEnter ---> w <--- to shoot North/Up\nEnter ---> a <--- to shoot West/Left\nEnter ---> s <--- to shoot South/Down\nEnter ---> d <--- to shoot East/Right\nInput: ";
        cin >> shot;
        if(shot == "w")
        {
            if ((player_x - 1) < cave_size && (player_x - 1) >= 0)
            {
                arrow_shot(1);
                error = 0;
            }
            else
            {
                cout << "\n\nYour shot would have went out of bounds.\nPlease try again.";
            }
        }
        else if(shot == "a")
        {
            if ((player_y - 1) < cave_size && (player_y - 1) >= 0)
            {
                arrow_shot(2);
                error = 0;
            }
            else
            {
                cout << "\n\nYour shot would have went out of bounds.\nPlease try again.";
            }
        }
        else if(shot == "s")
        {
            if ((player_x + 1) < cave_size && (player_x + 1) >= 0)
            {
                arrow_shot(3);
                error = 0;
            }
            else
            {
                cout << "\n\nYour shot would have went out of bounds.\nPlease try again.";
            }
        }
        else if(shot == "d")
        {
            if ((player_y + 1) < cave_size && (player_y + 1) >= 0)
            {
                arrow_shot(4);
                error = 0;
            }
            else
            {
                cout << "\n\nYour shot would have went out of bounds.\nPlease try again.";
            }
        }
    }
    num_arrows --;
}


void Game::player_move()
{
    int error = 1;
    string move;
    while(error == 1)
    {
        cout << "\n\nPlease enter the direction in which you want to move\nEnter ---> w <--- to move North/Up\nEnter ---> a <--- to move West/Left\nEnter ---> s <--- to move South/Down\nEnter ---> d <--- to move East/Right\nInput: ";
        cin >> move;
        if(move == "w")
        {
            if ((player_x - 1) < cave_size && (player_x - 1) >= 0)
            {
                player_x --;
                error = 0;
            }
            else
            {
                cout << "\n\nThe move you chose to make would have went out of bounds.\nPlease try again.";
            }
        }
        else if(move == "a")
        {
            if ((player_y - 1) < cave_size && (player_y - 1) >= 0)
            {
                player_y --;
                error = 0;
            }
            else
            {
                cout << "\n\nThe move you chose to make would have went out of bounds.\nPlease try again.";
            }
        }
        else if(move == "s")
        {
            if ((player_x + 1) < cave_size && (player_x + 1) >= 0)
            {
                player_x ++;
                error = 0;
            }
            else
            {
                cout << "\n\nThe move you chose to make would have went out of bounds.\nPlease try again.";
            }
        }
        else if(move == "d")
        {
            if ((player_y + 1) < cave_size && (player_y + 1) >= 0)
            {
                player_y ++;
                error = 0;
            }
            else
            {
                cout << "\n\nThe move you chose to make would have went out of bounds.\nPlease try again.";
            }
        }
    }
}


void Game::room_stuff()
{
    if(cave[player_x][player_y].get_room_event() == nullptr)
    {
        cout << "\n\n\n\n\n\nYou enter an empty room...\n\n\n\n\n\n";
        find_perceptions();
    }
    else
    {
        if((cave[player_x][player_y].get_room_event()->get_eventID()) == 1)
        {
            cout << cave[player_x][player_y].get_room_event()->get_encounter() << endl;
            has_gold = 1;
            cave[player_x][player_y].destroy_room_event();
            find_perceptions();
        }
        else if((cave[player_x][player_y].get_room_event()->get_eventID()) == 2)
        {
            cout << cave[player_x][player_y].get_room_event()->get_encounter() << endl;
            player_dead = 1;
        }
        else if((cave[player_x][player_y].get_room_event()->get_eventID()) == 3)
        {
            cout << cave[player_x][player_y].get_room_event()->get_encounter() << endl;
            bat_carry();
        }
        else if((cave[player_x][player_y].get_room_event()->get_eventID()) == 4)
        {
            cout << cave[player_x][player_y].get_room_event()->get_encounter() << endl;
            player_dead = 1;
        }
    }
}


void Game::bat_carry()
{
    int error = 1;
    while(error != 0)
    {
        int randomizerx = (rand() % cave_size);
        int randomizery = (rand() % cave_size);
        if(cave[randomizerx][randomizery].get_room_event() == nullptr && !((randomizerx == spawn_x) && (randomizery == spawn_y)) && !((randomizerx == player_x) && (randomizery == player_y)))
        {
            player_x = randomizerx;
            player_y = randomizery;
            error = 0;
        }
    }
}


void Game::destroy_rooms()
{
  for (int i = 0; i < cave_size; i++)
  {
      for (int j = 0; j < cave_size; j++)
      {
          cave[i][j].destroy_room_event();
      }
  }
}


void Game::find_perceptions()
{
    if ((player_x - 1) < cave_size && (player_x - 1) >= 0)
    {
        if ((!(cave[player_x - 1][player_y].get_room_event() == nullptr)))
        {
            cout << cave[player_x - 1][player_y].get_room_event()->get_perception() << endl;
        }
    }
    if ((player_x + 1) < cave_size && (player_x + 1) >= 0)
    {
        if ((!(cave[player_x + 1][player_y].get_room_event() == nullptr)))
        {
            cout << cave[player_x + 1][player_y].get_room_event()->get_perception() << endl;
        }
    }
    if ((player_y - 1) < cave_size && (player_y - 1) >= 0)
    {
        if ((!(cave[player_x][player_y - 1].get_room_event() == nullptr)))
        {
            cout << cave[player_x][player_y - 1].get_room_event()->get_perception() << endl;
        }
    }
    if ((player_y + 1) < cave_size && (player_y + 1) >= 0)
    {
        if ((!(cave[player_x][player_y + 1].get_room_event() == nullptr)))
        {
            cout << cave[player_x][player_y + 1].get_room_event()->get_perception() << endl;
        }
    }
}


void Game::arrow_shot(int x)
{
    int i = 1;
    int hit = 0;
    int hit_x = 0;
    int hit_y = 0;
    while((hit == 0) && (i < 4) && (i < cave_size && i >= 0))//for (int i = 1; i < 4; i++)
    {
        if(x == 1)
        {
            if(arrow_x - i == wumpus_x && arrow_y == wumpus_y)
            {
                    hit_x += arrow_x - i;
                    hit_y += arrow_y;
                    hit += 1;
                    //cout << hit_x << endl;
                    //cout << hit_y << endl;
            }
        }
        else if(x == 2)
        {
            if(arrow_x == wumpus_x && arrow_y - i == wumpus_y)
            {
                    hit_x += arrow_x;
                    hit_y += arrow_y - i;
                    hit += 1;
                    //cout << hit_x << endl;
                    //cout << hit_y << endl;
            }
        }
        else if(x == 3)
        {
            if(arrow_x + i == wumpus_x && arrow_y == wumpus_y)
            {
                    hit_x += arrow_x + i;
                    hit_y += arrow_y;
                    hit += 1;
                    //cout << hit_x << endl;
                    //cout << hit_y << endl;
            }
        }
        else if(x == 4)
        {
          if(arrow_x == wumpus_x && arrow_y + i == wumpus_y)
          {
                  hit_x += arrow_x;
                  hit_y += arrow_y + i;
                  hit += 1;
                  //cout << hit_x << endl;
                  //cout << hit_y << endl;
          }
        }
        /*if(x == 1)
        {
            if((!(cave[arrow_x - i][arrow_y].get_room_event() == nullptr)))
            {
                if((cave[arrow_x - i][arrow_y].get_room_event()->get_eventID()) == 2)
                {
                    hit_x += arrow_x - i;
                    hit_y += arrow_y;
                    hit += 1;
                    //cout << hit_x << endl;
                    //cout << hit_y << endl;
                }
            }
        }
        else if(x == 2)
        {
            if((!(cave[arrow_x][arrow_y - i].get_room_event() == nullptr)))
            {
                if((cave[arrow_x][arrow_y - i].get_room_event()->get_eventID()) == 2)
                {
                    hit_x += arrow_x;
                    hit_y += arrow_y - i;
                    hit += 1;
                    //cout << hit_x << endl;
                    //cout << hit_y << endl;
                }
            }
        }
        else if(x == 3)
        {
            if((!(cave[arrow_x + i][arrow_y].get_room_event() == nullptr)))
            {
                if((cave[arrow_x + i][arrow_y].get_room_event()->get_eventID()) == 2)
                {
                    hit_x += arrow_x + i;
                    hit_y += arrow_y;
                    hit += 1;
                    //cout << hit_x << endl;
                    //cout << hit_y << endl;
                }
            }
        }
        else if(x == 4)
        {
            if((!(cave[arrow_x][arrow_y + i].get_room_event() == nullptr)))
            {
                if((cave[arrow_x][arrow_y + i].get_room_event()->get_eventID()) == 2)
                {
                    hit_x += arrow_x;
                    hit_y += arrow_y + i;
                    hit += 1;
                    //cout << hit_x << endl;
                    //cout << hit_y << endl;
                }
            }
        } */
    i++;
    }
    if(hit == 0)
    {
        wumpus_move();
    }
    else if (hit == 1)
    {
        cout << "\n\nYou hear a loud screeching noise followed by a thud, and then silence...\nYour arrow hit and killed the Wumpus!!!";
        wumpus_slain = 1;
        cave[wumpus_x][wumpus_y].destroy_room_event();
    }
}


void Game::wumpus_move()
{
    int randomizer = (rand() % 4);
    if(randomizer != 1)
    {
        cout << "\n\nYou missed your shot...\nThe Wumpus has woken up and moved to a random room...";
        cave[wumpus_x][wumpus_y].destroy_room_event();
        populate_wumpus();
    }
    else
    {
        cout << "\n\nYou missed your shot...\nBut the Wumpus did not wake up...";
    }
}
