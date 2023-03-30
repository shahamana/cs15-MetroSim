#########################################################
#             PROJECT 1: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# MetroSim linking rule
MetroSim: main.o MetroSim.o PassengerQueue.o Passenger.o Train.o
	${CXX} ${LDFLAGS} -o MetroSim main.o MetroSim.o PassengerQueue.o \
	                     Passenger.o Train.o

# This rule builds PassengerQueue.o
PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h Passenger.cpp
	$(CXX) $(CXXFLAGS) -c PassengerQueue.cpp Passenger.cpp

# This rule builds Passenger.o
Passenger.o: Passenger.cpp Passenger.h
	$(CXX) $(CXXFLAGS) -c Passenger.cpp

# This rule builds Train.o
Train.o: PassengerQueue.cpp PassengerQueue.h Passenger.h Passenger.cpp \
         Station.h Train.cpp Train.h
	$(CXX) $(CXXFLAGS) -c Passenger.cpp PassengerQueue.cpp Train.cpp

# This rule builds MetroSim.o
MetroSim.o: Train.cpp Train.h MetroSim.cpp MetroSim.h
	$(CXX) $(CXXFLAGS) -c Train.cpp MetroSim.cpp

# This rule builds main.o
main.o: MetroSim.cpp MetroSim.h main.cpp
	$(CXX) $(CXXFLAGS) -c MetroSim.cpp main.cpp

# The below rule will be used by unit_test.
unit_test: unit_test_driver.o PassengerQueue.o Passenger.o Train.o MetroSim.o
	$(CXX) $(CXXFLAGS) $^

# This rule provides the final submission 
provide:
	provide comp15 proj1_MetroSim PassengerQueue.h \
				    PassengerQueue.cpp \
				    Passenger.h Passenger.cpp  \
					Train.h Station.h Train.cpp \
					MetroSim.cpp MetroSim.h \
					main.cpp commands1.txt \
				    unit_tests.h Makefile README

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out
