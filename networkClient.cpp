#include <iostream>
#include "networkClient.h"

namespace networkClient {

	std::string networkTools::getLocation() {
		return "Amsterdam";
	}

	networkClient::URI networkTools::makeHttpRequest(URI uri) {
		if (uri.statusCode < 200) {
			std::cout << "it's less than 200" << "\n";
		}
		return uri;
	}
}




