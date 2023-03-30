/*
 * MetroSim.h
 * Aman Shah
 * February 13th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Defines a new instance of the simulation that changes the state of the metro
 * based on user commands.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Train.h"
#include <string>
#include <iostream>
#include <fstream>

class MetroSim {
public:
    MetroSim(int argc, char *argv[]);
    ~MetroSim();

    void readStations(string filename);
    void playSim();
    void promptAndExecute(istream &input);

private:
    // New instance of Train for a new sim.
    Train *metro;
    // Stores the name of the commands file if there is one.
    string commandsFile;
};

#endif
