/*
 * Passenger.h
 * Aman Shah
 * February 9th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Defines a Passenger struct, which represents a passenger in the simulation
 * with arrival and destination stations.
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        void print(std::ostream &output);

};

#endif
