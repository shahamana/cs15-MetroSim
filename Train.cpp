/*
 * Train.cpp
 * Aman Shah
 * February 13th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Allows user to move the train, pick up and drop off passengers, and create 
 * new passengers for the simulation.
 *
 */

#include "Train.h"
#include <iostream>

using namespace std;

/*
 * name:      Train
 * purpose:   Initialize an instance of the Train for the sim.
 * arguments: Name of the output file for the sim.
 * returns:   None.
 * effects:   Creates a Train that starts at Station 0 with a speciifc output
 *            file.
 */
Train::Train(string filename) {
    curr_station = 0;
    next_passenger_id = 1;

    outputFile = filename;
    // Check that output file can open correctly and erase all pre-existing data
    // in the file.
    ofstream outstream;
    outstream.open(outputFile);
    if (not outstream.is_open()) {
        cerr << "Error: could not open file " << outputFile << endl;
        exit(EXIT_FAILURE);
    }
    outstream.close();
}

/*
 * name:      ~Train
 * purpose:   Destructor for the Train object to delete heap-allocated memory.
 * arguments: None.
 * returns:   None.
 * effects:   Called when Train goes out of scope and deletes all 
 *            heap-allocated memory used for this instance of the object.
 */
Train::~Train() {
    // Delete all train cars that were used
    for (int i = 0; i < train_cars.size(); i++) {
        delete train_cars.at(i);
    }   

    // Delete passengers left at the stations
    for (int i = 0; i < routeSize(); i++) {
        delete getStationWaiting(i);
    }
}

/*
 * name:      routeSize
 * purpose:   Finds the number of stations currently on the metro route.
 * arguments: None.
 * returns:   Int size of the route vector, which is the number of stations on
 *            the route.
 * effects:   N/A
 */
int Train::routeSize() {
    return route.size();
}

/*
 * name:      getStationName
 * purpose:   Finds the name of the station given the station number
 * arguments: Number of station that user needs information about
 * returns:   String name of the station given the number of the station
 * effects:   N/A
 */
string Train::getStationName(int number) {
    return route.at(number).name;
}

/*
 * name:      getStationWaiting
 * purpose:   Provides access to the queue of passengers waiting at a station
 * arguments: Number of station that user needs access to
 * returns:   Pointer to the PassengerQueue of passengers waiting at the station
 * effects:   Returns a pointer, not the actual object itself
 */
PassengerQueue *Train::getStationWaiting(int number) {
    return route.at(number).waiting;
}

/*
 * name:      numPassengers
 * purpose:   Find the total number of passengers currently on the train
 * arguments: None
 * returns:   Int total number of passengers currently traveling on the train
 * effects:   N/A
 */
int Train::numPassengers() {
    int total = 0;

    // Iterate over the list of all train cars and add the number of passengers
    // in each train car to the total.
    for (auto it = begin(train_cars); it != end(train_cars); ++it) {
        total = total + (*it)->size();
    }  
    return total;
}

/*
 * name:      currentStation
 * purpose:   Find the number of the station the train is currently at
 * arguments: None
 * returns:   Integer number of the station the train is currently at
 * effects:   N/A
 */
int Train::currentStation() {
    return curr_station;
}

/*
 * name:      addStation
 * purpose:   Add a new station to the route given name and number
 * arguments: Int number of new station and string name of new station
 * returns:   None
 * effects:   Adds a new station but also adds a new car to the train to store
 *            any new passengers that will depart the train at the new station.
 */
void Train::addStation(int num, string name) {
    // Add new station
    Station newStation(num, name);
    route.push_back(newStation);

    // Add new train car for the new departure station
    PassengerQueue *car = new PassengerQueue();
    train_cars.push_back(car);
}

/*
 * name:      newPassenger
 * purpose:   Create a new passenger and add them to the correct station to wait
              to board the metro.
 * arguments: Integer arrival and departure stations of the passenger.
 * returns:   None.
 * effects:   Increments a next ID variable to ensure that each new passenger
 *            gets a unique identification number.
 */
