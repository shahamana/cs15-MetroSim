/*
 * main.cpp
 * Aman Shah
 * February 13th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Contains main function that checks for the correct command line arguments and
 * then runs the train simulation.
 *
 */

#include <string>

#include "MetroSim.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Ensure that correct number of arguments passed by user in command line.
    if (argc != 3 and argc != 4) {
        cerr << "Usage: ./MetroSim stationsFile outputFile ";
        cerr << "[commandsFile]" << endl;
        exit(EXIT_FAILURE);
    }

    // Create a new instance of the sim and play it.
    MetroSim newSim(argc, argv);
    newSim.playSim();
    return 0;
}
