#include <iostream>
#include "nevinAPI/nweatherAPI.h"
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "cxxopts/cxxopts.hpp"
#include <optional>
#include "networkClient.h"
#include "weather.h"

/*
 *	Hello random person debugging this program
 *	Please don't steal my api key, it is free to create a new one
 */

bool is_valid(std::string inputArgument)
{
	return inputArgument.find_first_not_of("0123456789-.") == std::string::npos;
}


int main(int argc, char *argv[]) {

	/*
	
	bool country = false, help = false, humidity = false, radius = false, latLong = false, countryDescription = false;
	std::string units = "metric";
	std::string countryInput;
	//std::string latInput;
	//std::string lonInput;
	//std::string radiusCount;
	unsigned int radiusCount;
	using json = nlohmann::json;

	float latInput = -31111111.0f;
	float lonInput = -31111111.0f;

	//latInput = argv[1];
	//lonInput = argv[2];
	*/
	
	cxxopts::Options options("nweather", "error: No country input");

	setenv("nweather_UNITS", "metric", 1);


	options.add_options()
		("i,imperial", "enable imperial units")
		("k,kelvin", "enable kelvin units")
		("h,humidity", "enable humidity setting")
		("c,coordinates", "allow coordinates to be used", cxxopts::value<std::vector<int>>()->default_value("65535,65535"))
		("r,radius", "get the radius around an area", cxxopts::value<std::vector<int>>()->default_value("65535,65535,65535"))
		("d,description", "get the description of the weather");

	auto result = options.parse(argc, argv);

	std::vector<int> coordinates = result["c"].as<std::vector<int>>();

	std::vector<int> radius = result["r"].as<std::vector<int>>();

	std::cout << coordinates[0] << coordinates[1] << std::endl;

	if (result["i"].as<bool>()) setenv("nweather_UNITS", "imperial", 1);

	if (result["k"].as<bool>()) setenv("nweather_UNITS", "kelvin", 1);

	Weather weather;

	if (result["h"].as<bool>()) {
		std::cout << weather.getLocalWeatherHumidity() << std::endl;
		return 0;
	}

	float ip = weather.getLocalWeather();

	std::cout << ip << "\n";

	return 0;

	/*

	for (int m = 1; m < argc; m++)
	{
		if (is_valid(argv[m]))
		{
			if (!latInput)
			{
				latInput = atof(argv[m]);
			}
			else
			{
				if (lonInput)
				{
					break;
				}
				lonInput = atof(argv[m]);
			}
		}
	}

	if (latInput && lonInput)
		latLong = true;

	nweatherAPI nWeatherAPI;

	//std::cout << latInput << " " << lonInput << "\n";

	//latLong = true;

	int m;
	while ((m = getopt(argc, argv, "1234567890ukirhcd.")) != -1) // country name, help (usage), kelvin, imperial, radius, humidity, coordinates
	{
		switch(m)
		{
			case 'u':
				help = true;
				//std::cout << "Usage: " << argv[0] << " -u (usage) -k (kelvin) -i (imperial) -r (radius) -h (humidity) -c (coordinates) 'Country name' Country" << "\n";
				std::cout << "  Usage" << std::endl
					<< "----------" << std::endl
					<< "-i (imperial) -k (kelvin) | Both of these are optional. Defaults to metric" << std::endl
					<< argv[0] << " lat lon Country 'Country Name'" << std::endl
					<< argv[0] << " -h lat lon Country 'County Name'" << std::endl
					<< argv[0] << " -c lat lon" << std::endl
					<< argv[0] << " -r lat lon count" << std::endl
					<< argv[0] << " -d lat lon Country 'Country Name'" << std::endl;
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
				if (argv[optind] == NULL || argv[optind + 1] == NULL || argv[optind + 2] == NULL)
				{
					std::cerr << "Usage: " << argv[0] << " -r lat lon count" << std::endl;
					exit(-1);
				}
				if (std::stoi(argv[optind + 2]) > 50)
				{
					std::cerr << "Error: Count must be less than 50" << std::endl;
				}
			//	latInput = argv[optind];
			//	lonInput = argv[optind + 1];
				radiusCount = std::stoi(argv[optind + 2]);
				break;
			case 'h':
				humidity = true;
				break;
			case 'c':
				if (argv[optind] == NULL || argv[optind + 1] == NULL)
				{
					std::cerr << "Error: Must have latitude and longitude when using -c flag" << "\n";
					exit(-1);
				}
				latLong = true;
			//	latInput = argv[optind];
			//	lonInput = argv[optind + 1];
				break;
			case 'd':
				if (argv[optind] == NULL)
				{
					std::cerr << "Error: Must input country for description" << "\n";
					exit(-1);
				}
				countryDescription = true;
				break;
				
		}
	}
	if (argv[optind] != NULL && argv[optind + 1] == NULL)
	{
		country == true;
	}
	if (latLong == false && radius == false)
	{
		if (argv[optind] == NULL && latLong == false)
		{
			if (latInput == -31111111.0f && lonInput == -31111111.0f)
			{
				std::cerr << "Error: No Country" << "\n";
				exit(-1);
	
			}
		}
		countryInput = argv[optind];
		//std::cout << countryInput << "\n";
	}
	
	if (latLong == false && radius == false && countryDescription == false && help == false)
	{
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

	//nweatherAPI nWeatherAPI;

	if (humidity == true && latLong == false)
	{
		std::cout << nWeatherAPI.getCountryHumidity(countryInput, units) << std::endl;
		exit(0);
	}

	if (humidity == true && latLong == true)
	{
		std::cout << nWeatherAPI.getCountryHumidityByCoords(latInput, lonInput, units) << "\n";
		exit(0);
	}

	if (latInput != -31111111 && lonInput != -31111111 && countryDescription == false && radius == false)
	{
		std::cout << nWeatherAPI.getCountryWeatherByCoords(latInput, lonInput, units) << std::endl;

		//std::cout << nWeatherAPI.getCountryWeatherByCoords(latInput, lonInput, units) << std::endl;
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

	if (countryDescription == true)
	{
		if (argv[optind + 1] == NULL)
		{
			countryInput = argv[optind];
			std::cout << nWeatherAPI.getCountryDescription(countryInput, units) << std::endl;
			exit(0);
		}
		else
		{
		//	latInput = argv[optind];
		//	lonInput = argv[optind + 1];
			std::cout << nWeatherAPI.getCountryDescriptionByCoords(latInput, lonInput, units) << std::endl;
			exit(0);
		}
	}

	if (radius == true)
	{
		std::map radiusTemperature = nWeatherAPI.getRadiusWeather(latInput, lonInput, radiusCount, units);
		for (auto city = radiusTemperature.begin(); city != radiusTemperature.end(); ++city)
		{
			std::cout << std::left << std::setw(50) << city->first << city->second << "\n";
		}
		exit(0);
	}


	else
	{
		std::cout << "whaaat" << "\n";
		exit(0);
	}
	return 0;
} */
}
