#include "Table.h"
#include <string>
#include <iostream>
#include "TGraphErrors.h"
#include "TCanvas.h"
using namespace std;

void PlotScan()
{

  string file[6] = {"scan8.txt","scanExcl8.txt","scan4.txt","scanExcl4.txt","scan3.txt","scanExcl3.txt"};
  Table table[6];
  
  for( int i=0; i<6; i++ ) {
    table[i].Open( file[i] );
  }
  
  
  const int n = 8;
  double x[n], xe[n];
  double Gdt13[n], Gdt13e[n];
  double Ht13[n], Ht13e[n];
  int row[6];

  for( int i=0; i<6; i++ ) {
    cout<<table[i].FileName<<endl;
    cout<<table[i].NRows<<endl;
    
    row[i] = table[i].NRows;
    
    // Get data
    for( int p=0; p<row[i]; p++ ) {
      x[p] = p+1;
      xe[p] = 0;
      Gdt13[p] = atof( table[i].Columns["Gd"][p].c_str() );
      Gdt13e[p] = atof( table[i].Columns["GdErr"][p].c_str() );
      Ht13[p] = atof( table[i].Columns["H"][p].c_str() );
      Ht13e[p] = atof( table[i].Columns["HErr"][p].c_str() );

      cout<<Gdt13[p]<<" "<<Gdt13e[p]<<" "<<Ht13[p]<<" "<<Ht13e[p]<<endl;
    }
    
    // Plot them
    TGraphErrors* g = new TGraphErrors( row[i], x, Gdt13, xe, Gdt13e );
    TGraphErrors* h = new TGraphErrors( row[i], x, Ht13, xe, Ht13e );
    TCanvas * c = new TCanvas( table[i].FileName.c_str(), table[i].FileName.c_str() );
    g->SetMarkerColor(kRed);
    g->SetMarkerStyle(21);
    g->GetYaxis()->SetRangeUser(0.02,0.14);
    g->Draw("alp");

    h->SetMarkerColor(kBlue);
    h->SetMarkerStyle(21);
    h->Draw("lpsame");

    c->Print( (table[i].FileName+".jpg").c_str() );
  }
}
