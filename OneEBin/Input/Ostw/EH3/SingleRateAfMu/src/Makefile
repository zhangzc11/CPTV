CC=gcc
CC+= -g
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Ostw.C StreamReader.C StreamReaderDict.C TimeStamp.C SubEvt.C CachedQueueInsert.C EventTree.C BuildEvent.C RunInfo.C
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=Ostw

CFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDFLAGS += $(shell $(ROOTSYS)/bin/root-config --libs) 
LDFLAGS += -lTreePlayer

CFLAGS += -I../../ -I$(CLHEP)/include/

all: $(SOURCES) $(EXECUTABLE)

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o; rm $(EXECUTABLE)
