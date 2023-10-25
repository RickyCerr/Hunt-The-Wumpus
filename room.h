#ifndef ROOM_H
#define ROOM_H

#include <ctime>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

/*#include "event.h" */
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

using namespace std;

class Room
{
  private:
      int room_num;
      Event *event;

  public:
      Room();
      Room(const Room &room2);
      //~Room();

      int get_room_num();
      Event* get_room_event();
      void set_room_num(int x);
      void set_room_event(Event *event_ptr);
      void destroy_room_event();

};

#endif
