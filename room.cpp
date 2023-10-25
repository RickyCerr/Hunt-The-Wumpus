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

Room::Room()
{
    room_num = 1;
    event = nullptr;
    //cout << "\n\nRoom created \n\n" ;
}


Room::Room(const Room &room2)
{
    room_num = room2.room_num;
    event = nullptr;
}

/*
Room::~Room()
{
    if (this->event)
    {
        delete event;
    }
} */


int Room::get_room_num()
{
    return room_num;
}


Event* Room::get_room_event()
{
    return event;
}


void Room::set_room_num(int x)
{
    room_num = x;
}


void Room::set_room_event(Event *event_ptr)
{
        if (this->event)
        {
            delete event;
        }
        event = event_ptr;

}

void Room::destroy_room_event()
{
    if (this->event)
    {
        delete event;
    }
    event = nullptr;
}
