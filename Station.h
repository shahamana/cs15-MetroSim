/*
 * Station.h
 * Aman Shah
 * February 13th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Represents a station on the train line that has a number, name, and list of
 * passengers waiting at the station to board the train.
 *
 */

#ifndef __STATION_H__
#define __STATION_H__

#include "PassengerQueue.h"
#include <string>
#include <list>

using namespace std;

struct Station {
    int number;
    string name;
    // List of people waiting at station to board the train
    PassengerQueue *waiting;

    Station(int number, string name) {
        this->number = number;
        this->name = name;
        waiting = new PassengerQueue();
    } 
};

#endif
