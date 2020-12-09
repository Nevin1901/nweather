#include <iostream>
#include "networkClient.h"
#include "nlohmann/json.hpp"
#include "HTTPRequest.hpp"

namespace networkClient {

	using json = nlohmann::json;

	std::string networkTools::getIP() {
		URI uri = networkTools::makeHttpRequest("http://api.ipify.org");
		if (uri.status == 200) {
			return uri.data;
		}
		else {
			std::cerr << "Error: unable to make location api call request. Status code " << uri.status << "\n";
			exit(-1);
		}
	}

	URI networkTools::makeHttpRequest(std::string url) {
		try {
			http::Request request(url);
			const http::Response response = request.send("GET");
			std::string resData = std::string(response.body.begin(), response.body.end());
			URI uri(std::string(response.body.begin(), response.body.end()), response.status);
			return uri;
		} catch (const std::exception& e) {
			std::cerr << "Api call request failed, error " << e.what() << "\n";
			exit(-1);
		}
	}

	std::string networkTools::getLocation() {
		std::string ipAddr = networkTools::getIP();
		URI _locationData = networkTools::makeHttpRequest("http://ip-api.com/json/" + ipAddr);
		if (_locationData.status == 200) {
			json locationData = json::parse(_locationData.data);
			return locationData["city"];
		}
		else {
			std::cerr << "Error: Unable to get location. Status code " << _locationData.status << std::endl;
			exit(-1);
		}
	}
}




