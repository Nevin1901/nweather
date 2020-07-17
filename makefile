all:
	g++ main.cpp HTTPRequest.hpp nlohmann/json.hpp nevinAPI/nweatherAPI.cpp nevinAPI/nweatherAPI.h -o nweather
	./nweather -c Amsterdam
