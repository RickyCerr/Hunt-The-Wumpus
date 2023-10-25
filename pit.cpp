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

Pit::Pit()
{
    //cout << " Wumpus constuewtrfsd" << endl;
    perception = "You feel a breeze..";
    encounter = "\n\n\n\n\n\nOH NO! You walk into a dark room...\nYou only complete three steps when your next foot never hits the floor and you fall down a pit to your death...\n\n\n\n\n\n";
    event_ID = 4;
}


Pit::Pit(const Pit &pit2)
{
    perception = pit2.perception;
    encounter = pit2.encounter;
}

/*
Pit::~Pit()
{

}
*/

string Pit::get_perception()
{
    return perception;
}


string Pit::get_encounter()
{
    return encounter;
}


int Pit::get_eventID()
{
    return event_ID;
}
