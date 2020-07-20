#include <iostream>
#include "nweatherAPI.h"
#include "../HTTPRequest.hpp"
#include "../nlohmann/json.hpp"
#include <stdlib.h>
#include <string>

using json = nlohmann::json; 
/*
std::string getCountryWeather(std::string location, std::string units);
std::string makeLocalWeatherAPICall(std::string location, std::string units);
int getCountryHumidity(std::string location, std::string units);
std::string makeLocalWeatherAPICallByCoords(std::string lat, std::string lon, std::string units);
*/
int nweatherAPI::getCountryWeather(std::string_view location, std::string_view units)
{
	if (checkUnits(units))
	{
		json result = json::parse(makeLocalWeatherAPICall(location, units));
		if (result["main"]["temp"] == nlohmann::detail::value_t::null)
		{
			std::cerr << "Failed to parse weather data" << "\n";
			exit(-1);
		}

		else
		{
			return static_cast<int>(result["main"]["temp"]);
		}
	}
	else
	{
		std::cout << "incorrect units" << std::endl;
		exit(-1);
	}
}

int nweatherAPI::getCountryHumidity(std::string_view location, std::string_view units)
{
	if (checkUnits(units))
	{
		json result = json::parse(makeLocalWeatherAPICall(location, units));
		if (result["main"]["humidity"] == nlohmann::detail::value_t::null)
		{
			std::cerr << "Failed to parse humidity data" << "\n";
			exit(-1);
		}
		else
		{
			return static_cast<int>(result["main"]["humidity"]);
		}
	}
	else
	{
		std::cout << "incorrect units" << std::endl;
		exit(-1);
	}
}

int nweatherAPI::getCountryWeatherByCoords(std::string_view lat, std::string_view lon, std::string_view units)
{
	if (checkUnits(units))
	{
		json result = json::parse(makeLocalWeatherAPICallByCoords(lat, lon, units));
		if (result["main"]["temp"] == nlohmann::detail::value_t::null)
		{
			std::cerr << "Failed to parse temperature data" << "\n";
			exit(-1);
		}
		else
		{
			return static_cast<int>(result["main"]["temp"]);
		}
	}
	else
	{
		std::cout << "incorrect units" << std::endl;
		exit(-1);
	}
}

std::string nweatherAPI::makeLocalWeatherAPICallByCoords(std::string_view apiLat, std::string_view apiLon, std::string_view units)
{
	try
	{
		http::Request request(static_cast<std::string>("http://api.openweathermap.org/data/2.5/weather?lat=") + static_cast<std::string>(apiLat) + static_cast<std::string>("&lon=") + static_cast<std::string>(apiLon) + static_cast<std::string>("&appid=745e71977952cc564f59aada718bb85c&units=") + static_cast<std::string>(units));
		const http::Response response = request.send("GET");
	 	std::string resData = std::string(response.body.begin(), response.body.end());
	 	return resData;
		return "hi";
	}
	catch (const std::exception& e)
	{
		std::cerr << "Api call request failed, error " << e.what() << "\n";
		exit(-1);
	}
}

std::string nweatherAPI::makeLocalWeatherAPICall(std::string_view location, std::string_view units) 
{
	try
	{
		http::Request request((std::string)"api.openweathermap.org/data/2.5/weather?q=" + (std::string)location + "&appid=745e71977952cc564f59aada718bb85c&units=" + (std::string)units);
		const http::Response response = request.send("GET");
		std::string resData = std::string(response.body.begin(), response.body.end());
		return resData;
		
	}
	catch (const std::exception& e)
	{
		std::cerr << "Api call request failed, error " << e.what() << "\n";
		exit(-1);
	}
}

bool nweatherAPI::checkUnits(std::string_view unit)
{
	if (unit == "metric" || unit == "imperial" || unit == "kelvin") return true;
	else return false;
}

