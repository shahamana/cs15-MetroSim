/*
 * unit_tests.h
 * Aman Shah
 * February 9th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Use the unit_test framework to test the various objects of the sim, including
 * the Train, Passenger, and PassengerQueue.
 *
 * THE BELOW APPLIES TO TRAIN.H TESTS ONLY:
 *
 * Many of these tests were conducted on private functions that were 
 * temporarily made public for the purposes of this testing. Other tests used
 * these functions to prove that that specific feature is working correctly. 
 * ALL functions in Train.h should be made public for this testing.
 *
 */
#include "PassengerQueue.h"
#include "Passenger.h"
#include "Train.h"
#include <cassert>
#include <string>  
#include <iostream> 
#include <sstream> 

/************************** Test PassengerQueue Only **************************/

// Test that PassengerQueue initializes correctly.
void PassengerQueue_initialize() {
    PassengerQueue q;
}

// Test whether exception thrown when peeking at front of the queue.
void PassengerQueue_front_empty() {
    PassengerQueue q;

    // var to track whether runtime_error is thrown
    bool runtime_error_thrown = false;

    try {
        q.front();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
    }

    assert(runtime_error_thrown);
}

// Test whether correct passenger returned when peeking at front of queue.
void PassengerQueue_front_nonempty() {
    PassengerQueue q;
    Passenger p(1, 11, 12);
    q.enqueue(p);

    assert(q.front().id == 1);
    assert(q.front().from == 11);
    assert(q.front().to == 12);
}

// Test that adding to an empty PassengerQueue adds the correct Passenger.
void PassengerQueue_enqueue_one() {
    PassengerQueue q;
    Passenger p(1, 11, 12);

    q.enqueue(p);

    assert(q.size() == 1);
    assert(q.front().id == 1);
}

// Test whether appropriate exception thrown when removing from empty queue.
void PassengerQueue_dequeue_empty() {
    PassengerQueue q;

    // var to track whether runtime_error is thrown
    bool runtime_error_thrown = false;

    try {
        q.dequeue();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
    }

    assert(runtime_error_thrown);
}

// Test that removing from a 1-element PassengerQueue results in an empty queue.
void PassengerQueue_dequeue_one() {
    PassengerQueue q;
    Passenger p(1, 11, 12);

    q.enqueue(p);
    q.dequeue();

    assert(q.size() == 0);
}

// Test that adding and removing many Passengers from the queue works correctly.
void PassengerQueue_enqueue_dequeue_many() {
    PassengerQueue q;

    // Add 1000 passengers to the queue.
    for (int i = 0; i < 1000; i++) {
        Passenger p(i, i+5, i+18);
        q.enqueue(p);
    }

    assert(q.size() == 1000);

    // Remove passengers from the queue and make sure the passenger removed was
    // the passenger added at the same time.
    for (int i = 0; i < 1000; i++) {
        assert(q.front().id == i);
        q.dequeue();
    }

    assert(q.size() == 0);
}

// Test that an empty PassengerQueue reads as empty.
void PassengerQueue_size_empty() {
    PassengerQueue q;
    assert(q.size() == 0);
}

// Test that PassengerQueue prints with the correct syntax.
void PassengerQueue_print() {
    PassengerQueue q;
    Passenger p1(1, 11, 12);
    q.enqueue(p1);
    Passenger p2(2, 14, 16);
    q.enqueue(p2);

    std::stringstream buffer;
    q.print(buffer);

    assert(buffer.str() == "[1, 11->12][2, 14->16]");
}

/****************************** Test Train Only *******************************/

// Test if Train object initializes without errors.
void Train_initialize() {
    Train metro("reference.out");
}

// Test that routeSize returns 0 if there are no stations yet.
void Train_routeSize_empty() {
    Train metro("reference.out");
    assert(metro.routeSize() == 0);
}

// Test that routeSize returns the right number of stations on the route.
void Train_routeSize_many() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");

    assert(metro.routeSize() == 7);
}

// Test that the correct station name is returned if only one exists.
void Train_getStationName_single() {
    Train metro("reference.out");
    metro.addStation(0, "A");

    assert(metro.getStationName(0) == "A");
}

