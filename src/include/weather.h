#include <iostream>
#include "../URI/URI.h"
#include "../json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class Weather {
	public:
		float getLocalWeather();
		float getLocalWeatherHumidity();
		std::map<std::string, float> getWeatherByCoordinates(int lat, int lon, int radius);
		std::map<std::string, int> getWeatherHumidityByCoordinates(int lat, int lon, int radius);
		Weather(std::string units) {
			nweatherUnits = units;
		}
	private:
		json getLocalWeatherData();
		json getWeatherDataByCoordinates(int lat, int lon, int radius);
		std::string nweatherUnits;

};
