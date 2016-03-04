CC=gcc
CC+=-O2
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=FastStreamer.C AdSimpleReader.C AdSimpleReader_Dict.C CalibReadoutHeaderReader.C CalibReadoutHeaderReader_Dict.C CalibStatsReader.C CalibStatsReader_Dict.C StreamTree.C
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=FastStreamer

CFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDFLAGS += $(shell $(ROOTSYS)/bin/root-config --libs) 
LDFLAGS += -lTreePlayer

CFLAGS += -I../../Common/

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o; rm $(EXECUTABLE)
