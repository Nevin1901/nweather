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
	std::string latInput;
	std::string lonInput;
	std::string countryInput = "";
	using json = nlohmann::json;

	int m;
	while ((m = getopt(argc, argv, "ukirhlo")) != -1) // country name, help (usage), kelvin, imperial, radius, humidity, coordinates
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
			case 'l':
				latInput = optarg;
				latLong = true;
				break;
			case 'o':
				lonInput = optarg;
				break;
		}
	}

	if (argv[optind] == NULL)
	{
		std::cerr << "Error: No Country" << "\n";
		exit(-1);
	}

	//else if (latInput == NULL || lonInput == NULL)
	//{
//		std::cerr << "Error: Must have lat and lon coords" << "\n";
//		exit(-1);
//	}

	
	else if (radius == true && humidity == true)
	{
		std::cerr << "Error: Can't use humidity with radius weather" << "\n";
		exit(-1);
	}

	else if (country == true && latLong == true)
	{
		std::cerr << "Error: Can't input country and have coordinates" << "\n";
		exit(-1);
	}

	else
	{
		country = true;
		countryInput = argv[optind];
	}
	
	nweatherAPI nWeatherAPI;

	if (humidity == true) std::cout << nWeatherAPI.getCountryHumidity(countryInput, units) << std::endl;

	else if (latLong == true) std::cout << nWeatherAPI.getCountryWeatherByCoords(countryInput, latInput, lonInput, units) << std::endl;

	else std::cout << nWeatherAPI.getCountryWeather(countryInput, units) << std::endl;

	return 0;
}

