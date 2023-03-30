/*
 * Passenger.cpp
 * Aman Shah
 * February 9th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Implements the print function for the Passenger struct. Able to output the
 * details of any passenger to the user's preferred output stream.
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name:      print
 * purpose:   output a string representation of a passenger
 * arguments: ostream object that represents the output method (cout, etc)
 * returns:   none
 * effects:   none
 */
void Passenger::print(std::ostream &output) {
        output << "[" << id << ", " << from << "->" << to << "]";
}
