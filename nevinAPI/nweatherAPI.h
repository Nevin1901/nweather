#include <iostream>
#include "../nlohmann/json.hpp"
#include <string>

#ifndef nweatherAPI_H
#define nweatherAPI_H

class nweatherAPI {
	public:
		int getCountryWeather(std::string_view location, std::string_view units);
		int getCountryHumidity(std::string_view location, std::string_view units);
		int getCountryWeatherByCoords(std::string_view lat, std::string_view lon, std::string_view units);
	private:
		std::string makeLocalWeatherAPICall(std::string_view location, std::string_view units);
		std::string makeLocalWeatherAPICallByCoords(std::string_view apiLat, std::string_view apiLon, std::string_view units);
		bool checkUnits(std::string_view unit);
};

#endif
