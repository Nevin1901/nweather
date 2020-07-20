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
	std::string countryInput;
	std::string latInput;
	std::string lonInput;
	using json = nlohmann::json;

	int m;
	while ((m = getopt(argc, argv, "ukirhc")) != -1) // country name, help (usage), kelvin, imperial, radius, humidity, coordinates
	{
		switch(m)
		{
			case 'u':
				help = true;
				std::cout << "Usage: " << argv[0] << " -u (usage) -k (kelvin) -i (imperial) -r (radius) -h (humidity) -c (coordinates) 'Country name' Country" << "\n";
				exit(0);
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
			case 'c':
				if (argv[optind] == NULL || argv[optind] == NULL)
				{
					std::cerr << "Error: Must have latitude and longitude when using -c flag" << "\n";
					exit(-1);
				}
				latLong = true;
				latInput = argv[optind];
				lonInput = argv[optind + 1];
				break;
		}
	}

	if (latLong == false && radius == false)
	{
		if (argv[optind] == NULL && latLong == false)
		{
			std::cerr << "Error: No Country" << "\n";
			exit(-1000);
		}
		countryInput = argv[optind];
		country = true;
	}
	


	if (radius == true && humidity == true)
	{
		std::cerr << "Error: Can't use humidity with radius weather" << "\n";
		exit(-1);
	}

	if (country == true && latLong == true)
	{
		std::cerr << "Error: Can't input country and have coordinates" << "\n";
		exit(-1);
	}

	nweatherAPI nWeatherAPI;

	if (humidity == true)
	{
		std::cout << nWeatherAPI.getCountryHumidity(countryInput, units) << std::endl;
		exit(0);
	}

	if (latLong == true)
	{
		std::cout << nWeatherAPI.getCountryWeatherByCoords(latInput, lonInput, units) << std::endl;
		exit(0);
	}

	if (country == true)
	{
		std::cout << nWeatherAPI.getCountryWeather(countryInput, units) << std::endl;
		exit(0);
	}

	else
	{
		std::cout << "whaaat" << "\n";
		exit(0);
	}
	return 0;
}

