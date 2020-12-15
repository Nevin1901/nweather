#include <iostream>
#include "URI.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Weather {
	public:
		float getLocalWeather();
		float getLocalWeatherHumidity();
	private:
		json getLocalWeatherData();

};
