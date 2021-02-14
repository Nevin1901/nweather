#include <iostream>
#include "URI.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Weather {
	public:
		float getLocalWeather();
		float getLocalWeatherHumidity();
		Weather(std::string units) {
			nweatherUnits = units;
		}
	private:
		json getLocalWeatherData();
		std::string nweatherUnits;

};
