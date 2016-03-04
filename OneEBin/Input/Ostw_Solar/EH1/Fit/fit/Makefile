CC=gcc
CC+= -g
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Fit.C InverseBetaCS.C Measurement.C Truth.C Li9.C Tool.C TimeStamp.C Crosssection.C GetWeeklyFlux.C ProtonNumber.C Baseline.C DailyPlot.C AnalyzeData.C OstwEff.C SurvProb.C AdMap.C
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=Fit

CFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDFLAGS += $(shell $(ROOTSYS)/bin/root-config --libs) -lMinuit
LDFLAGS += -lTreePlayer

CFLAGS += -I../ -I/home/bes/wangzhe/CLHEP/include/

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o; rm $(EXECUTABLE)
