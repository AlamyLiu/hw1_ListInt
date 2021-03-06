
CC = g++
CFLAGS = -I. -std=c++11 -D_DEBUG -ggdb
LIBS =
TARGET = infinitearithmetic

HEADERS = DList.hpp ArgumentManager.h DebugW.hpp formula.hpp
SOURCES = DList.cpp infinitearithmetic.cpp DebugW.cpp

OBJS = $(patsubst %.cpp, %.o, $(SOURCES))


.PHONY: default all clean

default: $(TARGET)
all: default

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(OBJS)
	-rm -f $(TARGET)

