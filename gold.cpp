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

Gold::Gold()
{
    //cout << " Gold constuewtrfsd" << endl;
    perception = "You see a glimmer nearby...";
    encounter = "\n\n\n\n\n\nYou have found the GOLD...You pick it up...\n\n\n\n\n\n";
    event_ID = 1;
}


Gold::Gold(const Gold &gold2)
{
    perception = gold2.perception;
    encounter = gold2.encounter;
}

/*
Gold::~Gold()
{

}
*/

string Gold::get_perception()
{
    return perception;
}


string Gold::get_encounter()
{
    return encounter;
}

int Gold::get_eventID()
{
    return event_ID;
}
