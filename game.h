#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include <vector>

#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

using namespace std;

class Game{
  private:
      bool has_gold;
      bool wumpus_slain;
      bool player_dead;
      int num_arrows;

      int player_x;
      int player_y;

      int spawn_x;
      int spawn_y;

      int arrow_x;
      int arrow_y;

      int wumpus_x;
      int wumpus_y;

      int is_debug;
      int cave_size;

      Gold *gold;
      Wumpus *wumpus;
      Pit *pit1;
      Pit *pit2;
      Bats *bats1;
      Bats *bats2;

      vector <vector<Room>> cave;

  public:

      Game();
      Game(int x, int y);
      Game(const Game &game2);
      ~Game();

      int get_cave_size();
      void set_cave_size(int x);
      void test_print_vector();

      void printBoard();
      void printBoard_normal();
      void printBoard_debug();

      void populate_board();
      void populate_gold();
      void populate_wumpus();
      void populate_bats();
      void populate_pits();

      string event_check(int &i, int &j);
      int check_game_state();

      void player_turn();
      void player_shoot();
      void player_move();

      void room_stuff();
      void bat_carry();
      void destroy_rooms();
      void find_perceptions();
      void arrow_shot(int x);
      void wumpus_move();
};

#endif
