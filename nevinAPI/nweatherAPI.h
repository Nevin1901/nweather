#include <iostream>
#include "../nlohmann/json.hpp"

#ifndef nweatherAPI_H
#define nweatherAPI_H

class nweatherAPI {
	public:
		int getCountryWeather(std::string location, std::string units);
		int getCountryHumidity(std::string location, std::string units);
		int getCountryWeatherByCoords(std::string lat, std::string lon, std::string units);
	private:
		std::string makeLocalWeatherAPICall(std::string location, std::string units);
		std::string makeLocalWeatherAPICallByCoords(std::string apiLat, std::string apiLon, std::string units);
		bool checkUnits(std::string unit);
};

#endif
