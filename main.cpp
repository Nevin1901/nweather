#include <iostream>
#include "HTTPRequest.hpp"
#include "nlohmann/json.hpp"
#include "nevinAPI/nweatherAPI.h"

/*
 *	Hello random person debugging this program
 *	Please don't steal my api key, it is free to create a new one
 */

using json = nlohmann::json;

int main(int argc, char *argv[]) {
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " 'COUNTRY NAME'" << std::endl;
		return 0;
	}
	if (argc > 2)
	{
		std::cerr << "Usage: " << argv[0] << " 'COUNTRY NAME'" << std::endl;
		return 0;
	}
	nweatherAPI nWeatherAPI;
	std::cout << nWeatherAPI.getCountryWeather("Amsterdam", "metric") << std::endl;
	/*
	try
	{
		std::string countryArguments = argv[1];
		std::string apiCallString = "api.openweathermap.org/data/2.5/weather?q=" + countryArguments + "&appid=745e71977952cc564f59aada718bb85c&units=metric";
		http::Request request(apiCallString);
		const http::Response response = request.send("GET");
		std::string resData = std::string(response.body.begin(), response.body.end());
		json result = json::parse(resData);
		if (result["main"]["temp"] == nlohmann::detail::value_t::null) {
			std::cout << "Unknown Location\n";
		}
		else {
			std::cout << result["main"]["temp"] << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Request failed, error: " << e.what() << "\n";
	}
	*/
	return 0;
}

