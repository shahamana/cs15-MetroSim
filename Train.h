/*
 * Train.h
 * Aman Shah
 * February 13th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Defines an object that represents a train in the simulation, including all
 * passengers on the train and ways to change the state of the train in the sim.
 *
 */

#ifndef __TRAIN_H__
#define __TRAIN_H__

#include "Station.h"
#include "Passenger.h"
#include "PassengerQueue.h"
#include <list>
#include <vector>
#include <string>
#include <fstream>

class Train {
public:
    Train(std::string filename);
    ~Train();

    // Functions to change the station of the simulation
    void addStation(int num, std::string name);
    void newPassenger(int arrivalStation, int destStation);
    void moveMetro();
    void dropOffPassengers();
    void pickUpPassengers();

    void printState();

private:
    // List of stations on the route and list of passengers on the train
    vector<Station>         route;
    vector<PassengerQueue*> train_cars;

    int         curr_station;
    int         next_passenger_id;
    std::string outputFile;

    // Functions that return information about state of the simulation
    int            routeSize();
    std::string    getStationName(int number);
    PassengerQueue *getStationWaiting(int number);
    int            numPassengers();
    int            currentStation();
};

#endif