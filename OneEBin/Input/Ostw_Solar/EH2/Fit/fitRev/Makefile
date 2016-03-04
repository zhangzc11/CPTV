CC=gcc
CC+= -g
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Fit.C Measurement.C Truth.C Background/Background.C Background/Li9.C Background/Acc.C Background/FastN.C Tool/Tool.C TimeStamp.C ProtonNumber.C Baseline.C DailyPlot.C AnalyzeData.C SurvProb.C AdMap.C RctXsecTheory/RctSpec.C RctXsecTheory/Crosssection.C RctXsecTheory/InverseBetaCS.C RctXsecTheory/RctXsec.C Flux/GetFluxXsec.C ../../Common/OstwEff.C
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=Fit

CFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDFLAGS += $(shell $(ROOTSYS)/bin/root-config --libs) -lMinuit
LDFLAGS += -lTreePlayer

CFLAGS += -I./ -I../../ -I$(CLHEP)/include/

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
	rm -f *.o; rm -f */*.o; rm $(EXECUTABLE)
