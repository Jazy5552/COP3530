#Assignment makefile for single cpp/out compiling
CC = g++
#	-g adds debugging information to executable
#	-Wall shows most warnings
CFLAGS = -g -Wall
TARGET = assignment3a.out assignment3b.out assignment3c.out 
SOURCES = $(TARGET:%.out=%.cpp)
#Objects will just be all the sources files
OBJECTS = $(SOURCES:%.cpp=%.o)

default: $(TARGET)

%.out: %.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

phony:
	echo $(SOURCES)

clean:
	$(RM) $(TARGET) *.o

