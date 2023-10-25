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

Wumpus::Wumpus()
{
    //cout << " Wumpus constuewtrfsd" << endl;
    perception = "You smell a terrible stench.";
    encounter = "\n\n\n\n\n\nOH NO! You see a horrifying beast with its back turned away from you...\nSuddenly, it turns around to face you...\nJust before you can fully process its monstruous face. Before you can even feel the fear in your heart...\nIt opens its wide jaws and devours you...\n\n\n\n\n\n";
    event_ID = 2;
}


Wumpus::Wumpus(const Wumpus &wumpus2)
{
    perception = wumpus2.perception;
    encounter = wumpus2.encounter;
}

/*
Wumpus::~Wumpus()
{

}
*/

string Wumpus::get_perception()
{
    return perception;
}


string Wumpus::get_encounter()
{
    return encounter;
}


int Wumpus::get_eventID()
{
    return event_ID;
}
