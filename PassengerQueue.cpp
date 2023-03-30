/*
 * PassengerQueue.cpp
 * Aman Shah
 * February 9th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Implements a PassengerQueue which allows for addition and removal of 
 * Passengers under a FIFO framework.
 *
 */

#include <string>
#include <stdexcept>
#include "PassengerQueue.h"

using namespace std;

/*
 * name:      front
 * purpose:   peek at the first object in the queue
 * arguments: none
 * returns:   first Passenger object in the queue
 * effects:   throws exception is queue is empty
 */
Passenger PassengerQueue::front() {
    if (queue.empty()) {
        throw runtime_error("cannot access the first of an empty queue");
    }

    return queue.front();
}

/*
 * name:      dequeue 
 * purpose:   remove the first object in the queue
 * arguments: none
 * returns:   none
 * effects:   throws exception is queue is empty
 */
void PassengerQueue::dequeue() {
    if (queue.empty()) {
        throw runtime_error("cannot remove the first of an empty queue");
    }

    queue.pop_front();
}

/*
 * name:      enqueue
 * purpose:   add a Passenger to the back of the queue
 * arguments: constant Passenger object to add
 * returns:   none
 * effects:   adds one Passenger to the PassengerQueue
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    queue.push_back(passenger);
}

/*
 * name:      size
 * purpose:   get the current number of Passengers in this PassengerQueue
 * arguments: none
 * returns:   size of the PassengerQueue
 * effects:   none
 */
int PassengerQueue::size() {
    return queue.size();
}

/*
 * name:      print
 * purpose:   print the details of all Passengers in this PassengerQueueu
 * arguments: output stream to be printed to
 * returns:   none
 * effects:   prints all Passenger details to the given output stream
 */
void PassengerQueue::print(std::ostream &output) {
    // Use an iterator to iterate over the queue and print each Passenger
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        it->print(output);
    }
}

