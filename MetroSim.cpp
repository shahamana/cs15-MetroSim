/*
 * MetroSim.cpp
 * Aman Shah
 * February 13th, 2023
 *
 * CS 15 Project 1 - MetroSim
 *
 * Reads in user commands and then directs the simulation to take appropriate
 * action, whether it's adding a new passenger, moving the train, or ending the
 * simulation.
 *
 */

#include "MetroSim.h"

using namespace std;

/*
 * name:      MetroSim
 * purpose:   Create a new instance of the MetroSim object, which will run the
 *            simulation based on user preferences.
 * arguments: Number of command line arguments and array of pointers to the 
 *            command line arguments.
 * returns:   None
 * effects:   Creates a new Train, adds stations to the sim, and checks if 
 *            there is a file of commands from the user.
 */
MetroSim::MetroSim(int argc, char *argv[]) {
    metro = new Train(argv[2]);
    readStations(argv[1]);

    if (argc == 4) {
        commandsFile = argv[3];
    }
    else {
        commandsFile = "none";
    }
}

/*
 * name:      ~MetroSim
 * purpose:   Destructor for an instance of MetroSim to delete all 
 *            heap-allocated memory used.
 * arguments: None
 * returns:   None
 * effects:   None
 */
MetroSim::~MetroSim() {
    delete metro;
}

/*
 * name:      readStations
 * purpose:   Add stations to the train route based on the given file
 * arguments: Name of the file that includes names of all stations
 * returns:   None
 * effects:   None
 */
void MetroSim::readStations(string filename) {
    // Open stations input file and check if opened correctly
    ifstream instream;
    instream.open(filename);

    if (not instream.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    // Initialize variables to store name and number of station
    int station_num = 0;
    string station_name;

    // Get name of station from file and add to the train route
    getline(instream, station_name);
    while(not instream.eof()) {
        metro->addStation(station_num, station_name);
        station_num++;
        getline(instream, station_name);
    }

    // Close the input file
    instream.close();
}

/*
 * name:      playSim
 * purpose:   Runs the sim using command line input or the given commands file.
 * arguments: None
 * returns:   Outputs a thank you message once sim is over.
 * effects:   None.
 */
void MetroSim::playSim() {
    if (commandsFile == "none") {
        promptAndExecute(cin);
    }
    else {
        ifstream instream;
        instream.open(commandsFile);

        if (not instream.is_open()) {
            cerr << "Error: could not open file " << commandsFile << endl;
            exit(EXIT_FAILURE);
        }

        promptAndExecute(instream);
        instream.close();
    }
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

/*
 * name:      promptAndExecute
 * purpose:   Runs the simulation, until user ends the game or input file no
 *            longer has commands.
 * arguments: istream object that represents the input method (cin, a file)
 * returns:   None
 * effects:   None
 */
void MetroSim::promptAndExecute(istream &input) {
    bool endGame = false;
    string command = "";

    while (not endGame) {
        // Print simulation state and ask for a command
        metro->printState();
        cout << "Command? ";
        input >> command;

        // Create a new passenger if the p command is used
        if (command == "p") {
            int arrivalStation, destStation;
            input >> arrivalStation >> destStation;
            metro->newPassenger(arrivalStation, destStation);
            continue;
        }

        // If not p, get the second section of the inputted command
        input >> command;

        // If the m m command, move the train, otherwise end the game.
        if (command == "m") {
            metro->moveMetro();
        }
        else {
            endGame = true;
        }
    }
}
