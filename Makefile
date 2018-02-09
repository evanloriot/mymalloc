CC=gcc
CCFLAGS= -Wall -g
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET = memgrind 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^  

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
