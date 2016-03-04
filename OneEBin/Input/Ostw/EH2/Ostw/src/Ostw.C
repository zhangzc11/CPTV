//
//   Every readout -> Good SubEvt -> Event
//
//   Zhe Wang, Jan. 27, 2012
//
#include "Globals.h"
#include <stdio.h>

TChain*  StreamChain;
StreamReader* Reader;
Cuts*         AllCut;
string   RunInfoOutput;

/* The core of the first loop of the code */
SubEvtQueue CachedQueue;

/* Delay the output of each SubEvt. They are cached in CachedQueue. */
/* Through caching, there is a chance to test the SubEvts in the queue and build up association. */
SubEvtQueue CachedQueueInsert( TimeStamp time, SubEvt* pSubEvt );

/* Muon information */
TimeStamp LastMuonT;
map<int /* AD No. */, TimeStamp /* last pool muon time */  > LastPoolMuonT;
map<int /* AD No. */, TimeStamp /* last AD muon time */    > LastAdMuonT;
map<int /* AD No. */, TimeStamp /* last shower muon time */> LastShowerMuonT;
map<int /* AD No. */, TimeStamp /* last net muon time */   > LastNetMuonT;

map<int /* AD No. */, TimeStamp /* veto all SubEvt till */>  MuonVetoTime;

/* The core of the second loop of the code */
map<int /* AD No. */, RunStatus::RunStatus_t /* Running Status */> RunStatusDict;
map<int /* AD No. */, Event /* Event under construction */       > EventDict;

map<int /* AD No. */, TimeStamp /* time of last subevt */ > LastSubEvtT;

int BuildEvent( SubEvt* pSubEvt );

/* Output TWin tree */
EventTree*    aEventTree;

int Usage()
{
  cout<<"Usage:"<<endl;
  cout<<"    Ostw InputFile.root(.list) OutputFile.TWin.root RunInfo.txt Gd|H"<<endl;
  cout<<endl;
  exit(1);
}

int BeginJob( int argc, char** argv );
int EndJob();

RunInfo CurrRun;
int BeginRun(StreamReader* Reader);
int EndRun(StreamReader* Reader);


///////////////////added by zzc on 2014/05/31////////////////////////////////////////////////////////////////
Double_t Z_WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
Double_t Z_StartTime = 1324678393.80705;
Double_t Z_EndTime = 1385769600.00000;
Int_t    Z_NumOfBin = (Z_EndTime - Z_StartTime)/Z_WidthOfBin;// = 17016.04  -->  17016
Int_t    Z_Site ;
Int_t    Z_Bin;
Double_t Z_FullTime_t=0;
Double_t Z_SkipTime_t=0;

Double_t Z_VT1_t=0;
Double_t Z_VT2_t=0;
Double_t Z_VT3_t=0;
Double_t Z_VT4_t=0;

Int_t Z_SgUp1_t=0;
Int_t Z_SgUp2_t=0;
Int_t Z_SgUp3_t=0;
Int_t Z_SgUp4_t=0;

Int_t Z_SgLow1_t=0;
Int_t Z_SgLow2_t=0;
Int_t Z_SgLow3_t=0;
Int_t Z_SgLow4_t=0;

Int_t Z_NetMuon1_t=0;
Int_t Z_NetMuon2_t=0;
Int_t Z_NetMuon3_t=0;
Int_t Z_NetMuon4_t=0;

Int_t Z_AdMuon_t[4]={0,0,0,0};
Int_t Z_HMuonL5_t[4]={0,0,0,0};
Int_t Z_HMuonG5_t[4]={0,0,0,0};
Int_t Z_HMuonG10_t[4]={0,0,0,0};
Int_t Z_HMuonG15_t[4]={0,0,0,0};

Double_t Z_VT1[3][17016];//={0};
Double_t Z_VT2[3][17016];//={0};
Double_t Z_VT3[3][17016];//={0};
Double_t Z_VT4[3][17016];//={0};
Int_t Z_SgUp1[3][17016];//={0};
Int_t Z_SgUp2[3][17016];//={0};
Int_t Z_SgUp3[3][17016];//={0};
Int_t Z_SgUp4[3][17016];//={0};
Int_t Z_SgLow1[3][17016];//={0};
Int_t Z_SgLow2[3][17016];//={0};
Int_t Z_SgLow3[3][17016];//={0};
Int_t Z_SgLow4[3][17016];//={0};
Int_t Z_NetMuon1[3][17016];//={0};
Int_t Z_NetMuon2[3][17016];//={0};
Int_t Z_NetMuon3[3][17016];//={0};
Int_t Z_NetMuon4[3][17016];//={0};

Int_t Z_AdMuon[4][3][17016];
Int_t Z_HMuonL5[4][3][17016];
Int_t Z_HMuonG5[4][3][17016];
Int_t Z_HMuonG10[4][3][17016];
Int_t Z_HMuonG15[4][3][17016];

