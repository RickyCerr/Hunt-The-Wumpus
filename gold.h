#ifndef GOLD_H
#define GOLD_H

#include <ctime>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"

using namespace std;

class Gold : public Event
{
  private:

  public:
      Gold();
      Gold(const Gold &gold2);
      ~Gold(){};

      string get_perception();
      string get_encounter();
      int get_eventID();

};

#endif
