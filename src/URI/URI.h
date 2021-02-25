
#ifndef URI_H
#define URI_H


#include <iostream>

class URI {
	public:
		URI(std::string _data, int _status) {
			data = _data;
			status = _status;
		}
		int status;
		std::string data;
};

#endif
