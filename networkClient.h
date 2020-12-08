namespace networkClient {
	class URI {
		public:
			URI(std::string _data, int _statusCode) {
				data = _data;
				statusCode = _statusCode;
			}
			int statusCode;
			std::string data;

		
	};
	class networkTools {
		public:
			std::string getLocation();
			networkClient::URI makeHttpRequest(networkClient::URI uri);
	};
}

