#include "Table.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
  string FileName;
  if( argc == 2 ) {
    FileName = argv[1];
  } else {
    cout<<"Usage:"<<endl;
    cout<<"  g++ main.C"<<endl;
    cout<<"  a.out ../RunInfo.txt"<<endl;
  }  
  
  Table RunInfo( FileName );
  
  double FullTime[6] = {0,0,0,0,0,0};
  double Veto[6]     = {0,0,0,0,0,0};
  double LiveTime[6] = {0,0,0,0,0,0};

  for( int row=0; row<RunInfo.NRows; row++ ) {
    int site = atoi( RunInfo.Columns["Site"][row].c_str() );
    if( site == 1 ) {
      FullTime[0] += atof( RunInfo.Columns["FullTime"][row].c_str() );
      FullTime[1] += atof( RunInfo.Columns["FullTime"][row].c_str() );
      Veto[0] += atof( RunInfo.Columns["Veto1"][row].c_str() );
      Veto[1] += atof( RunInfo.Columns["Veto2"][row].c_str() );
    }
    if( site == 2 ) {
      FullTime[2] += atof( RunInfo.Columns["FullTime"][row].c_str() );
      Veto[2] += atof( RunInfo.Columns["Veto1"][row].c_str() );
    }
    if( site == 4 ) {
      FullTime[3] += atof( RunInfo.Columns["FullTime"][row].c_str() );
      FullTime[4] += atof( RunInfo.Columns["FullTime"][row].c_str() );
      FullTime[5] += atof( RunInfo.Columns["FullTime"][row].c_str() );
      Veto[3] += atof( RunInfo.Columns["Veto1"][row].c_str() );
      Veto[4] += atof( RunInfo.Columns["Veto2"][row].c_str() );
      Veto[5] += atof( RunInfo.Columns["Veto3"][row].c_str() );
    }

  }

  for( int ad=0; ad<6; ad++ ) {
    cout<<ad<<"\t"<<FullTime[ad]/(24*60*60)<<"\t"<<Veto[ad]/(24*60*60)<<"\t"<<1-Veto[ad]/FullTime[ad]<<endl;
  }
  
  return 1;
}

