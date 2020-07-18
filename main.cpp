#include <iostream>
#include "nevinAPI/nweatherAPI.h"
#include <unistd.h>
#include <cstdlib>

/*
 *	Hello random person debugging this program
 *	Please don't steal my api key, it is free to create a new one
 */

int main(int argc, char *argv[]) {
	
	bool country = false, help = false, humidity = false, radius = false, latLong = false;
	std::string units = "metric";
	std::string latLongInput = "";
	std::string countryInput = "";
	using json = nlohmann::json;

	int m;
	while ((m = getopt(argc, argv, "ukirhp: ")) != -1) // country name, help (usage), kelvin, imperial, radius, humidity, coordinates
	{
		switch(m)
		{
			case 'u':
				help = true;
				break;
			case 'k':
				units = "kelvin";
				break;
			case 'i':
				units = "imperial";
				break;
			case 'r':
				radius = true;
				break;
			case 'h':
				humidity = true;
				break;
			case 'p':
				latLong = true;
				latLongInput = optarg;
				break;
		}
	}
	
	nweatherAPI nWeatherAPI;

	if (argv[optind] == NULL)
	{
		std::cerr << "Error: No Country" << "\n";
		exit(0);
	}
	countryInput = argv[optind];

	if (radius == true && humidity == true)
	{
		std::cerr << "Error: Can't use humidity with radius weather" << "\n";
		exit(-1);
	}

	else if (country == true && latLong == true)
	{
		std::cerr << "Error: Can't input country and have coordinates" << "\n";
		exit(-2);
	}

	if (humidity == true) std::cout << nWeatherAPI.getCountryHumidity(countryInput, units) << std::endl;

	else std::cout << nWeatherAPI.getCountryWeather(countryInput, units) << std::endl;

	return 0;
}

