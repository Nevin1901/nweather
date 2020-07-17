

all: main.o HTTPRequest.o nlohmann/json.o nevinAPI/nweatherAPI.o
	g++ main.cpp HTTPRequest.hpp nlohmann/json.hpp nevinAPI/nweatherAPI.cpp nevinAPI/nweatherAPI.h -o nweather
	./nweather -c Amsterdam