// Test that the correct station name is returned if multiple are on the route.
void Train_getStationName_multiple() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");

    assert(metro.getStationName(3) == "D");
    assert(metro.getStationName(5) == "F");
}

// Test that the correct queue is returned if only one station exists.
void Train_getStationWaiting_single() {
    Train metro("reference.out");
    metro.addStation(0, "A");

    assert(metro.getStationWaiting(0)->size() == 0);
}

// Test that the correct queue is returned if there are multiple stations on the
// route.
void Train_getStationWaiting_multiple() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");

    assert(metro.getStationWaiting(3)->size() == 0);
    assert(metro.getStationWaiting(5)->size() == 0);
}

// Tests that the correct number of passengers are returned if none are 
// currently on the train. 
void Train_numPassengers_empty() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");

    assert(metro.numPassengers() == 0);
}

// Tests that the correct number of stations were added to the route.
void Train_addStations() {
    Train metro("reference.out");

    metro.addStation(0, "A");
    assert(metro.routeSize() == 1);
    assert(metro.getStationName(0) == "A");

    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    assert(metro.routeSize() == 5);
    assert(metro.getStationName(3) == "D");
}

// Tests that a single passenger was added correctly to an empty station.
void Train_newPassenger_empty_stations() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");

    metro.newPassenger(1, 6);

    assert(metro.getStationWaiting(1)->size() == 1);
}

// Tests that passengers were added correctly to previously populated stations.
void Train_newPassenger_full_stations() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");

    metro.newPassenger(1, 6);
    metro.newPassenger(1, 10);
    metro.newPassenger(1, 1);

    assert(metro.getStationWaiting(1)->size() == 3);
}

// Tests that an empty train will move one station.
void Train_moveMetro_empty() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");

    metro.moveMetro();

    assert(metro.currentStation() == 1);
}

// Tests that an empty train will move to the end of the route and return to the
// beginning correctly. Also tests currentStation to ensure it returns the 
// correct value.
void Train_moveMetro_wrap_around() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");

    metro.moveMetro();
    metro.moveMetro();
    metro.moveMetro();
    metro.moveMetro();
    metro.moveMetro();
    metro.moveMetro();
    assert(metro.currentStation() == 6);

    metro.moveMetro();
    assert(metro.currentStation() == 0);
}

// Tests that train can move and pick up a single passenger. Tests that 
// numPassengers can identify when there is one passenger on the train.
void Train_pickUpPassengers_single() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");  

    metro.newPassenger(1, 6);
    metro.moveMetro();
    metro.moveMetro();

    assert(metro.numPassengers() == 1);
}

// Test that the train can move and pick up multiple passengers. Tests that 
// numPassengers can count how many passengers are on a populated train.
void Train_pickUpPassengers_multiple() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");  

    metro.newPassenger(1, 6);
    metro.newPassenger(1, 1);
    metro.newPassenger(2, 4);
    metro.moveMetro();
    metro.moveMetro();

    assert(metro.numPassengers() == 2);
}

// Tests that passengers can be picked up and dropped off correctly.
void Train_dropOffPassengers() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");  

    metro.newPassenger(1, 4);
    metro.newPassenger(1, 1);
    metro.newPassenger(2, 4);

    metro.moveMetro();
    metro.moveMetro();
    metro.moveMetro();

    assert(metro.numPassengers() == 3);

    metro.moveMetro();
    metro.moveMetro();

    assert(metro.numPassengers() == 1);
}

// Tests that passengers can be picked up and dropped off correctly, including
// if the arrival station is after the departure station on the route.
void Train_dropOffPassengers_wrap_around() {
    Train metro("reference.out");
    metro.addStation(0, "A");
    metro.addStation(1, "B");
    metro.addStation(2, "C");
    metro.addStation(3, "D");
    metro.addStation(4, "E");
    metro.addStation(5, "F");
    metro.addStation(6, "G");  

    metro.newPassenger(5, 2);

    for (int i = 0; i < 7; i++) {
        metro.moveMetro();
    }
    assert(metro.numPassengers() == 1);

    for (int i = 0; i < 5; i++) {
        metro.moveMetro();
    }
    assert(metro.numPassengers() == 0);
}