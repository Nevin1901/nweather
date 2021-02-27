#include <iostream>
#include "../URI/URI.h"

namespace networkClient {
	class networkTools {
		public:
			std::string getLocation();
			std::string getIP();
			URI makeHttpRequest(std::string url);
	};
}

