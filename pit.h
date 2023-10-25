#ifndef PIT_H
#define PIT_H

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
#include "wumpus.h"

using namespace std;

class Pit : public Event
{
  private:

  public:
      Pit();
      Pit(const Pit &pit2);
      ~Pit(){};

      string get_perception();
      string get_encounter();
      int get_eventID();

};

#endif
