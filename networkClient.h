namespace networkClient {
	class URI {
		public:
			URI(std::string _data, int _status) {
				data = _data;
				status = _status;
			}
			int status;
			std::string data;

		
	};
	class networkTools {
		public:
			std::string getLocation();
		private:
			networkClient::URI makeHttpRequest(std::string url);
	};
}

