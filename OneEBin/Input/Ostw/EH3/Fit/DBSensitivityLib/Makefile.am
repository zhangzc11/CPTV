AUTOMAKE_OPTIONS = foreign

INCLUDES = -I/afs/rhic.bnl.gov/dayabay/software/releases/external/ROOT/5.22.00a/x86_64-slc5-gcc43-opt/root/include

lib_LTLIBRARIES = \
  libDBSensitivityLib.la 

noinst_HEADERS = \
  DBSensitivityLibLinkDef.h 

include_HEADERS = \
  ReactorCore.h \
  Detector.h \
  InverseBetaCS.h \
  MixingMatrix.h \
  Experiment.h

libDBSensitivityLib_la_SOURCES = \
  ReactorCore.C \
  Detector.C \
  InverseBetaCS.C \
  MixingMatrix.C \
  Experiment.C \
  DBSensitivityLib_Dict.C

#linking libraries
 libDBSensitivityLib_la_LIBADD = \
 -L/afs/rhic.bnl.gov/dayabay/software/releases/external/ROOT/5.22.00a/x86_64-slc5-gcc43-opt/root/lib -lCore -lCint -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lm -ldl -lMinuit


# Rule for generating CINT dictionaries from class headers. (root specific)
DBSensitivityLib_Dict.C: \
  ReactorCore.h \
  Detector.h \
  InverseBetaCS.h \
  MixingMatrix.h \
  Experiment.h \
  DBSensitivityLibLinkDef.h
	rootcint -f $@ -c $(DEFAULT_INCLUDES) $(INCLUDES) $^

clean-local:
	rm -f *Dict*
