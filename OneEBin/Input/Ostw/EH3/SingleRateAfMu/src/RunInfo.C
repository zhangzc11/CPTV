#include "RunInfo.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int RunInfo::Dump()
{
  cout<<Run<<" "<<Site<<" "<<StartTime<<" "<<StopTime<<" "<<FullTime.GetSeconds()<<" "
      <<VetoTime[1].GetSeconds()<<" "<<VetoTime[2].GetSeconds()<<" "<<VetoTime[3].GetSeconds()<<" "<<VetoTime[4].GetSeconds()<<endl
      <<NMuon<<" "
      <<NPlMuon[1]<<" "<<NPlMuon[2]<<" "<<NPlMuon[3]<<" "<<NPlMuon[4]<<" "
      <<NAdMuon[1]<<" "<<NAdMuon[2]<<" "<<NAdMuon[3]<<" "<<NAdMuon[4]<<" "
      <<NShMuon[1]<<" "<<NShMuon[2]<<" "<<NShMuon[3]<<" "<<NShMuon[4]<<" "
      <<NNetMuon[1]<<" "<<NNetMuon[2]<<" "<<NNetMuon[3]<<" "<<NNetMuon[4]<<endl
      <<NShMuon[1]/FullTime.GetSeconds()<<" "<<NShMuon[2]/FullTime.GetSeconds()<<" "<<NShMuon[3]/FullTime.GetSeconds()<<" "<<NShMuon[4]/FullTime.GetSeconds();

  for( unsigned int cnt=0; cnt<Breaks.size(); cnt++ ) {
    cout<<" "<<Breaks[cnt].GetSec()<<" "<<Breaks[cnt].GetNanoSec();
  }
  cout<<endl;


  return 1;
}

int RunInfo::DumpToFile( string filename )
{
  FILE* m_outfile = fopen(filename.c_str(), "a");

  // Title
  /*
# [Run] [Site] [StartSec] [StartNano] [StopSec] [StopNano] [FullTime] [Veto1] [Veto2] [Veto3] [Veto4] [NMuon] [NPl1] [NPl2] [NPl3] [NPl4] [NAd1] [NAd2] [NAd3] [NAd4] [NSh1] [NSh2] [NSh3] [NSh4] [NNet1] [NNet2] [NNet3] [NNet4] [NSgUp1] [NSgLw1] [NSgUp2] [NSgLw2] [NSgUp3] [NSgLw3] [NSgUp4] [NSgLw4] [Scale1] [Scale2] [Scale3] [Scale4] [N8MeV1] [N8MeV2] [N8MeV3] [N8MeV4] [N22MeV1] [N22MeV2] [N22MeV3] [N22MeV4] [Bk1B] [Bk1E] [Bk2B] [Bk2E] [Bk3B] [Bk3E] [Bk4B] [Bk4E]
  */

  fprintf(m_outfile,
	  "%10d %10d %10d %10d %10d %10d %8.3f %8.3f %8.3f %8.3f %8.3f %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d",
	  Run, Site, 
	  int(StartTime.GetSec()), StartTime.GetNanoSec(), 
	  int(StopTime.GetSec()),  StopTime.GetNanoSec(), 
	  FullTime.GetSeconds(),
	  VetoTime[1].GetSeconds(), VetoTime[2].GetSeconds(), VetoTime[3].GetSeconds(), VetoTime[4].GetSeconds(),
	  NMuon,
	  NPlMuon[1], NPlMuon[2], NPlMuon[3], NPlMuon[4],
	  NAdMuon[1], NAdMuon[2], NAdMuon[3], NAdMuon[4],
	  NShMuon[1], NShMuon[2], NShMuon[3], NShMuon[4],
	  NNetMuon[1], NNetMuon[2], NNetMuon[3], NNetMuon[4],
	  NSingleUp[1], NSingleLow[1], NSingleUp[2], NSingleLow[2],
	  NSingleUp[3], NSingleLow[3], NSingleUp[4], NSingleLow[4]);
        

  if( Breaks.size()>8 ) {
    cout<<" The size of breaks is above 4, which is beyond the number of columns of txt output. "<<endl;
  }
  // Print the breaks out and enclose them with zeros.
  for( unsigned int cnt=0; cnt<8; cnt++ ) {
    if( cnt<Breaks.size() ) {
      fprintf(m_outfile," %10d %10d",
	      int(Breaks[cnt].GetSec()), Breaks[cnt].GetNanoSec());
    } else {
      fprintf(m_outfile," %10d %10d", 0, 0);
    }
  }

  fprintf(m_outfile,"\n");

  fclose(m_outfile);

  return 1;
}
