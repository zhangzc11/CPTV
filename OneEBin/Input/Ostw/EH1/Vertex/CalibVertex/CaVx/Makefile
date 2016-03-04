CC=gcc
CC+= -O2
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= CaVx.C
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE= CaVx

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
