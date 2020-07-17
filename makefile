
nweather: main.o nweatherAPI.o
	g++ main.o nweatherAPI.o -o nweather

main.o: main.cpp
	g++ -c main.cpp

#HTTPRequest.o: HTTPRequest.hpp
#	g++ -c HTTPRequest.hpp

#nlohmann/json.o: nlohmann/json.hpp
#	g++ -c nlohmann/json.hpp

nweatherAPI.o: nevinAPI/nweatherAPI.cpp
	g++ -c nevinAPI/nweatherAPI.cpp

#all: main.o HTTPRequest.o nlohmann/json.o nevinAPI/nweatherAPI.o
#	g++ main.cpp HTTPRequest.hpp nlohmann/json.hpp nevinAPI/nweatherAPI.cpp nevinAPI/nweatherAPI.h -o nweather
#	./nweather -c Amsterdam
