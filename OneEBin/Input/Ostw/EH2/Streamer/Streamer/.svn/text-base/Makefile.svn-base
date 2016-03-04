CC=gcc
CC+=-DDEBUG -g
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Main.C StreamTree.C Tree2Selector.C Tree2Selectordict.C
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=Streamer

CFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDFLAGS += $(shell $(ROOTSYS)/bin/root-config --libs) 

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o; rm $(EXECUTABLE)
