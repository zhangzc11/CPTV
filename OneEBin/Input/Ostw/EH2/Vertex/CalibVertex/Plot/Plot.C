#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "math.h"
#include <string>
#include <iostream>
using namespace std;

void Extract( string File, double Mean[3], double Sigma[3] );

int Plot()
{
  bool Ge = true;
  bool Co = !Ge;

  string CoCalibFile[6][9] = {
    "../data/EH1_AmC_Co60_A/Output-1-0.root",
    "../data/EH1_AmC_Co60_A/Output-1-1350.root",
    "../data/EH1_AmC_Co60_A/Output-1-n1350.root",
    "../data/EH1_AmC_Co60_B/Output-1-0.root",
    "../data/EH1_AmC_Co60_B/Output-1-1350.root",
    "../data/EH1_AmC_Co60_B/Output-1-n1350.root",
    "../data/EH1_AmC_Co60_C/Output-1-0.root",
    "../data/EH1_AmC_Co60_C/Output-1-1350.root",
    "../data/EH1_AmC_Co60_C/Output-1-n1350.root",

    "../data/EH1_AmC_Co60_A/Output-2-0.root",
    "../data/EH1_AmC_Co60_A/Output-2-1350.root",
    "../data/EH1_AmC_Co60_A/Output-2-n1350.root",
    "../data/EH1_AmC_Co60_B/Output-2-0.root",
    "../data/EH1_AmC_Co60_B/Output-2-1350.root",
    "../data/EH1_AmC_Co60_B/Output-2-n1350.root",
    "../data/EH1_AmC_Co60_C/Output-2-0.root",
    "../data/EH1_AmC_Co60_C/Output-2-1350.root",
    "../data/EH1_AmC_Co60_C/Output-2-n1350.root",

    "../data/EH2_AmC_Co60_A/Output-1-0.root",
    "../data/EH2_AmC_Co60_A/Output-1-1350.root",
    "../data/EH2_AmC_Co60_A/Output-1-n1350.root",
    "../data/EH2_AmC_Co60_B/Output-1-0.root",
    "../data/EH2_AmC_Co60_B/Output-1-1350.root",
    "../data/EH2_AmC_Co60_B/Output-1-n1350.root",
    "../data/EH2_AmC_Co60_C/Output-1-0.root",
    "",
    "",

    "../data/EH3_AmC_Co60_A/Output-1-0.root",
    "../data/EH3_AmC_Co60_A/Output-1-1350.root",
    "../data/EH3_AmC_Co60_A/Output-1-n1350.root",
    "../data/EH3_AmC_Co60_B/Output-1-0.root",
    "../data/EH3_AmC_Co60_B/Output-1-1350.root",
    "../data/EH3_AmC_Co60_B/Output-1-n1350.root",
    "../data/EH3_AmC_Co60_C/Output-1-0.root",
    "../data/EH3_AmC_Co60_C/Output-1-1350.root",
    "../data/EH3_AmC_Co60_C/Output-1-n1350.root",

    "../data/EH3_AmC_Co60_A/Output-2-0.root",
    "../data/EH3_AmC_Co60_A/Output-2-1350.root",
    "../data/EH3_AmC_Co60_A/Output-2-n1350.root",
    "../data/EH3_AmC_Co60_B/Output-2-0.root",
    "../data/EH3_AmC_Co60_B/Output-2-1350.root",
    "../data/EH3_AmC_Co60_B/Output-2-n1350.root",
    "../data/EH3_AmC_Co60_C/Output-2-0.root",
    "../data/EH3_AmC_Co60_C/Output-2-1350.root",
    "../data/EH3_AmC_Co60_C/Output-2-n1350.root",

    "../data/EH3_AmC_Co60_A/Output-3-0.root",
    "../data/EH3_AmC_Co60_A/Output-3-1350.root",
    "../data/EH3_AmC_Co60_A/Output-3-n1350.root",
    "../data/EH3_AmC_Co60_B/Output-3-0.root",
    "../data/EH3_AmC_Co60_B/Output-3-1350.root",
    "../data/EH3_AmC_Co60_B/Output-3-n1350.root",
    "../data/EH3_AmC_Co60_C/Output-3-0.root",
    "../data/EH3_AmC_Co60_C/Output-3-1350.root",
    "../data/EH3_AmC_Co60_C/Output-3-n1350.root"
  };

  string GeCalibFile[6][9] = { 
    "../data/EH1_Ge68_A/Output-1-0.root",
    "../data/EH1_Ge68_A/Output-1-1350.root",
    "../data/EH1_Ge68_A/Output-1-n1350.root",
    "../data/EH1_Ge68_B/Output-1-0.root",
    "../data/EH1_Ge68_B/Output-1-1350.root",
    "../data/EH1_Ge68_B/Output-1-n1350.root",
    "../data/EH1_Ge68_C/Output-1-0.root",
    "../data/EH1_Ge68_C/Output-1-1350.root",
    "../data/EH1_Ge68_C/Output-1-n1350.root",

    "../data/EH1_Ge68_A/Output-2-0.root",
    "../data/EH1_Ge68_A/Output-2-1350.root",
    "../data/EH1_Ge68_A/Output-2-n1350.root",
    "../data/EH1_Ge68_B/Output-2-0.root",
    "../data/EH1_Ge68_B/Output-2-1350.root",
    "../data/EH1_Ge68_B/Output-2-n1350.root",
    "../data/EH1_Ge68_C/Output-2-0.root",
    "../data/EH1_Ge68_C/Output-2-1350.root",
    "../data/EH1_Ge68_C/Output-2-n1350.root",

    "../data/EH2_Ge68_A/Output-1-0.root",
    "../data/EH2_Ge68_A/Output-1-1350.root",
    "../data/EH2_Ge68_A/Output-1-n1350.root",
    "../data/EH2_Ge68_B/Output-1-0.root",
    "../data/EH2_Ge68_B/Output-1-1350.root",
    "../data/EH2_Ge68_B/Output-1-n1350.root",
    "../data/EH2_Ge68_C/Output-1-0.root",
    "../data/EH2_Ge68_C/Output-1-1350.root",
    "../data/EH2_Ge68_C/Output-1-n1350.root",

    "../data/EH3_Ge68_A/Output-1-0.root",
    "../data/EH3_Ge68_A/Output-1-1350.root",
    "../data/EH3_Ge68_A/Output-1-n1350.root",
    "../data/EH3_Ge68_B/Output-1-0.root",
    "../data/EH3_Ge68_B/Output-1-1350.root",
    "../data/EH3_Ge68_B/Output-1-n1350.root",
    "../data/EH3_Ge68_C/Output-1-0.root",
    "../data/EH3_Ge68_C/Output-1-1350.root",
    "../data/EH3_Ge68_C/Output-1-n1350.root",

    "../data/EH3_Ge68_A/Output-2-0.root",
    "../data/EH3_Ge68_A/Output-2-1350.root",
    "../data/EH3_Ge68_A/Output-2-n1350.root",
    "../data/EH3_Ge68_B/Output-2-0.root",
    "../data/EH3_Ge68_B/Output-2-1350.root",
    "../data/EH3_Ge68_B/Output-2-n1350.root",
    "../data/EH3_Ge68_C/Output-2-0.root",
    "../data/EH3_Ge68_C/Output-2-1350.root",
    "../data/EH3_Ge68_C/Output-2-n1350.root",

    "../data/EH3_Ge68_A/Output-3-0.root",
    "../data/EH3_Ge68_A/Output-3-1350.root",
    "../data/EH3_Ge68_A/Output-3-n1350.root",
    "../data/EH3_Ge68_B/Output-3-0.root",
    "../data/EH3_Ge68_B/Output-3-1350.root",
    "../data/EH3_Ge68_B/Output-3-n1350.root",
    "../data/EH3_Ge68_C/Output-3-0.root",
    "../data/EH3_Ge68_C/Output-3-1350.root",
    "../data/EH3_Ge68_C/Output-3-n1350.root"
  };

  double Mean[6][9][3], Sigma[6][9][3];
  
  for( int Ad=0; Ad<6; Ad++ ) {
    for( int Pos=0; Pos<9; Pos++ ) {
      if( Ge ) {
	Extract( GeCalibFile[Ad][Pos].c_str(), Mean[Ad][Pos], Sigma[Ad][Pos] );
      } else {
	Extract( CoCalibFile[Ad][Pos].c_str(), Mean[Ad][Pos], Sigma[Ad][Pos] );
      }
    }
  }

  /* 0 for mean and 1 for rms */
  double MeanFluc[9][3][2], SigmaFluc[9][3][2];
  int NMean[9][3];
  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      MeanFluc[Pos][dem][0] = 0;
      MeanFluc[Pos][dem][1] = 0;
      SigmaFluc[Pos][dem][0] = 0;
      SigmaFluc[Pos][dem][1] = 0;
      NMean[Pos][dem] = 0;
    }
  }

  /* Mean of means */
  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      for( int Ad=0; Ad<6; Ad++ ) {
	if( Sigma[Ad][Pos][dem] > 0.0001 ) {
	  MeanFluc[Pos][dem][0] += Mean[Ad][Pos][dem];
	  NMean[Pos][dem]+=1;
	}
      }
    }
  }  
  
  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      MeanFluc[Pos][dem][0] /= NMean[Pos][dem];
    }
  }
  
  /* RMS of means */
  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      for( int Ad=0; Ad<6; Ad++ ) {
	if( Sigma[Ad][Pos][dem] > 0.0001 ) {
	  MeanFluc[Pos][dem][1] += pow( (Mean[Ad][Pos][dem]-MeanFluc[Pos][dem][0]), 2 );
	}
      }
    }
  }

  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      MeanFluc[Pos][dem][1] /= NMean[Pos][dem];
      MeanFluc[Pos][dem][1] = sqrt( MeanFluc[Pos][dem][1] );
    }
  }

  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      cout<<MeanFluc[Pos][dem][0]<<"+/-"<<MeanFluc[Pos][dem][1]<<"  ";
    }
    cout<<endl;
  }
    
  /* =========================================== */
  /* Mean of sigmas */
  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      for( int Ad=0; Ad<6; Ad++ ) {
	if( Sigma[Ad][Pos][dem] > 0.0001 ) {
	  SigmaFluc[Pos][dem][0] += Sigma[Ad][Pos][dem];
	}
      }
    }
  }

  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      SigmaFluc[Pos][dem][0] /= NMean[Pos][dem];
    }
  }

  /* RMS of sigmas */
  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      for( int Ad=0; Ad<6; Ad++ ) {
	if( Sigma[Ad][Pos][dem] > 0.0001 ) {
	  SigmaFluc[Pos][dem][1] += pow( (Sigma[Ad][Pos][dem]-SigmaFluc[Pos][dem][0]), 2 );
	}
      }
    }
  }

  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      SigmaFluc[Pos][dem][1] /= NMean[Pos][dem];
      SigmaFluc[Pos][dem][1] = sqrt( SigmaFluc[Pos][dem][1] );
    }
  }

  cout<<endl;
  for( int Pos=0; Pos<9; Pos++ ) {
    for( int dem=0; dem<3; dem++ ) {
      cout<<SigmaFluc[Pos][dem][0]<<"+/-"<<SigmaFluc[Pos][dem][1]<<"  ";      
    }
    cout<<endl;    
  }
  

  cout<<endl;
  for( int Ad=0; Ad<6; Ad++ ) {
    cout<<Mean[Ad][1][0]<<" ";
  }
  cout<<endl;
  for( int Ad=0; Ad<6; Ad++ ) {
    cout<<Sigma[Ad][1][0]<<" ";
  }  
  cout<<endl;
  cout<<NMean[1][0]<<endl;

  /* Make a plot for each of them */
  string PlotTitle[12] = { "MeanX", "MeanY", "MeanZ",
			   "MeanXFluc", "MeanYFluc", "MeanZFluc",
			   "SigmaX", "SigmaY", "SigmaZ",
			   "SigmaXFluc", "SigmaYFluc", "SigmaZFluc" };

  const Int_t nx = 3;
  const Int_t ny = 3;
  char *AcuName[nx]  = { "ACUA", "ACUB", "ACUC"  };
  char *Position[ny] = { "-1350", "0",   "1350" };
  
  TFile Plots("Results.root","RECREATE");
  
  for( int ng = 0; ng<12; ng++ )  {

    TH2F *hnew = new TH2F( PlotTitle[ng].c_str(), PlotTitle[ng].c_str(), 3,0,3,3,0,3 );
    hnew->SetBit(TH1::kCanRebin);
    hnew->SetStats(0);

    int alpha = ng % 6;
    int pos = alpha % 3;
    int type = int(alpha/3);  /* 0 for mean, and 1 for fluctuation. */

    if( ng<6 ) {
      hnew->SetBinContent( 1,2, MeanFluc[0][pos][type] );
      hnew->SetBinContent( 1,3, MeanFluc[1][pos][type] );
      hnew->SetBinContent( 1,1, MeanFluc[2][pos][type] );
      hnew->SetBinContent( 2,2, MeanFluc[3][pos][type] );
      hnew->SetBinContent( 2,3, MeanFluc[4][pos][type] );
      hnew->SetBinContent( 2,1, MeanFluc[5][pos][type] );
      hnew->SetBinContent( 3,2, MeanFluc[6][pos][type] );
      hnew->SetBinContent( 3,3, MeanFluc[7][pos][type] );
      hnew->SetBinContent( 3,1, MeanFluc[8][pos][type] );
    } else {
      hnew->SetBinContent( 1,2, SigmaFluc[0][pos][type] );
      hnew->SetBinContent( 1,3, SigmaFluc[1][pos][type] );
      hnew->SetBinContent( 1,1, SigmaFluc[2][pos][type] );
      hnew->SetBinContent( 2,2, SigmaFluc[3][pos][type] );
      hnew->SetBinContent( 2,3, SigmaFluc[4][pos][type] );
      hnew->SetBinContent( 2,1, SigmaFluc[5][pos][type] );
      hnew->SetBinContent( 3,2, SigmaFluc[6][pos][type] );
      hnew->SetBinContent( 3,3, SigmaFluc[7][pos][type] );
      hnew->SetBinContent( 3,1, SigmaFluc[8][pos][type] );
    }
    
    for( int acu=0; acu<3; acu++ ) {
      hnew->GetXaxis()->SetBinLabel( acu+1, AcuName[acu] );
    }
    for( int pos=0; pos<3; pos++ ) {
      hnew->GetYaxis()->SetBinLabel( pos+1, Position[pos] );
    }
    
    hnew->LabelsDeflate("X");
    hnew->LabelsDeflate("Y");
    hnew->LabelsOption("v");
    
    TCanvas* c = new TCanvas;
    hnew->SetStats(0);
    hnew->LabelsOption("h","X");
    hnew->GetXaxis()->SetLabelSize(0.08);
    hnew->GetYaxis()->SetLabelSize(0.08);
    
    if( type==0 ) {
      hnew->SetMarkerSize(3.0);
      hnew->Draw("text");
    } else {
      hnew->Draw("colz");
    }
    c->Print( (PlotTitle[ng]+".ps").c_str() );
  }
  
  Plots.Write();
  Plots.Close();
  
  return 1;
}


