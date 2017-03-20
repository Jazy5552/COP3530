#Assignment2 makefile
CC = g++
#	-g adds debugging information to executable
#	-Wall shows most warnings
CFLAGS = -g -Wall -std=c++11
TARGET = project1.out
SOURCES = $(wildcard *.cpp)
#Objects will just be all the sources files
OBJECTS = $(SOURCES:%.cpp=%.o)

default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

phony:
	echo $(SOURCES)

clean:
	$(RM) $(TARGET) *.o

