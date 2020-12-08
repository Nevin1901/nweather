CC			:= g++
CCFLAGS		:= -std=c++17
LDFLAGS		:= -c

TARGETPATH	:= ./bin
TARGETNAME	:= nweather

nweather: main.o nweatherAPI.o networkClient.o
	$(CC) $(CCFLAGS) main.o nweatherAPI.o networkClient.o -o $(TARGETNAME)

main.o: main.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) main.cpp

#HTTPRequest.o: HTTPRequest.hpp
#	g++ -c HTTPRequest.hpp

#nlohmann/json.o: nlohmann/json.hpp
#	g++ -c nlohmann/json.hpp

nweatherAPI.o: nevinAPI/nweatherAPI.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) nevinAPI/nweatherAPI.cpp

networkClient.o: networkClient.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) networkClient.cpp

#all: main.o HTTPRequest.o nlohmann/json.o nevinAPI/nweatherAPI.o
#	g++ main.cpp HTTPRequest.hpp nlohmann/json.hpp nevinAPI/nweatherAPI.cpp nevinAPI/nweatherAPI.h -o nweather
#	./nweather -c Amsterdam

clean:
	rm *.o
