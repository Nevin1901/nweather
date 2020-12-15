#include <iostream>
#include <stdlib.h>
#include "networkClient.h"
#include "weather.h"
#include "URI.h"
#include "nlohmann/json.hpp"

networkClient::networkTools network;

using json = nlohmann::json;

float Weather::getLocalWeather() {
 	json localWeather = getLocalWeatherData();
	return localWeather["main"]["temp"];
}

float Weather::getLocalWeatherHumidity() {
	json localWeather = getLocalWeatherData();
	return localWeather["main"]["humidity"];
}

json Weather::getLocalWeatherData() {
	std::string location = network.getLocation();
	URI localWeatherData = network.makeHttpRequest("api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=745e71977952cc564f59aada718bb85c&units=" + getenv("nweather_UNITS"));
	if (localWeatherData.status == 200) {
		json localWeatherDataJson = json::parse(localWeatherData.data);
		return localWeatherDataJson;
	}
	else {
		std::cerr << "error: failed getting local weather. Status code " << localWeatherData.status << std::endl;
		exit(-1);
	}
}
