//
// This package reads the reactor flux data from offline DB.
// This package was reduced from GuoFu's update of InverBeta generator, and is only supposed to read reactor flux.
// Fengpeng An 2011.12.27
// 
// Adopted.
// Apr. 6 2012
// Zhe Wang
//
// Usage:
//    ReactorTable.exe ReactorTable.exe [StartUTC] [StopUTC]; TIME Format Example: 2009-04-24T00:00:00
//    The time is utc time, i.e. the time in the timestamp in each data.
//    Remember to set DBCONF to offline_db.
//    The so-called one day average in database is also utc one day.
//    
//    Output a txt table can be read by root tree ReadFile.
//
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <time.h>
#include "KRLReactorFlux.hh"

using namespace std;
void ProcessArgs(int argc, char** argv, int& StartUTC, int& StopUTC);
void Usage();

int main(int argc, char** argv) {

  int StartUTC, StopUTC; /// Sec since epoch
  ProcessArgs(argc, argv, StartUTC, StopUTC);

  gReactorFlux = new KRLReactorFlux(); 

  /// Root Header
  cout<<"StartUTC:StopUTC:Reactor:Total:E1500keV:E1750keV:E2000keV:E2250keV:E2500keV:E2750keV:E3000keV:E3250keV:E3500keV:E3750keV:E4000keV:E4250keV:E4500keV:E4750keV:E5000keV:E5250keV:E5500keV:E5750keV:E6000keV:E6250keV:E6500keV:E6750keV:E7000keV:E7250keV:E7500keV:E7750keV:E8000keV:E8250keV:E8500keV:E8750keV:E9000keV:E9250keV:E9500keV"<<endl;
  /// Table Header
  cout<<"# [StartUTC] [StopUTC] [Reactor] [Total] [E1500keV] [E1750keV] [E2000keV] [E2250keV] [E2500keV] [E2750keV] [E3000keV] [E3250keV] [E3500keV] [E3750keV] [E4000keV] [E4250keV] [E4500keV] [E4750keV] [E5000keV] [E5250keV] [E5500keV] [E5750keV] [E6000keV] [E6250keV] [E6500keV] [E6750keV] [E7000keV] [E7250keV] [E7500keV] [E7750keV] [E8000keV] [E8250keV] [E8500keV] [E8750keV] [E9000keV] [E9250keV] [E9500keV]"<<endl;

  const int dayInSec = 24*60*60;
  for( int query = StartUTC; query<StopUTC; query+=dayInSec )  {
    gReactorFlux->SetTime(query);
    gReactorFlux->SetContext();

    for( int rct=0; rct<6; rct++ )  {
      cout<<query<<"\t"<<query+dayInSec<<"\t"<<rct+1<<"\t"<<gReactorFlux->fTotalNumber[rct]<<"\t";
      for( int bin=0; bin<33; bin++ )  {
	cout<<gReactorFlux->fEPointsFlux[rct][bin]<<"\t";
      }
      cout<<endl;
    }
  }

  return 0;
}


void ProcessArgs(int argc, char** argv, int& StartUTC, int& StopUTC) 
{
  const char* DATETIME_FORMAT = "%Y-%m-%dT%H:%M:%S";
  struct tm stm;

  if (argc!=3){
    Usage();
    exit (0);
  } else {
    char* Start = new char[strlen(argv[1]) +1];
    char* Stop  = new char[strlen(argv[2]) +1];

    strcpy(Start, argv[1]);
    strcpy(Stop,  argv[2]);

    /// mktime will think the input parameter stm as local time, but in fact it is not.
    strptime(Start, DATETIME_FORMAT, &stm);
    StartUTC = int(mktime(&stm)-timezone);

    /// mktime will think the input parameter stm as local time, but in fact it is not.
    strptime(Stop, DATETIME_FORMAT, &stm);
    StopUTC = int(mktime(&stm)-timezone);
  }
}


void Usage() {
  printf("ReactorTable.exe [StartUTC] [StopUTC]; TIME Format Example: 2009-04-24T00:00:00\n");
}

