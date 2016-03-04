
#include "SubEvt.h"
#include <iostream>
#include "math.h"

using namespace std;

SubEvt::SubEvt()
{
  Run      = -1; 
  Site     = -1;
  Det      = -1; 

  TrigNum  = -1; 
  TrigType = -1; 
  TrigSec  = -1; 
  TrigNano = -1; 

  NPmt     = -1; 

  E        = -1; 
  X        = -1; 
  Y        = -1; 
  Z        = -1; 

  TRms     = -1; 
  Quadrant = -1; 
  QMax2Sum = -1; 
  MaxQ2Inch = -1;

  MuonStat[1] = MuonId::NonMuon;
  MuonStat[2] = MuonId::NonMuon;
  MuonStat[3] = MuonId::NonMuon;
  MuonStat[4] = MuonId::NonMuon;
}

SubEvt::~SubEvt()
{
  MuonStat.clear();
}

SubEvt::SubEvt( StreamReader* Reader )
{
  Run	   = Reader-> Run;	  
  Site	   = Reader-> Site;	  
  Det	   = Reader-> Det;	  
                           
  TrigNum  = Reader-> TrigNum; 
  TrigType = Reader-> TrigType;
  TrigSec  = Reader-> TrigSec; 
  TrigNano = Reader-> TrigNano;
                           
  NPmt	   = Reader-> NPmt;	  
                           
  E	   = Reader-> E;	  
  X	   = Reader-> X;	  
  Y	   = Reader-> Y;	  
  Z	   = Reader-> Z;	  
                           
  TRms	   = Reader-> TRms;	  
  Quadrant = Reader-> Quadrant;
  QMax2Sum = Reader-> QMax2Sum;
  MaxQ2Inch = Reader-> MaxQ2Inch;
  
  MuonStat[1] = MuonId::NonMuon;
  MuonStat[2] = MuonId::NonMuon;
  MuonStat[3] = MuonId::NonMuon;
  MuonStat[4] = MuonId::NonMuon;
}
 
int SubEvt::Dump()
{
  cout<<"Det: "<<Det
      <<"\tTrigNum: "<<TrigNum
      <<"\tE: "<<E<<"\tNPmt: "
      <<NPmt<<"\tEllipse: "<<sqrt( (Quadrant)*(Quadrant) + (QMax2Sum)/0.45*(QMax2Sum)/0.45 )<<" "
      <<MuonStat[1]<<MuonStat[2]<<MuonStat[3]<<MuonStat[4]
      <<endl;

  return 1;
}
