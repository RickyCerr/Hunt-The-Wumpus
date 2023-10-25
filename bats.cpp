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

Bats::Bats()
{
    //cout << " Bats constuewtrfsd" << endl;
    perception = "You hear wings flapping.";
    encounter = "\n\n\n\n\n\nOH NO! You see hundreds of eyes on the ceiling...\nYou light your torch and realize that the eyes belong to serveral SUPER BATS...\nThey notice your precense and start flapping their weing violently around you...\nOne of them picks you up and begins flying through the cave...\nYou fight it off until it lets go of you...\nYou are now in a different room.\n\n\n\n\n\n";
    event_ID = 3;
}


Bats::Bats(const Bats &bats2)
{
    perception = bats2.perception;
    encounter = bats2.encounter;
}

/*
Bats::~Bats()
{

}
*/

string Bats::get_perception()
{
    return perception;
}


string Bats::get_encounter()
{
    return encounter;
}


int Bats::get_eventID()
{
    return event_ID;
}
