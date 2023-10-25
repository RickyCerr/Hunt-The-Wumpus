#include <ctime>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

#include "game.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

using namespace std;

Event::Event()
{
    perception = " ";
    encounter = " ";
    event_ID = 0;
    //cout << "\n\nEvent created \n\n" ;
}


Event::Event(const Event &event2)
{
    perception = event2.perception;
    encounter = event2.encounter;
    event_ID = event2.event_ID;
}

/*
Event::~Event()
{

}
*/
/*
string Event::get_perception()
{
    return perception;
}


string Event::get_encounter()
{
    return encounter;
}
*/
