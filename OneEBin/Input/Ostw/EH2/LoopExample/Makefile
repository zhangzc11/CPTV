CC=gcc
CC+=-DDEBUG -g
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Looper.C TreeReader.C TreeReaderDict.C 
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=Looper

CFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDFLAGS += $(shell $(ROOTSYS)/bin/root-config --libs) 

CFLAGS += -I../

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o; rm $(EXECUTABLE)
