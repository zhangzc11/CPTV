CC=gcc
CC+= -g
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= AccSub.C EventReader.C EventReaderDict.C AdMap.C ../../Common/OstwEff.C ../../Common/RunStat.C ../../Common/RunStatDict.C
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=AccSub

CFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDFLAGS += $(shell $(ROOTSYS)/bin/root-config --libs) 

CFLAGS += -I../../ -I$(CLHEP)/include/

all: $(SOURCES) $(EXECUTABLE)

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o; rm $(EXECUTABLE)
