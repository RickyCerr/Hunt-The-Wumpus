#ifndef WUMPUS_H
#define WUMPUS_H

#include <ctime>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

#include "room.h"
#include "event.h"
#include "bats.h"
#include "gold.h"
#include "pit.h"

using namespace std;

class Wumpus : public Event
{
  private:

  public:
      Wumpus();
      Wumpus(const Wumpus &wumpus2);
      ~Wumpus(){};

      string get_perception();
      string get_encounter();
      int get_eventID();

};

#endif
