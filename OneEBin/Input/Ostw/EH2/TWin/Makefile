CC=gcc
CC+=-DDEBUG -g
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Main.C EventTree.C SubEvtReader.C SubEvtReaderDict.C TimeStamp.C
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=TWin

CFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDFLAGS += $(shell $(ROOTSYS)/bin/root-config --libs) 

CFLAGS += -I../ -I/home/bes/wangzhe/CLHEP/include/

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o; rm $(EXECUTABLE)
