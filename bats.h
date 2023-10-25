#ifndef BATS_H
#define BATS_H

#include <ctime>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "gold.h"
#include "pit.h"

using namespace std;

class Bats : public Event
{
  private:

  public:
      Bats();
      Bats(const Bats &bats2);
      ~Bats(){};

      string get_perception();
      string get_encounter();
      int get_eventID();

};

#endif