void Train::newPassenger(int arrivalStation, int departStation) {
    // Create a new passenger
    Passenger newPassenger(next_passenger_id, arrivalStation, departStation);

    // Get a pointer to the Queue of passengers waiting at the station and add
    // the newest passenger
    getStationWaiting(arrivalStation)->enqueue(newPassenger);

    next_passenger_id++;
}

/*
 * name:      moveMetro
 * purpose:   Move the train to the next station, picking up and dropping of 
 *            passengers as necessary.
 * arguments: None
 * returns:   None
 * effects:   Moves train to the beginning of the route if it is at the last 
 *            station on the route. Picks up passengers before leaving station
 *            and drops off passengers after arriving at the new station.
 */
void Train::moveMetro() {
    // Pick up passengers as train is leaving the station
    pickUpPassengers();

    // If train is at end of line, return to the start. Otherwise, move the
    // train one station.
    if (curr_station == routeSize() - 1) {
        curr_station = 0;
    }
    else {
        curr_station++;
    }

    // Drop off passengers at the new station after moving
    dropOffPassengers();
}

/*
 * name:      dropOffPassengers
 * purpose:   Drop off any passengers on the train who are supposed to depart
 *            at the current station.
 * arguments: None
 * returns:   None
 * effects:   Outputs to a file with information on each passenger that departs
 *            the train.
 */
void Train::dropOffPassengers() {
    // Get train car for departure station and name of station.
    PassengerQueue *car = train_cars.at(curr_station);
    string stationName = getStationName(curr_station);

    // Open output file and ensure that it is appending to the pre-existing
    // data in the file, not overwriting it.
    ofstream outstream;
    outstream.open(outputFile, fstream::app);
    if (not outstream.is_open()) {
        cerr << "Error: could not open file " << outputFile << endl;
        exit(EXIT_FAILURE);
    }
    
    // Until car is empty, record ID of passenger, output that they left the 
    // train, and remove passenger.
    while (car->size() > 0) {
        int id = car->front().id;
        car->dequeue();

        outstream << "Passenger " << id << " left train at station ";
        outstream << stationName << endl;
    }

    outstream.close();
}

/*
 * name:      pickUpPassengers
 * purpose:   Pick up passengers waiting at the station to board the train.
 * arguments: None
 * returns:   None
 * effects:   Adds passenger to the train based on which station they will be
 *            getting off the train at.
 */
void Train::pickUpPassengers() {
    // Get list of passengers waiting at the station.
    PassengerQueue *newPassengers = getStationWaiting(curr_station);
    
    // Add each waiting passenger to the correct train car.
    while (newPassengers->size() > 0) {
        // Get the next passenger waiting at the station.
        Passenger p = newPassengers->front();
        newPassengers->dequeue();

        // Get the train car for the destination of the passenger.
        PassengerQueue *car = train_cars.at(p.to);

        // Add passenger to the correct car.
        car->enqueue(p);
    }
}

/*
 * name:      printState
 * purpose:   Print the state of the simulation, including where passengers are
 *            and which station the train is at.
 * arguments: None
 * returns:   None
 * effects:   Prints state of simulation to the console, including
 *            information about the passengers on the train and waiting at 
 *            specific stations.
 */
void Train::printState() {
    // Loop through train cars and print all passengers on the train.
    cout << "Passengers on the train: {";
    for (auto it = begin(train_cars); it != end(train_cars); ++it) {
        (*it)->print(cout);
    }                                  
    cout << "}" << endl;

    // For each station, print name of station and all passengers waiting.
    for (int i = 0; i < routeSize(); i++) {
        // Mark the station the train is currently at.
        if (i == curr_station) {
            cout << "TRAIN: ";
        }
        else {
            cout << "       ";
        }

        // Print out station info and passengers currently waiting there.
        cout << "[" << i << "] " << getStationName(i) << " {";
        getStationWaiting(i)->print(cout);
        cout << "}" << endl;
    }
}