CXX = g++

CXXFLAGS = -o

PROGRAM_NAME = nweather

.DEFAULT_GOAL := main



.main:
	$(CXX) *.cpp $(CXXFLAGS) $(PROGRAM_NAME)

