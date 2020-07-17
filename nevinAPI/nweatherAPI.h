#include <iostream>
#include "../nlohmann/json.hpp"

#ifndef nweatherAPI_H
#define nweatherAPI_H

class nweatherAPI {
	public:
		int getCountryWeather(std::string location, std::string units, bool humidity);
	private:
		std::string makeLocalWeatherAPICall(std::string location, std::string units);
		bool checkUnits(std::string unit);
};

#endif
