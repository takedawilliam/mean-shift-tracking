# Variables to control Makefile operation
CXX = g++
CXXFLAGS = -Wall -ggdb `pkg-config --cflags --libs opencv`

# Targets needed to bring the executable up to date
MeanShiftTracking: MeanShiftTracking.o MeanShift.o
	$(CXX) $(CXXFLAGS) -o MeanShiftTracking MeanShiftTracking.o MeanShift.o
MeanShiftTracking.o: MeanShiftTracking.cpp MeanShift.h
	$(CXX) $(CXXFLAGS) -c MeanShiftTracking.cpp
MeanShift.o: MeanShift.cpp MeanShift.h
	$(CXX) $(CXXFLAGS) -c MeanShift.cpp
clean:
	rm *.o
