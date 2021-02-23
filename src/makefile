CC			:= g++
CCFLAGS		:= -std=c++17
LDFLAGS		:= -c -ggdb -g3
RLFLAGS 	:= -Os

BUILDDIR	:= ./src
TARGETPATH	:= ../bin
TARGETNAME	:= nweather

SRCDEPS		:= $(wildcard *.cpp)
OUTDEPS		:= $(patsubst %.cpp,%.o,$(wildcard *.cpp))


nweather: $(OUTDEPS)
	$(CC) $(CCFLAGS) $(OUTDEPS) -o $(TARGETNAME)

%.o: %.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm *.o