Double_t Z_SkipTime[3][17016];//={0};
Double_t Z_LiveTime[3][17016];//={0};
Double_t Z_FullTime[3][17016];//={0};
Int_t    Z_Run[3][17016];//={0};
Int_t	 Z_BeginBin;
Int_t    Z_EndBin;
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Main function */
int main(int argc, char** argv)
{

  if( BeginJob( argc, argv ) == 0 ) {
    cout<<"BeginJob failed"<<endl;
    return 0;
  }

  /* Layer 1. The main loop over every stream entries */
  /* ------------------------------------------------ */
  CurrRun.Run = -1;
  cout<<"StreamChain add "<<StreamChain<<endl;
  unsigned int entries = StreamChain->GetEntries();
  for( unsigned int entry=0; entry<entries; entry++ )  {
    unsigned int localentry = StreamChain->LoadTree(entry);
    int ret = Reader->GetEntry( localentry );
    if( ret==0 ) { 
      cout<<"Error: Read error"<<endl;
      return 1;
    }
    
    /* Process run information and possible long time jump */
    if( Reader->Run != CurrRun.Run )  {
      if( CurrRun.Run != -1 )  {
	/* End Run */
	if( EndRun( Reader ) == 0 ) {
	  cout<<"EndRun failed"<<endl;
	  return 0;
	}
      }
      /* Begin Run */
      if( BeginRun( Reader ) == 0 ) {
	cout<<"BeginRun failed"<<endl;
	return 0;
      }
    }
    
    /*** Test each entry here ***/
    SubEvt* pSubEvt = new SubEvt( Reader );
    TimeStamp NewTime( pSubEvt->TrigSec, pSubEvt->TrigNano );

	

    if( (NewTime - CurrRun.CurrTime).GetSeconds() > 120 /* Two minutes */ ) {
      ///////////////////////////added by zzc/////////////////////////////////////////////////////////////////////////////////////////
	  Int_t Z_Bin1,Z_Bin2;
	  Z_Bin2 = int((NewTime.GetSeconds()-Z_StartTime)/Z_WidthOfBin);
	  Z_Bin1 = Z_Bin;
	  if(Z_Bin2 == Z_Bin1)
	  {
		  CurrRun.Breaks.push_back( CurrRun.CurrTime );
		CurrRun.Breaks.push_back( NewTime );
		CurrRun.SkipTime.Add( (NewTime - CurrRun.CurrTime).GetSeconds() );
	  }
	  else
	  {
		  if((Z_Bin>=0)&&(Z_Bin<Z_NumOfBin)){
		Z_VT1[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[1].GetSeconds()-Z_VT1_t);
		Z_VT2[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[2].GetSeconds()-Z_VT2_t);
		Z_VT3[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[3].GetSeconds()-Z_VT3_t);
		Z_VT4[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[4].GetSeconds()-Z_VT4_t);

		Z_SgUp1[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[1]-Z_SgUp1_t);
		Z_SgUp2[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[2]-Z_SgUp2_t);
		Z_SgUp3[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[3]-Z_SgUp3_t);
		Z_SgUp4[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[4]-Z_SgUp4_t);

		Z_SgLow1[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[1]-Z_SgLow1_t);
		Z_SgLow2[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[2]-Z_SgLow2_t);
		Z_SgLow3[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[3]-Z_SgLow3_t);
		Z_SgLow4[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[4]-Z_SgLow4_t);

		Z_NetMuon1[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[1]-Z_NetMuon1_t);
		Z_NetMuon2[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[2]-Z_NetMuon2_t);
		Z_NetMuon3[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[3]-Z_NetMuon3_t);
		Z_NetMuon4[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[4]-Z_NetMuon4_t);

		for(int Det = 0; Det<4; Det++)
		{
			Z_AdMuon[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NAdMuon[Det+1] -	Z_AdMuon_t[Det];
			Z_HMuonL5[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonL5[Det+1] - Z_HMuonL5_t[Det];
			Z_HMuonG5[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG5[Det+1] - Z_HMuonG5_t[Det];
			Z_HMuonG10[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG10[Det+1] - Z_HMuonG10_t[Det];
			Z_HMuonG15[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG15[Det+1] - Z_HMuonG15_t[Det];
		}

		Z_SkipTime[int(Z_Site/2)][Z_Bin] += (CurrRun.SkipTime.GetSeconds()-Z_SkipTime_t);
		Z_FullTime[int(Z_Site/2)][Z_Bin] += (CurrRun.CurrTime.GetSeconds()-CurrRun.StartTime.GetSeconds() - CurrRun.SkipTime.GetSeconds() - Z_FullTime_t);//CurrRun.Fulltime is calculated in EndRun, so...
		Z_Run[int(Z_Site/2)][Z_Bin] = CurrRun.Run;
		/*cout<<"[Run]:"<<Z_Run[int(Z_Site/2)][Z_Bin] <<" [Site]:"<<Z_Site<<" [Bin]:"<<Z_Bin<<" [FullTime]:"
			<<Z_FullTime[int(Z_Site/2)][Z_Bin]<<" [SkipTime]:"<<Z_SkipTime[int(Z_Site/2)][Z_Bin]<<" [Veto1]:"
			<<Z_VT1[int(Z_Site/2)][Z_Bin]<<" [Veto2]:"<<Z_VT2[int(Z_Site/2)][Z_Bin]<<" [Veto3]:"<<Z_VT3[int(Z_Site/2)][Z_Bin]<<
			" [Veto4]:"<<Z_VT4[int(Z_Site/2)][Z_Bin]<<endl;*/
		}
		  Z_VT1_t = CurrRun.VetoTime[1].GetSeconds();
		Z_VT2_t = CurrRun.VetoTime[2].GetSeconds();
		Z_VT3_t = CurrRun.VetoTime[3].GetSeconds();
		Z_VT4_t = CurrRun.VetoTime[4].GetSeconds();

		Z_SgUp1_t = CurrRun.NSingleUp[1];
		Z_SgUp2_t = CurrRun.NSingleUp[2];
		Z_SgUp3_t = CurrRun.NSingleUp[3];
		Z_SgUp4_t = CurrRun.NSingleUp[4];

		Z_SgLow1_t = CurrRun.NSingleLow[1];
		Z_SgLow2_t = CurrRun.NSingleLow[2];
		Z_SgLow3_t = CurrRun.NSingleLow[3];
		Z_SgLow4_t = CurrRun.NSingleLow[4];

		Z_NetMuon1_t = CurrRun.NNetMuon[1];
		Z_NetMuon2_t = CurrRun.NNetMuon[2];
		Z_NetMuon3_t = CurrRun.NNetMuon[3];
		Z_NetMuon4_t = CurrRun.NNetMuon[4];

		for(int Det=0;Det<4;Det++)
		{
			Z_AdMuon_t[Det]		= CurrRun.NAdMuon[Det+1];
			Z_HMuonL5_t[Det]	= CurrRun.NHMuonL5[Det+1];
			Z_HMuonG5_t[Det]	= CurrRun.NHMuonG5[Det+1];
			Z_HMuonG10_t[Det]	= CurrRun.NHMuonG10[Det+1];
			Z_HMuonG15_t[Det]	= CurrRun.NHMuonG15[Det+1];
		}

		
		Z_FullTime_t = CurrRun.CurrTime.GetSeconds()-CurrRun.StartTime.GetSeconds()- CurrRun.SkipTime.GetSeconds();////CurrRun.Fulltime is calculated in EndRun, so...

		CurrRun.Breaks.push_back( CurrRun.CurrTime );
      CurrRun.Breaks.push_back( NewTime );
      CurrRun.SkipTime.Add( (NewTime - CurrRun.CurrTime).GetSeconds() );

	  Z_SkipTime_t = CurrRun.SkipTime.GetSeconds();

	  for(int Bin = Z_Bin1+1;Bin<Z_Bin2;Bin++)
	  {
		  Z_VT1[int(Z_Site/2)][Bin] = 0;
		Z_VT2[int(Z_Site/2)][Bin] = 0;
		Z_VT3[int(Z_Site/2)][Bin] = 0;
		Z_VT4[int(Z_Site/2)][Bin] =0;

		 Z_SgUp1[int(Z_Site/2)][Bin] = 0;
		Z_SgUp2[int(Z_Site/2)][Bin] = 0;
		Z_SgUp3[int(Z_Site/2)][Bin] = 0;
		Z_SgUp4[int(Z_Site/2)][Bin] =0;

		 Z_SgLow1[int(Z_Site/2)][Bin] = 0;
		Z_SgLow2[int(Z_Site/2)][Bin] = 0;
		Z_SgLow3[int(Z_Site/2)][Bin] = 0;
		Z_SgLow4[int(Z_Site/2)][Bin] =0;

		 Z_NetMuon1[int(Z_Site/2)][Bin] = 0;
		Z_NetMuon2[int(Z_Site/2)][Bin] = 0;
		Z_NetMuon3[int(Z_Site/2)][Bin] = 0;
		Z_NetMuon4[int(Z_Site/2)][Bin] =0;

		for(int Det = 0; Det<4; Det++)
		{
			Z_AdMuon[Det][int(Z_Site/2)][Z_Bin] =0;
			Z_HMuonL5[Det][int(Z_Site/2)][Z_Bin] =0;
			Z_HMuonG5[Det][int(Z_Site/2)][Z_Bin] =0;
			Z_HMuonG10[Det][int(Z_Site/2)][Z_Bin] =0;
			Z_HMuonG15[Det][int(Z_Site/2)][Z_Bin] =0;
		}

		Z_SkipTime[int(Z_Site/2)][Bin] = Z_WidthOfBin ;
		Z_FullTime[int(Z_Site/2)][Bin] = 0;//CurrRun.Fulltime is calculated in EndRun, so...
	  }
	  Z_Bin = Z_Bin2;
	  } 
    }
	
	if(int((NewTime.GetSeconds()-Z_StartTime)/Z_WidthOfBin)>Z_Bin)
	{
		//CurrRun.Dump();
		/*cout<<"NSingleUp[1]:"<<CurrRun.NSingleUp[1]<<endl;
		cout<<"NSingleUp[2]:"<<CurrRun.NSingleUp[2]<<endl;
		cout<<"NSingleUp[3]:"<<CurrRun.NSingleUp[3]<<endl;
		cout<<"NSingleUp[4]:"<<CurrRun.NSingleUp[4]<<endl;
		cout<<"NSingleLow[1]:"<<CurrRun.NSingleLow[1]<<endl;
		cout<<"NSingleLow[2]:"<<CurrRun.NSingleLow[2]<<endl;
		cout<<"NSingleLow[3]:"<<CurrRun.NSingleLow[3]<<endl;
		cout<<"NSingleLow[4]:"<<CurrRun.NSingleLow[4]<<endl;

		cout<<"NNetMuon[1]:"<<CurrRun.NNetMuon[1]<<endl;
		cout<<"NNetMuon[2]:"<<CurrRun.NNetMuon[2]<<endl;
		cout<<"NNetMuon[3]:"<<CurrRun.NNetMuon[3]<<endl;
		cout<<"NNetMuon[4]:"<<CurrRun.NNetMuon[4]<<endl;*/

		if((Z_Bin>=0)&&(Z_Bin<Z_NumOfBin)){
		Z_VT1[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[1].GetSeconds()-Z_VT1_t);
		Z_VT2[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[2].GetSeconds()-Z_VT2_t);
		Z_VT3[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[3].GetSeconds()-Z_VT3_t);
		Z_VT4[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[4].GetSeconds()-Z_VT4_t);

		Z_SgUp1[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[1]-Z_SgUp1_t);
		Z_SgUp2[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[2]-Z_SgUp2_t);
		Z_SgUp3[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[3]-Z_SgUp3_t);
		Z_SgUp4[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[4]-Z_SgUp4_t);

		Z_SgLow1[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[1]-Z_SgLow1_t);
		Z_SgLow2[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[2]-Z_SgLow2_t);
		Z_SgLow3[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[3]-Z_SgLow3_t);
		Z_SgLow4[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[4]-Z_SgLow4_t);

		Z_NetMuon1[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[1]-Z_NetMuon1_t);
		Z_NetMuon2[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[2]-Z_NetMuon2_t);
		Z_NetMuon3[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[3]-Z_NetMuon3_t);
		Z_NetMuon4[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[4]-Z_NetMuon4_t);

		for(int Det = 0; Det<4; Det++)
		{
			Z_AdMuon[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NAdMuon[Det+1] -	Z_AdMuon_t[Det];
			Z_HMuonL5[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonL5[Det+1] - Z_HMuonL5_t[Det];
			Z_HMuonG5[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG5[Det+1] - Z_HMuonG5_t[Det];
			Z_HMuonG10[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG10[Det+1] - Z_HMuonG10_t[Det];
			Z_HMuonG15[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG15[Det+1] - Z_HMuonG15_t[Det];
		}

		Z_SkipTime[int(Z_Site/2)][Z_Bin] += (CurrRun.SkipTime.GetSeconds()-Z_SkipTime_t);
		Z_FullTime[int(Z_Site/2)][Z_Bin] += (NewTime.GetSeconds()-CurrRun.StartTime.GetSeconds() - CurrRun.SkipTime.GetSeconds() - Z_FullTime_t);//CurrRun.Fulltime is calculated in EndRun, so...
		Z_Run[int(Z_Site/2)][Z_Bin] = CurrRun.Run;
		cout<<"[Run]:"<<Z_Run[int(Z_Site/2)][Z_Bin] <<" [Site]:"<<Z_Site<<" [Bin]:"<<Z_Bin<<" [FullTime]:"
			<<Z_FullTime[int(Z_Site/2)][Z_Bin]<<" [SkipTime]:"<<Z_SkipTime[int(Z_Site/2)][Z_Bin]<<" [Veto1]:"
			<<Z_VT1[int(Z_Site/2)][Z_Bin]<<" [Veto2]:"<<Z_VT2[int(Z_Site/2)][Z_Bin]<<" [Veto3]:"<<Z_VT3[int(Z_Site/2)][Z_Bin]<<
			" [Veto4]:"<<Z_VT4[int(Z_Site/2)][Z_Bin]<<" [SgUp1]:"
			<<Z_SgUp1[int(Z_Site/2)][Z_Bin]<<" [SgUp2]:"<<Z_SgUp2[int(Z_Site/2)][Z_Bin]<<" [SgUp3]:"<<Z_SgUp3[int(Z_Site/2)][Z_Bin]<<
			" [SgUp4]:"<<Z_SgUp4[int(Z_Site/2)][Z_Bin]<<" [SgLow1]:"
			<<Z_SgLow1[int(Z_Site/2)][Z_Bin]<<" [SgLow2]:"<<Z_SgLow2[int(Z_Site/2)][Z_Bin]<<" [SgLow3]:"<<Z_SgLow3[int(Z_Site/2)][Z_Bin]<<
			" [SgLow4]:"<<Z_SgLow4[int(Z_Site/2)][Z_Bin]<<" [NetMuon1]:"
			<<Z_NetMuon1[int(Z_Site/2)][Z_Bin]<<" [NetMuon2]:"<<Z_NetMuon2[int(Z_Site/2)][Z_Bin]<<" [NetMuon3]:"<<Z_NetMuon3[int(Z_Site/2)][Z_Bin]<<
			" [NetMuon4]:"<<Z_NetMuon4[int(Z_Site/2)][Z_Bin]<<endl;
		}
		Z_VT1_t = CurrRun.VetoTime[1].GetSeconds();
		Z_VT2_t = CurrRun.VetoTime[2].GetSeconds();
		Z_VT3_t = CurrRun.VetoTime[3].GetSeconds();
		Z_VT4_t = CurrRun.VetoTime[4].GetSeconds();

		Z_SgUp1_t = CurrRun.NSingleUp[1];
		Z_SgUp2_t = CurrRun.NSingleUp[2];
		Z_SgUp3_t = CurrRun.NSingleUp[3];//.GetSeconds();
		Z_SgUp4_t = CurrRun.NSingleUp[4];//.GetSeconds();

		Z_SgLow1_t = CurrRun.NSingleLow[1];//.GetSeconds();
		Z_SgLow2_t = CurrRun.NSingleLow[2];//.GetSeconds();
		Z_SgLow3_t = CurrRun.NSingleLow[3];//.GetSeconds();
		Z_SgLow4_t = CurrRun.NSingleLow[4];//.GetSeconds();

		Z_NetMuon1_t = CurrRun.NNetMuon[1];//.GetSeconds();
		Z_NetMuon2_t = CurrRun.NNetMuon[2];//.GetSeconds();
		Z_NetMuon3_t = CurrRun.NNetMuon[3];//.GetSeconds();
		Z_NetMuon4_t = CurrRun.NNetMuon[4];//.GetSeconds();

		for(int Det=0;Det<4;Det++)
		{
			Z_AdMuon_t[Det]		= CurrRun.NAdMuon[Det+1];
			Z_HMuonL5_t[Det]	= CurrRun.NHMuonL5[Det+1];
			Z_HMuonG5_t[Det]	= CurrRun.NHMuonG5[Det+1];
			Z_HMuonG10_t[Det]	= CurrRun.NHMuonG10[Det+1];
			Z_HMuonG15_t[Det]	= CurrRun.NHMuonG15[Det+1];
		}

		Z_SkipTime_t = CurrRun.SkipTime.GetSeconds();
		Z_FullTime_t = NewTime.GetSeconds()-CurrRun.StartTime.GetSeconds()- CurrRun.SkipTime.GetSeconds();////CurrRun.Fulltime is calculated in EndRun, so...
		
		Z_Bin++;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CurrRun.CurrTime = NewTime;

    /* Cache all temporal related event. Give a chance to clean up the queue and do muon Id */
    SubEvtQueue PassedQueue = CachedQueueInsert( NewTime, pSubEvt );

    /* Layer 2. The main loop over every non-muon SubEvt */
    /* ------------------------------------------------- */
    SubEvtQueueIterator it, it_end = PassedQueue.end();
    for( it = PassedQueue.begin(); it != it_end; it++ )  {
      
      /* Build delay coincident event */
      SubEvt* pSubEvt = it->second;
      int ret = BuildEvent( pSubEvt );
      if( ret == 0 )  {
	cout<<"Error in BuildEvent"<<endl;
      }
      
      delete pSubEvt;

    }
    /***  End of SubEvt loop  ***/

  }
  /***  End of stream entry loop  ***/

  if( EndRun( Reader ) == 0 ) {
    cout<<"EndRun failed"<<endl;
    return 0;
  }

  /* End Job */
  /* ------- */
  if( EndJob() == 0 ) {
    cout<<"BeginJob failed"<<endl;
    return 0;
  }

  return 1;
}

int BeginJob( int argc, char** argv )
{
  string inputfile;
  string outputfile;
  string DataSet;
  vector<string> datafiles;
  ///////////////added by zzc//////////////////////////////////////////////////////////////////////////
  memset(Z_VT1,0,sizeof(Z_VT1));
  memset(Z_VT2,0,sizeof(Z_VT2));
  memset(Z_VT3,0,sizeof(Z_VT3));
  memset(Z_VT4,0,sizeof(Z_VT4));

   memset(Z_SgUp1,0,sizeof(Z_SgUp1));
  memset(Z_SgUp2,0,sizeof(Z_SgUp2));
  memset(Z_SgUp3,0,sizeof(Z_SgUp3));
  memset(Z_SgUp4,0,sizeof(Z_SgUp4));

   memset(Z_SgLow1,0,sizeof(Z_SgLow1));
  memset(Z_SgLow2,0,sizeof(Z_SgLow2));
  memset(Z_SgLow3,0,sizeof(Z_SgLow3));
  memset(Z_SgLow4,0,sizeof(Z_SgLow4));

   memset(Z_NetMuon1,0,sizeof(Z_NetMuon1));
  memset(Z_NetMuon2,0,sizeof(Z_NetMuon2));
  memset(Z_NetMuon3,0,sizeof(Z_NetMuon3));
  memset(Z_NetMuon4,0,sizeof(Z_NetMuon4));

  memset(Z_AdMuon,0,sizeof(Z_AdMuon));
  memset(Z_HMuonL5,0,sizeof(Z_HMuonL5));
  memset(Z_HMuonG5,0,sizeof(Z_HMuonG5));
  memset(Z_HMuonG10,0,sizeof(Z_HMuonG10));
  memset(Z_HMuonG15,0,sizeof(Z_HMuonG15));

  memset(Z_SkipTime,0,sizeof(Z_SkipTime));
  memset(Z_LiveTime,0,sizeof(Z_LiveTime));
  memset(Z_FullTime,0,sizeof(Z_FullTime));
  memset(Z_Run,0,sizeof(Z_Run));
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /* Argument parsing */
  /* ---------------- */
  if( argc != 5 ) {
    Usage();
  } else {
    inputfile = argv[1];
    outputfile = argv[2];
    RunInfoOutput = argv[3];
    DataSet = argv[4];

    string extension = inputfile.substr( inputfile.length()-5, 5 );
    /* A single input file */
    if( extension == ".root" )  {
      //cout<<"A single input file, "<<inputfile<<endl;
      datafiles.push_back(inputfile);
    }
    /* Input file is a list */
    else if( extension == ".list" )  {
      //cout<<"A list of root files, "<<inputfile<<endl;
      /* Grab all the data files in the list */
      ifstream inlist( inputfile.c_str() );
      string line;
      while( getline( inlist, line ) )  {
        datafiles.push_back( line );
      }
    }

    if( DataSet == "Gd" )      AllCut = new Cuts( Cuts::Gd );
    else if ( DataSet == "H" ) AllCut = new Cuts( Cuts::H  );
    else {
      cout<<"Unknown data set "<<endl;
      exit(0);
    }
  }

  /* Load the StreamChain and initializa StreamChain Tree reader */
  /* ----------------------------------------------------------- */
  StreamChain = new TChain("Stream");

  for( unsigned int i =0; i<datafiles.size(); i++ ) {
    StreamChain->Add( datafiles[i].c_str() );
  }
  //cout<<datafiles.size()<<" data files will be processed."<<endl;

  Reader = new StreamReader;
  Reader->Init(StreamChain);

  /* Prepare the output tree */
  aEventTree = new EventTree("Event",outputfile.c_str(),0);

  return 1;
}

int EndJob()
{
  aEventTree->Close();

  
  return 1;
}

int BeginRun(StreamReader* Reader)
{
  cout<<"Start to process run: " << Reader->Run <<" ... "<<endl;
  CurrRun.Reset();
  CurrRun.Run = Reader->Run;
  CurrRun.Site = Reader->Site;
  CurrRun.StartTime = TimeStamp( Reader->TrigSec, Reader->TrigNano );
  CurrRun.CurrTime = CurrRun.StartTime;
  CurrRun.SkipTime = TimeStamp( 0, 0 );

  ////////////////////added by zzc//////////////////////////////////////////////////////////////////
  Z_Site = CurrRun.Site;
  Z_Bin = int((CurrRun.StartTime.GetSeconds()-Z_StartTime)/Z_WidthOfBin);
  Z_BeginBin = Z_Bin;

  //////////////////////////////////////////////////////////////////////////////////////////////////

  /* Reset all detectors' event searching status to waiting */
  for( int det = 1; det <= 4; det++ ) {
    RunStatusDict[ det ] = RunStatus::waiting;
  }

  /* Reset all last muon time stamp to BOT */
  LastMuonT       = TimeStamp::GetBOT();
  for( int det = 1; det <= 4; det++ ) {
    LastAdMuonT[det]     = TimeStamp::GetBOT();
    LastShowerMuonT[det] = TimeStamp::GetBOT();
    LastNetMuonT[det]    = TimeStamp::GetBOT();
    MuonVetoTime[det]    = TimeStamp::GetBOT();
    LastSubEvtT[det]     = TimeStamp::GetBOT();
  }

  return 1;
}

int EndRun(StreamReader* Reader)
{
	cout<<"End process Run: "<< Reader->Run <<" ... "<<endl;
  CurrRun.StopTime = TimeStamp( Reader->TrigSec, Reader->TrigNano );
  CurrRun.FullTime = CurrRun.StopTime - CurrRun.StartTime - CurrRun.SkipTime;
  //CurrRun.Dump();
  CurrRun.DumpToFile( RunInfoOutput );
  Z_EndBin = int((CurrRun.StopTime.GetSeconds()-Z_StartTime)/Z_WidthOfBin);

  /////////////////////////////added by zzc//////////////////////////////////////////
  if((Z_Bin>=0)&&(Z_Bin<Z_NumOfBin)){
        Z_VT1[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[1].GetSeconds()-Z_VT1_t);
		Z_VT2[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[2].GetSeconds()-Z_VT2_t);
		Z_VT3[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[3].GetSeconds()-Z_VT3_t);
		Z_VT4[int(Z_Site/2)][Z_Bin] += (CurrRun.VetoTime[4].GetSeconds()-Z_VT4_t);

		Z_SgUp1[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[1]-Z_SgUp1_t);
		Z_SgUp2[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[2]-Z_SgUp2_t);
		Z_SgUp3[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[3]-Z_SgUp3_t);
		Z_SgUp4[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleUp[4]-Z_SgUp4_t);

		Z_SgLow1[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[1]-Z_SgLow1_t);
		Z_SgLow2[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[2]-Z_SgLow2_t);
		Z_SgLow3[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[3]-Z_SgLow3_t);
		Z_SgLow4[int(Z_Site/2)][Z_Bin] += (CurrRun.NSingleLow[4]-Z_SgLow4_t);

		Z_NetMuon1[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[1]-Z_NetMuon1_t);
		Z_NetMuon2[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[2]-Z_NetMuon2_t);
		Z_NetMuon3[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[3]-Z_NetMuon3_t);
		Z_NetMuon4[int(Z_Site/2)][Z_Bin] += (CurrRun.NNetMuon[4]-Z_NetMuon4_t);

		for(int Det = 0; Det<4; Det++)
		{
			Z_AdMuon[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NAdMuon[Det+1] -	Z_AdMuon_t[Det];
			Z_HMuonL5[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonL5[Det+1] - Z_HMuonL5_t[Det];
			Z_HMuonG5[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG5[Det+1] - Z_HMuonG5_t[Det];
			Z_HMuonG10[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG10[Det+1] - Z_HMuonG10_t[Det];
			Z_HMuonG15[Det][int(Z_Site/2)][Z_Bin] += CurrRun.NHMuonG15[Det+1] - Z_HMuonG15_t[Det];
		}

		Z_SkipTime[int(Z_Site/2)][Z_Bin] += (CurrRun.SkipTime.GetSeconds()-Z_SkipTime_t);
		Z_FullTime[int(Z_Site/2)][Z_Bin] += (CurrRun.FullTime.GetSeconds()-Z_FullTime_t);
		Z_Run[int(Z_Site/2)][Z_Bin] = CurrRun.Run;
		cout<<"[Run]:"<<Z_Run[int(Z_Site/2)][Z_Bin] <<" [Site]:"<<Z_Site<<" [Bin]:"<<Z_Bin<<" [FullTime]:"
			<<Z_FullTime[int(Z_Site/2)][Z_Bin]<<" [SkipTime]:"<<Z_SkipTime[int(Z_Site/2)][Z_Bin]<<" [Veto1]:"
			<<Z_VT1[int(Z_Site/2)][Z_Bin]<<" [Veto2]:"<<Z_VT2[int(Z_Site/2)][Z_Bin]<<" [Veto3]:"<<Z_VT3[int(Z_Site/2)][Z_Bin]<<
			" [Veto4]:"<<Z_VT4[int(Z_Site/2)][Z_Bin]<<endl;
  }
		Z_VT1_t = 0;//CurrRun.VetoTime[1].GetSeconds();
		Z_VT2_t = 0;//CurrRun.VetoTime[2].GetSeconds();
		Z_VT3_t = 0;//CurrRun.VetoTime[3].GetSeconds();
		Z_VT4_t = 0;//CurrRun.VetoTime[4].GetSeconds();

		Z_SgUp1_t = 0;
		Z_SgUp2_t = 0;
		Z_SgUp3_t = 0;
		Z_SgUp4_t =0;

		 Z_SgLow1_t = 0;
		Z_SgLow2_t = 0;
		Z_SgLow3_t = 0;
		Z_SgLow4_t =0;

		 Z_NetMuon1_t = 0;
		Z_NetMuon2_t = 0;
		Z_NetMuon3_t = 0;
		Z_NetMuon4_t =0;

		for(int Det=0;Det<4;Det++)
		{
			Z_AdMuon_t[Det]		= 0;
			Z_HMuonL5_t[Det]	= 0;
			Z_HMuonG5_t[Det]	= 0;
			Z_HMuonG10_t[Det]	= 0;
			Z_HMuonG15_t[Det]	= 0;
		}

		Z_SkipTime_t = 0;//CurrRun.SkipTime.GetSeconds();
		Z_FullTime_t = 0;//CurrRun.FullTime.GetSeconds();
  
  /////////////////////////////////////////////////////////////////////////////////////

/////////////added by zzc//////////////////////////////////////////////////
  FILE* m_outfile = fopen("InfoInEachBin.txt", "a");
  Int_t Site = int(Z_Site/2);
  //title
   //fprintf(m_outfile,"		[Run]		[Site]  [Bin]		[LiveTime]		 [StartTime]				[EndTime]		[FullTime]		[SkipTime]			[Veto1]			[Veto2]			[Veto3]			[Veto4]  \n");
  for(int Bin=Z_BeginBin;Bin<=Z_EndBin;Bin++)
  {
	  Double_t LiveTime;
	  if(Site==0)
	  {
		  LiveTime = Z_FullTime[Site][Bin] - Z_VT1[Site][Bin] - Z_VT2[Site][Bin];
	  }
	  else if(Site == 1)
	  {
		  LiveTime = Z_FullTime[Site][Bin] - Z_VT1[Site][Bin];
	  }
	  else
	  {
		  LiveTime = Z_FullTime[Site][Bin] - Z_VT1[Site][Bin] - Z_VT2[Site][Bin] - Z_VT3[Site][Bin];
	  }
	  if((Bin>=0)&&(Bin<Z_NumOfBin)){
/*[Run][Site][Bin][LiveTime][StartTime][EndTime][FullTime][SkipTime][Veto1][Veto2][Veto3][Veto4][SgUp1][SgUp2][SgUp3][SgUp4][SgLow1][SgLow2][SgLow3][SgLow4][NetMuon1][NetMuon2][NetMuon3][NetMuon4]  */
  fprintf(m_outfile,
	  "%10d %10d %10d %15.10f %15.10f %15.10f %15.10f %15.10f  %15.10f %15.10f %15.10f %15.10f %15d %15d %15d %15d %15d %15d %15d %15d %15d %15d %15d %15d",
	  Z_Run[Site][Bin], Site, Bin,LiveTime, 
	  Z_StartTime + Bin*Z_WidthOfBin, Z_StartTime + (Bin+1)*Z_WidthOfBin, Z_FullTime[Site][Bin], Z_SkipTime[Site][Bin],
	  Z_VT1[Site][Bin],Z_VT2[Site][Bin],Z_VT3[Site][Bin],Z_VT4[Site][Bin],
	  Z_SgUp1[Site][Bin],Z_SgUp2[Site][Bin],Z_SgUp3[Site][Bin],Z_SgUp4[Site][Bin],
	  Z_SgLow1[Site][Bin],Z_SgLow2[Site][Bin],Z_SgLow3[Site][Bin],Z_SgLow4[Site][Bin],
	  Z_NetMuon1[Site][Bin],Z_NetMuon2[Site][Bin],Z_NetMuon3[Site][Bin],Z_NetMuon4[Site][Bin]
	  );
	  for(int Det=0;Det<4;Det++)
	  {
		  fprintf(m_outfile,"%15d ",Z_AdMuon[Det][Site][Bin]);
	  }
	  for(int Det=0;Det<4;Det++)
	  {
		  fprintf(m_outfile,"%15d ",Z_HMuonL5[Det][Site][Bin]);
	  }
	  for(int Det=0;Det<4;Det++)
	  {
		  fprintf(m_outfile,"%15d ",Z_HMuonG5[Det][Site][Bin]);
	  }
	  for(int Det=0;Det<4;Det++)
	  {
		  fprintf(m_outfile,"%15d ",Z_HMuonG10[Det][Site][Bin]);
	  }
	  for(int Det=0;Det<4;Det++)
	  {
		  fprintf(m_outfile,"%15d ",Z_HMuonG15[Det][Site][Bin]);
	  }
 
  fprintf(m_outfile,"\n");
  }
  }
  
  fclose(m_outfile);

  ///////////////////////////////////////////////////////////////////////////
  ///////////////added by zzc///////////////////////////////
  memset(Z_VT1,0,sizeof(Z_VT1));
  memset(Z_VT2,0,sizeof(Z_VT2));
  memset(Z_VT3,0,sizeof(Z_VT3));
  memset(Z_VT4,0,sizeof(Z_VT4));

   memset(Z_SgUp1,0,sizeof(Z_SgUp1));
  memset(Z_SgUp2,0,sizeof(Z_SgUp2));
  memset(Z_SgUp3,0,sizeof(Z_SgUp3));
  memset(Z_SgUp4,0,sizeof(Z_SgUp4));

   memset(Z_SgLow1,0,sizeof(Z_SgLow1));
  memset(Z_SgLow2,0,sizeof(Z_SgLow2));
  memset(Z_SgLow3,0,sizeof(Z_SgLow3));
  memset(Z_SgLow4,0,sizeof(Z_SgLow4));

   memset(Z_NetMuon1,0,sizeof(Z_NetMuon1));
  memset(Z_NetMuon2,0,sizeof(Z_NetMuon2));
  memset(Z_NetMuon3,0,sizeof(Z_NetMuon3));
  memset(Z_NetMuon4,0,sizeof(Z_NetMuon4));

  memset(Z_AdMuon,0,sizeof(Z_AdMuon));
  memset(Z_HMuonL5,0,sizeof(Z_HMuonL5));
  memset(Z_HMuonG5,0,sizeof(Z_HMuonG5));
  memset(Z_HMuonG10,0,sizeof(Z_HMuonG10));
  memset(Z_HMuonG15,0,sizeof(Z_HMuonG15));

  memset(Z_SkipTime,0,sizeof(Z_SkipTime));
  memset(Z_LiveTime,0,sizeof(Z_LiveTime));
  memset(Z_FullTime,0,sizeof(Z_FullTime));
  memset(Z_Run,0,sizeof(Z_Run));
  ////////////////////////////////////////////////////////
  
  return 1;
}
