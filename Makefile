TARGET=fewo-blacklist
LIBS=
CC=g++
CFLAGS=-march=native -O2 -g -Wall

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

run:
	./$(TARGET)

reset:
	-echo   > daten.txt
	-echo 0 > counter.txt
