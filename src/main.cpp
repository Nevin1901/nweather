#include <iostream>
// #include "nevinAPI/nweatherAPI.h"
#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "cxxopts-2.2.1/include/cxxopts.hpp"
// #include <optional>
#include "./include/weather.h"
#ifdef _WIN32	    // irrelevant includes for now, these headers might be used if I want to switch the
	#include <io.h> // console mode in windows to print unicode charactesrs
	#include<fcntl.h>
#endif

/*
 *	Hello random person debugging this program
 *	Please don't steal my api key, it is free to create a new one
 */


int main(int argc, char *argv[]) {

    std::map<std::string, const char*> shortUnits = {{"metric", u8"\u00B0C"}, {"imperial", u8"\u00B0F"}, {"kelvin", u8"\u00B0K"}};

	cxxopts::Options options(argv[0]);

	std::vector<int> coordinates; 

	int radius = 1;

	options.add_options()
		("i,imperial", "enable imperial units")
		("k,kelvin", "enable kelvin units")
		("h,humidity", "enable humidity setting")
		("c,coordinates", "allow coordinates to be used", cxxopts::value(coordinates), "[x,y]")
		("r,radius", "get the radius around an area", cxxopts::value<int>(radius), "[0-50]")
		("d,description", "get the description of the weather")
		("u,usage", "usage information");

	std::string nweatherUnits = "metric";

	auto result = options.parse(argc, argv);

	if (result.count("i")) nweatherUnits = "imperial";

	if (result.count("k")) nweatherUnits = "kelvin";

	if (result.count("u")) {
		std::cout << options.help({""}) << std::endl;
		return 0;
	}

	Weather weather(nweatherUnits);

	if (result.count("c")) {
		if (coordinates.size() <= 1 || coordinates.size() > 2) {
			std::wcout << "Error: Invalid amount of coordinates" << std::endl;
			return 0;
		}

		if (result.count("h")) {
			std::map<std::string, int> weatherCoordinates = weather.getWeatherHumidityByCoordinates(coordinates[0], coordinates[1], radius);
			for (auto city = weatherCoordinates.begin(); city != weatherCoordinates.end(); ++city) {
				std::cout << std::left << std::setw(50) << city->first << city->second << std::endl;
			}
			return 0;
		}
		else {
			std::map<std::string, float> weatherCoordinates = weather.getWeatherByCoordinates(coordinates[0], coordinates[1], radius);
			for (auto city = weatherCoordinates.begin(); city != weatherCoordinates.end(); ++city) {
					std::cout << std::left << std::setw(50) << city->first << city->second << shortUnits[nweatherUnits] << std::endl;
			}
		}

		// TODO: Make a function which returns all of the data and is easily grepable
		return 0;
	}

	if (result.count("h")) {
		std::wcout << weather.getLocalWeatherHumidity() << std::endl;
		return 0;
	}

	if (result.count("d")) {
		std::cout << weather.getLocalWeatherDescription() << std::endl;
	}

	else {
		#ifdef _WIN32
			_setmode(_fileno(stdout), _O_U16TEXT); // while the console is set to the correct mode, the degrees
		#endif //									  still doesn't work

		std::cout << weather.getLocalWeather();

		std::cout << shortUnits[nweatherUnits] << std::endl;
		return 0;
	}

}
