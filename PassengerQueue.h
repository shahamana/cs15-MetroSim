/*
 * PassengerQueue.h
 * Aman Shah
 * February 9th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Defines a PassengerQueue object, each of which represents a car of the Train,
 * organized by destination station of all Passengers in the Queue.
 *
 */

#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__

#include "Passenger.h"
#include <list>

class PassengerQueue {
public:
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);

private:
    std::list<Passenger> queue;
};

#endif