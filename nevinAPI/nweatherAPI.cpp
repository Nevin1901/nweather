#include <iostream>
#include "nweatherAPI.h"
#include "../HTTPRequest.hpp"
#include "../nlohmann/json.hpp"
#include <stdlib.h>

using json = nlohmann::json; 

std::string getCountryWeather(std::string location, std::string units, bool humidity);
std::string makeLocalWeatherAPICall(std::string location, std::string units);
bool checkUnits(std::string unit);

int nweatherAPI::getCountryWeather(std::string location, std::string units, bool humidity)
{
	if (checkUnits(units) == true)
	{
		json result = json::parse(makeLocalWeatherAPICall(location, units));
		if (result["main"]["temp"] == nlohmann::detail::value_t::null)
		{
			std::cerr << "Failed to parse weather data" << "\n";
			exit(-3000);
		}

		if (humidity == true)
		{
			return (int)result["main"]["humidity"];
		}

		else
		{
			return (int)result["main"]["temp"];
		}
	}
	else
	{
		std::cout << "incorrect units" << std::endl;
		exit(-7000);
	}
	return 0;
}

std::string nweatherAPI::makeLocalWeatherAPICall(std::string location, std::string units) 
{
	try
	{
		//std::string apiCallString = "api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=745e71977952cc564f59aada718bb85c&units=" + units;
		http::Request request((std::string)"api.openweathermap.org/data/2.5/weather?q=" + (std::string)location + "&appid=745e71977952cc564f59aada718bb85c&units=" + (std::string)units);
		const http::Response response = request.send("GET");
		std::string resData = std::string(response.body.begin(), response.body.end());
		return resData;
		
	}
	catch (const std::exception& e)
	{
		std::cerr << "Api call request failed, error" << "\n";
		exit(-500);
	}
	return "ERROR";
}

bool nweatherAPI::checkUnits(std::string unit)
{
	std::string metrics[3] = {"metric", "kelvin", "imperial"};
	int metricSize = *(&metrics + 1) - metrics;
	for (int i = 0; i < metricSize; i++)
	{
		if (metrics[i] == unit)
		{
			return true;
		}
	}
	return false;
}

