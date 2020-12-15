#include <iostream>
#include "../nlohmann/json.hpp"
#include <string>

#ifndef nweatherAPI_H
#define nweatherAPI_H

class nweatherAPI {
	public:
		float getCountryWeather(std::string_view location, std::string_view units);
		int getCountryHumidity(std::string_view location, std::string_view units);
		int getCountryHumidityByCoords(float& lat, float& lon, std::string_view units); 	
		float getCountryWeatherByCoords(float& lat, float& lon, std::string_view units);
		std::map<std::string, float> getRadiusWeather(float& lat, float&, int count, std::string_view units);
		std::string getCountryDescription(std::string_view location, std::string_view units);
		std::string getCountryDescriptionByCoords(float lat, float lon, std::string_view units);
	private:
		std::string makeLocalWeatherAPICall(std::string_view location, std::string_view units);
		std::string makeLocalWeatherAPICallByCoords(float apiLat, float apiLon, std::string_view units);
		std::string makeRadiusWeatherAPICall(float& lat, float& lon, int count, std::string_view units);
		std::string makeLocalWeatherAPICallByCityId(int cityId, std::string_view units);
		bool checkUnits(std::string_view unit);
};

#endif
