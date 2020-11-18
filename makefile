
nweather: main.o nweatherAPI.o
	mkdir -p ./bin && g++ -std=c++17 main.o nweatherAPI.o -o ./bin/nweather && rm *.o

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

#HTTPRequest.o: HTTPRequest.hpp
#	g++ -c HTTPRequest.hpp

#nlohmann/json.o: nlohmann/json.hpp
#	g++ -c nlohmann/json.hpp

nweatherAPI.o: nevinAPI/nweatherAPI.cpp
	g++ -std=c++17 -c nevinAPI/nweatherAPI.cpp

#all: main.o HTTPRequest.o nlohmann/json.o nevinAPI/nweatherAPI.o
#	g++ main.cpp HTTPRequest.hpp nlohmann/json.hpp nevinAPI/nweatherAPI.cpp nevinAPI/nweatherAPI.h -o nweather
#	./nweather -c Amsterdam