void Extract( string File, double Mean[3], double Sigma[3] )
{
  if( File.length() < 1 ) {
    for( int i=0; i<3; i++ ) {
      Mean[i] = 0;
      Sigma[i] = 0;
    }
    return;
  }

  TFile f(File.c_str());
  TH1F* hX = (TH1F*)f.Get("SglX");
  TH1F* hY = (TH1F*)f.Get("SglY");
  TH1F* hZ = (TH1F*)f.Get("SglZ");

  TF1 *fg = new TF1("fg","gaus(0)",-2500,2500);

  fg->SetParameters(1000, hX->GetMean(), hX->GetRMS() );
  hX->Fit(fg);
  Mean[0]  = fg->GetParameter(1);
  Sigma[0] = fabs(fg->GetParameter(2));

  fg->SetParameters(1000, hY->GetMean(), hY->GetRMS() );
  hY->Fit(fg);
  Mean[1]  = fg->GetParameter(1);
  Sigma[1] = fabs(fg->GetParameter(2));

  fg->SetParameters(1000, hZ->GetMean(), hZ->GetRMS() );
  hZ->Fit(fg);
  Mean[2]  = fg->GetParameter(1);
  Sigma[2] = fabs(fg->GetParameter(2));

  cout<<File<<endl;
  cout<<Mean[0]<<" "<<Sigma[0]<<endl;
  cout<<Mean[1]<<" "<<Sigma[1]<<endl;
  cout<<Mean[2]<<" "<<Sigma[2]<<endl;
  
}
