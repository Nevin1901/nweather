#include <iostream>
#include "URI.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Weather {
	public:
		float getLocalWeather();
		float getLocalWeatherHumidity();
		std::map<std::string, float> getWeatherByCoordinates(int lat, int lon, int radius);
		Weather(std::string units) {
			nweatherUnits = units;
		}
	private:
		json getLocalWeatherData();
		json getWeatherDataByCoordinates(int lat, int lon, int radius);
		std::string nweatherUnits;

};
