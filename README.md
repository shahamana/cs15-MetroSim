**Project 1: Metro Simulator**

Program Purpose:
---------------
Creates a simulation of a metro line with stations and passengers that board 
and depart the single train running on the line based on user commands.

Compile/Run:
-----------
    Compile using: make MetroSim
    Run using:     ./MetroSim stationsFile outputFile [commandsFile]

Instructions:
------------
Use stations.txt as the stationsFile to simulate the Boston Green Line
Add passengers to the simulation with the command: p [boardingStation] [departingStation]
Move the metro to the next station:                m m
End the simulation:                                m f

Acknowledgements: 
----------------
TA's were super helpful with this project! And the design checkoff was super
helpful in making my code more useful.

Used this answer on Stack Overflow:
www.stackoverflow.com/questions/23615975/how-to-append-file-in-c-using-fstream
It gave me the code necessary to append to a file I was writing to instead of
overwriting it.

Also used the C++ official documentation for std::list and std::vector to 
understand how to use both data structures.

Files: 
-----
main.cpp:
     Check that user provided the correct number of files and then run the 
     simulation.

MetroSim.cpp:
     Implementation of MetroSim class. Main functionality of the simulation, so
     it can take in user input to move the train, take in and remove passengers
     as the correct stations are reached.

MetroSim.h:
     Defines the MetroSim class which runs the simulation based on user input
     that it reads.

stations.txt:
     An example file containing a list of stations.

test_commands.txt:
     Sample list of commands that to test the simulation.

commands1.txt
     Another sample list of commands to test the simulation

the_metroSim:
     Reference implementation for students to see how the simulation should
     function.

Passenger.h:
     Defines the attributes of a Passenger, including their arrival and 
     destination.

Passenger.cpp:
     Implements a function that can print the details of any Passenger to a
     given output.

PassengerQueue.h:
     Defines a queue of Passengers that can be added to or removed from in a
     FIFO format.

PassengerQueue.cpp:
     Implements a queue of Passengers, allowing for printing of the Passengers
     in the queue.

Train.h:
     Interface for the Train class, which represents the train that runs up and
     down the metro line. Stores the passengers currently on the route and on
     the train itself.

Train.cpp:
     Implementation of the Train class, which includes functionality to create
     new stations, board passengers, record departing passengers, and more.

Station.h:
     Defines a Station struct, which represents a Station on the metro route as
     well as all passengers waiting to board the train at that station.

unit_test.h:
     Includes various unit tests that are used to test specific features and
     functions of the various classes and structs in this program.

Makefile:
     File used to build the program executable as well as to use unit testing.

README:
    This file, providing an overview of the program and any pertinent info.


Data Structures:
---------------
Passenger is a struct with primitive type variables. PassengerQueue is a class
and each instance of PassengerQueue contains a queue (C++ list) of Passengers
as well. Each Queue allows for removal from the front of the list using an 
O(1) operation, and same with adding to the back of the list. The disadvantage
with using a Queue instead of an ArrayList is that it is a high-complexity
task to access elements in the middle, but it is unnecessary to do so for this
sim.

Station is a struct with primitive type variables as well as a pointer to a
PassengerQueue. As such, each Station is an object that has a pointer to a
queue of Passengers waiting at the station. This allows the user to access
a Station and remove all Passengers waiting at the station (basically removing
them from the queue) in order without having to do an extra search through the
list for the first Passenger that reached the station.

Train is a class that represents the train running on the metro line in the sim.
It has a vector of Stations that are in order to represent the route the train
will take. The use of a vector, also known as an ArrayList allows for O(1) 
access to any station on the route to add new passengers as they are created.
It also has a vector of pointers to PassengerQueues, each of which
represent one car in the train that has Passengers all going to the same 
destination. This allows O(1) operations to access the Queue that corresponds
to a specific destination station. 


Testing:
-------
Conducted thorough unit testing of PassengerQueue to ensure that both the 
Passenger struct and PassengerQueue class were working as intended. Made sure
that appropriate exceptions were thrown, that Passengers could be created as
intended, and that adding and removing from a PassengerQueue also worked as
intended.

Conducted thorough unit testing of Train to ensure that the Station struct and
Train class were working as intended. Ensured that train could move, interact
with passengers appropriately, and add stations correctly. One bug I found 
here is that I did not actually create PassengerQueues, I only defined
PassengerQueue variables. As such, since the unit testing was showing that the
Passengers were not being added, I realized I had to rewrite the vector in Train
as a vector of PassengerQueue pointers and rewrite each Station as having a
pointer to a PassengerQueue, not a queue itself.

Conducted diff testing against the given reference executable to check that the
output after passengers were dropped off was accurate. Did this with two 
different set of user commands: test_commands.txt and commands1.txt
One bug I found through this was the fact that I had the passenger pick-up
occur AFTER the train moved to the next station, when in fact it had to 
happen BEFORE the train moved. Only through differences in the order of 
passengers in the output files was I able to figure out what the issue was.

Conducted diff testing for the standard console output against the given
reference for test_commands.txt and did the same for standard error output. The
diff testing for standard console output ensured that stations could be read 
accurately from the file, that the sim worked with command line input OR a 
file, and that the flow of the game in terms of inputting commands and the 
state of the sim changing was correct.

For MetroSim specifically, I also used inline cout statements to test the code.
I checked if the correct station name was being read in readStations and if
the correct command was being read in promptAndExecute to ensure that my file
I/O code was correct. 

Lastly, I used valgrind when running the entire program using both command
files to ensure that memory was being recycled properly.


Hours Spent:
-----------
    Roughly 21 hours spent total.
