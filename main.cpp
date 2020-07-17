#include <iostream>
#include "nevinAPI/nweatherAPI.h"
#include <unistd.h>
#include <cstdlib>

/*
 *	Hello random person debugging this program
 *	Please don't steal my api key, it is free to create a new one
 */

int main(int argc, char *argv[]) {
	
	bool country = false, help = false, humidity = false, radius = false, latLong = false;
	std::string units = "metric";
	std::string latLongInput = "";
	std::string countryInput = "";
	using json = nlohmann::json;


	/*if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " 'COUNTRY NAME'" << std::endl;
		return 0;
	}
	if (argc > 2)
	{
		std::cerr << "Usage: " << argv[0] << " 'COUNTRY NAME'" << std::endl;
		return 0;
	}
	*/
	int m;
	while ((m = getopt(argc, argv, "c:ukirhp:")) != -1) // help, kelvin, imperial, humidity, radius around location, lat,long, 
	{
		switch(m)
		{
			case 'c':
				country = true;
				countryInput = optarg;
				break;
			case 'u':
				help = true;
				break;
			case 'k':
				units = "kelvin";
				break;
			case 'i':
				units = "imperial";
				break;
			case 'r':
				radius = true;
				break;
			case 'h':
				humidity = true;
				break;
			case 'p':
				latLong = true;
				latLongInput = optarg;
				break;
		}
	}

	if (radius == true && humidity == true)
	{
		std::cerr << "Error: Can't use himidity with radius weather" << "\n";
		exit(-1);
	}

	nweatherAPI nWeatherAPI;
	std::cout << nWeatherAPI.getCountryWeather(countryInput, units) << std::endl;
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

