#include <iostream>
#include "networkClient.h"
#include "nlohmann/json.hpp"
#include "HTTPRequest.hpp"

namespace networkClient {

	using json = nlohmann::json;

	std::string networkTools::getLocation() {
		networkClient::URI uri = networkTools::makeHttpRequest("http://api.ipify.org");
		if (uri.status == 200) {
			return uri.data;
		}
		else {
			std::cerr << "Error: unable to make location api call request. Status code " << uri.status << "\n";
			exit(-1);
		}
	}

	networkClient::URI networkTools::makeHttpRequest(std::string url) {
		try {
			std::cout << url << std::endl;
			http::Request request(static_cast<std::string>(url));
			const http::Response response = request.send("GET");
			std::string resData = std::string(response.body.begin(), response.body.end());
			networkClient::URI uri(std::string(response.body.begin(), response.body.end()), response.status);
			return uri;
		} catch (const std::exception& e) {
			std::cerr << "Api call request failed, error " << e.what() << "\n";
			exit(-1);
		}
	}
}




