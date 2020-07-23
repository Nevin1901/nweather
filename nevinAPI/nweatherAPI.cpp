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

std::map<std::string, int> nweatherAPI::getRadiusWeather(std::string_view lat, std::string_view lon, std::string_view count, std::string_view units)
{
	if (checkUnits(units))
	{
		json result = json::parse(makeRadiusWeatherAPICall(lat, lon, count, units));
		if (result["cod"] == nlohmann::detail::value_t::null)
		{
			std::cerr << "Failed to parse temperature data" << "\n";
			exit(-1);
		}
		else
		{
			std::map<std::string, int> countries;
			for (auto& el : result["list"].items())
			{
				countries.insert({static_cast<std::string>(el.value()["name"]), static_cast<int>(el.value()["main"]["temp"])});
			//	std::cout << el.value()["name"] << " : " << el.value()["main"]["temp"] << std::endl;
			}
			return countries;
		}
	}
	else
	{
		std::cerr << "incorrect units" << std::endl;
		exit(-1);
	}
}

std::string nweatherAPI::getCountryDescription(std::string_view location, std::string_view units)
{
	if (checkUnits(units))
	{
		json result = json::parse(makeLocalWeatherAPICall(location, units));
		if (result["weather"][0]["description"] == nlohmann::detail::value_t::null)
		{
			std::cerr << "Failed to parse description data" << "\n";
			exit(-1);
		}
		else
		{
			return static_cast<std::string>(result["weather"][0]["description"]);
		}
	}
	else
	{
		std::cerr << "incorrect units" << std::endl;
		exit(-1);
	}
}

std::string nweatherAPI::getCountryDescriptionByCoords(std::string_view lat, std::string_view lon, std::string_view units)
{
	if (checkUnits(units))
	{
		json result = json::parse(makeLocalWeatherAPICallByCoords(lat, lon, units));
		if (result["weather"][0]["description"] == nlohmann::detail::value_t::null)
		{
			std::cerr << "Failed to parse description data" << "\n";
			exit(-1);
		}
		else
		{
			return static_cast<std::string>(result["weather"][0]["description"]);
		}
	}
	else
	{
		std::cerr << "incorrect units" << std::endl;
		exit(-1);
	}
}

std::string nweatherAPI::makeRadiusWeatherAPICall(std::string_view lat, std::string_view lon, std::string_view count, std::string_view units)
{
	try
	{
		http::Request request(static_cast<std::string>("http://api.openweathermap.org/data/2.5/find?lat=" + static_cast<std::string>(lat) + "&lon=" + static_cast<std::string>(lon) +"&cnt=" + static_cast<std::string>(count) + "&units=" + static_cast<std::string>(units) + "&appid=745e71977952cc564f59aada718bb85c"));
		const http::Response response = request.send("GET");
		std::string responseData = std::string(response.body.begin(), response.body.end());
		return responseData;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Api call request failed, error " << e.what() << "\n";
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

