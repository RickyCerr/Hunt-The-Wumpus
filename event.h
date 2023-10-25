#ifndef EVENT_H
#define EVENT_H

#include <ctime>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

#include "room.h"


using namespace std;

class Event{
  private:
  protected:
      string perception;
      string encounter;
      int event_ID;
  public:
      Event();
      Event(const Event &event2);
      virtual ~Event() = default;

      virtual string get_perception() = 0;
      virtual string get_encounter() = 0;
      virtual int get_eventID() = 0;

};

#endif
