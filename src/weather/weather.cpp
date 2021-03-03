#include <iostream>
#include <stdlib.h>
#include "../include/networkClient.h"
#include "../include/weather.h"
#include "../URI/URI.h"
#include "../json/single_include/nlohmann/json.hpp"

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

std::map<std::string, int> Weather::getWeatherHumidityByCoordinates(int lat, int lon, int radius) {
	json localWeather = getWeatherDataByCoordinates(lat, lon, radius);
	if (localWeather["cod"] == nlohmann::detail::value_t::null) {
		std::cerr << "Error: Failed to parse temperature data" << std::endl;
		exit(-1);
	} else {
		std::map<std::string, int> weatherData;
		for (auto& el : localWeather["list"].items()) {
			weatherData.insert({static_cast<std::string>(el.value()["name"]), static_cast<int>(el.value()["main"]["humidity"])});
		}
		return weatherData;
	}
}

std::map<std::string, float> Weather::getWeatherByCoordinates(int lat, int lon, int radius) {
	json localWeather = getWeatherDataByCoordinates(lat, lon, radius);
	if (localWeather["cod"] == nlohmann::detail::value_t::null) {
		std::cerr << "Error: Failed to parse temperature data" << std::endl;
		exit(-1);
	}
	else {
		std::map<std::string, float> weatherData;
		for (auto& el : localWeather["list"].items()) {
			weatherData.insert({static_cast<std::string>(el.value()["name"]), static_cast<float>(el.value()["main"]["temp"])});
		}
		return weatherData;
	}
}

json Weather::getLocalWeatherData() {
	std::string location = network.getLocation();
	URI localWeatherData = network.makeHttpRequest("api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=745e71977952cc564f59aada718bb85c&units=" + nweatherUnits);
	if (localWeatherData.status == 200) {
		json localWeatherDataJson = json::parse(localWeatherData.data);
		return localWeatherDataJson;
	}
	else {
		std::cerr << "error: failed getting local weather. Status code " << localWeatherData.status << std::endl;
		exit(-1);
	}
}

json Weather::getWeatherDataByCoordinates(int lat, int lon, int radius) {
	URI localWeatherData = network.makeHttpRequest("api.openweathermap.org/data/2.5/find?lat=" + std::to_string(lat) + "&lon=" + std::to_string(lon) + "&cnt=" + std::to_string(radius) + "&appid=745e71977952cc564f59aada718bb85c&units=" + nweatherUnits);
	if (localWeatherData.status == 200) {
		json localWeatherDataJson = json::parse(localWeatherData.data);
		return localWeatherDataJson;
	}
	else {
		std::cerr << "error: failed getting local weather by coordinates. Status code " << localWeatherData.status << std::endl;
		exit(-1);
	}
}

