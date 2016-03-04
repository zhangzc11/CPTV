void Pal0()
{
  static Int_t  colors[500];
  static Bool_t initialized = kFALSE;

  UInt_t Number = 4;
  /*
  Double_t Red[4]  = { 1,   1.0, 1.0, 0.1 };
  Double_t Green[4] = { 1,  1.0, 0.0, 0.0 };
  Double_t Blue[4] = { 1,   0.0, 0.0, 0.0 };
  */
  Double_t Red[4]  =  { 0.0, 0.0, 0.0, 0.0 };
  Double_t Green[4] = { 1.0, 0.0, 1.0, 0.7 };
  Double_t Blue[4] =  { 1.0, 1.0, 0.0, 0.0 };
  Double_t Stops[4] = { 0.0, 6.283e-2, 0.53, 1.0 };  // Can't be above 1. It doesn't give error alert!
  int nb = 500;

  if(!initialized){
    Int_t FI = TColor::CreateGradientColorTable(Number,Stops,Red,Green,Blue,nb);
    for (int i=0; i<nb; i++) colors[i] = FI+i;
    initialized = kTRUE;
    return;
  }
  gStyle->SetPalette(nb,colors);
}


void Pal1()
{
  static Int_t  colors[500];
  static Bool_t initialized = kFALSE;

  UInt_t Number = 6;
  /*
  Double_t Red[4]  = { 1,   1.0, 1.0, 0.1 };
  Double_t Green[4] = { 1,  1.0, 0.0, 0.0 };
  Double_t Blue[4] = { 1,   0.0, 0.0, 0.0 };
  */
  Double_t Red[6]  =  { 1.0,  1.0, 0.0, 0.0, 0.0, 0.0 };
  Double_t Green[6] = { 0.0,  1.0, 1.0, 0.0, 1.0, 0.7 };
  Double_t Blue[6] =  { 0.0,  1.0, 1.0, 1.0, 0.0, 0.0 };
  Double_t Stops[6] = { 0.0, 8.374595e-03, 2.42116e-02, 6.283e-2, 0.53, 1.0 };  // Can't be above 1. It doesn't give error alert!
  int nb = 500;

  if(!initialized){
    Int_t FI = TColor::CreateGradientColorTable(Number,Stops,Red,Green,Blue,nb);
    for (int i=0; i<nb; i++) colors[i] = FI+i;
    initialized = kTRUE;
    return;
  }
  gStyle->SetPalette(nb,colors);
}

void Pal2()
{
  static Int_t  colors[500];
  static Bool_t initialized = kFALSE;
  
  UInt_t Number = 6;
  /*
  Double_t Red[5]  = { 0.1, 1.0,  1.0, 1.0, 0.4 };
  Double_t Green[5] = { 0.5, 1.0,  1.0, 0.0, 0.0 };
  Double_t Blue[5] = { 1, 1.0,  0.0, 0.0, 0.0 };
  */
  Double_t Red[6]  =  { 1.0, 1.0,  0.0, 0.0, 0.0, 0.0 };
  Double_t Green[6] = { 0.0, 1.0,  1.0, 0.0, 1.0, 0.7 };
  Double_t Blue[6] =  { 0.0, 1.0,  1.0, 1.0, 0.0, 0.0 };
  Double_t Stops[6] = { 0.0, 1.46366834084400682e-01, 0.16, 0.2, 0.6, 1.0 };  // Can't be above 1. It doesn't give error alert!
  int nb = 500;

  if(!initialized){
    Int_t FI = TColor::CreateGradientColorTable(Number,Stops,Red,Green,Blue,nb);
    for (int i=0; i<nb; i++) colors[i] = FI+i;
    initialized = kTRUE;
    return;
  }
  gStyle->SetPalette(nb,colors);
}

void Short3()
{
  TCanvas *c1 = new TCanvas("c1","multipads",600,700);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  //gStyle->SetFrameLineWidth(1);

  TPad* m  = new TPad("NF","Near and Far",      0, 0.655, 1, 1    );
  TPad* s1 = new TPad("NF","Near and Far",      0, 0.345, 1, 0.655);
  TPad* s2 = new TPad("NF","Near and Far",      0, 0.0,   1, 0.345);

  m->Draw();
  s1->Draw();
  s2->Draw();


  m->cd();
  m->SetTopMargin(0.1);
  m->SetBottomMargin(0.0);
  m->SetLeftMargin(0.13);
  m->SetRightMargin(0.13);
  /// Far site
  {
    TFile f("../../data/Sample/P12e_1.5MeV/H/EH3.root");

    double xmin = h2dVtxSum->GetXaxis()->GetXmin();
    double xmax = h2dVtxSum->GetXaxis()->GetXmax();
    double ymin = h2dVtxSum->GetYaxis()->GetXmin();
    double ymax = h2dVtxSum->GetYaxis()->GetXmax();
    int    n    = h2dVtxSum->GetXaxis()->GetNbins();
    TH2F * NVtx = new TH2F("n","n",n,ymin,ymax,n,xmin,xmax); // switch x-y axis

    for( int nx=1; nx<=n; nx++ )  {
      for( int ny=1; ny<=n; ny++ )  {
	NVtx->SetBinContent(nx, ny, h2dVtxSum->GetBinContent(ny, nx) );
      }
    }

    NVtx->Rebin2D(3,3);
    NVtx->GetXaxis()->SetRangeUser(1.3, 10.25);
    NVtx->GetYaxis()->SetRangeUser(1.3, 10.25);
    //h2dAccSum->GetZaxis()->SetRangeUser(-10,40);

    NVtx->GetYaxis()->SetLabelSize(0.08);
    NVtx->GetYaxis()->SetTitleSize(0.08);
    NVtx->GetYaxis()->SetTitleOffset(0.6);
    NVtx->GetZaxis()->SetLabelSize(0.06);
    NVtx->GetZaxis()->SetTitleSize(0.08);

    NVtx->GetYaxis()->SetTitle("E_{p} [MeV]");

    //NVtx->SetMinimum(0);
    // What is this principle?
    NVtx->DrawCopy("col");
    TExec *ex1 = new TExec("ex1","Pal0();");
    ex1->Draw();
    NVtx->SetContour(500);
    NVtx->DrawCopy("colz same");
    NVtx->DrawCopy("same axis");
    
    TPaveLabel *label = new TPaveLabel(9.0,8.6,9.8,10,"a");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.65);
    label->Draw();

    f.Close();
  }
  
  // Bottom pad
  s2->cd();
  s2->SetTopMargin(0.0);
  s2->SetBottomMargin(0.15);
  s2->SetLeftMargin(0.13);
  s2->SetRightMargin(0.13);
  /// Far site
  {
    TFile ff("../../data/Sample/P12e_1.5MeV/H/EH3.root");

    h1dNeutronSum->GetXaxis()->SetRangeUser(1.3, 10.25);
    h1dNeutronSum->GetXaxis()->SetLabelSize(0.08);
    h1dNeutronSum->GetXaxis()->SetTitleSize(0.08);
    h1dNeutronSum->GetXaxis()->SetTitleOffset(0.9);

    //h1dNeutronSum->GetYaxis()->SetRangeUser(-50, 1050);
    h1dNeutronSum->GetYaxis()->SetLabelSize(0.08);
    h1dNeutronSum->GetYaxis()->SetTitleSize(0.08);
    h1dNeutronSum->GetYaxis()->SetTitleOffset(0.6);
    
    h1dNeutronSum->GetXaxis()->SetTitle("E_{d} [MeV]");

    h1dNeutronSum->DrawCopy("");
    //leg->AddEntry( h1dNeutronSum, "Far", "le" );
    double FEntries = h1dNeutronSum->Integral();
    ff.Close();
    
    TFile f("../../data/Sample/P12e_1.5MeV/H/Near.root");
    double NEntries = h1dNeutronSum->Integral();
    h1dNeutronSum->Scale(FEntries/NEntries);
    h1dNeutronSum->SetLineColor(kRed);
    h1dNeutronSum->SetMarkerColor(kRed);
    h1dNeutronSum->DrawCopy("same");
    f.Close();

    /*
    TLegend* leg = new TLegend(0.35, 0.57, 0.70, 0.74);
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->AddEntry( ((TObject*)0), "Far", "" );
    leg->AddEntry( ((TObject*)0), "Near", "" );    
    leg->Draw();
    */

    TPaveLabel *label = new TPaveLabel(9.0,625,9.8,800,"c");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.65);
    label->Draw();

    TLine *line = new TLine;
    line->DrawLine(1.3,0, 10.25,0);
  }

  
  // Middle pad
  s1->cd();
  s1->SetTopMargin(0.0);
  s1->SetBottomMargin(0.0);
  s1->SetLeftMargin(0.13);
  s1->SetRightMargin(0.13);
  s1->Draw();
  s1->cd();
  {
    TFile ff("../../data/Sample/P12e_1.5MeV/H/EH3.root");
    
    h2dAccBkgSum->Rebin2D(3,3);
    h2dAccBkgSum->GetXaxis()->SetRangeUser(1.3, 10.25);
    h2dAccBkgSum->GetYaxis()->SetRangeUser(1.3, 10.25);

    h2dAccBkgSum->GetXaxis()->SetLabelSize(0.06);
    h2dAccBkgSum->GetXaxis()->SetTitleSize(0.06);

    h2dAccBkgSum->GetYaxis()->SetLabelSize(0.09);
    h2dAccBkgSum->GetYaxis()->SetTitleSize(0.095);

    h2dAccBkgSum->GetXaxis()->SetTitleOffset(0.5);
    h2dAccBkgSum->GetYaxis()->SetTitleOffset(0.5);

    h2dAccBkgSum->GetZaxis()->SetLabelSize(0.06);
    h2dAccBkgSum->GetZaxis()->SetTitleSize(0.06);

    h2dAccBkgSum->GetXaxis()->SetTitle("E_{d} [MeV]");
    h2dAccBkgSum->GetYaxis()->SetTitle("E_{p} [MeV]");
    

    // What is this principle?
    h2dAccBkgSum->DrawCopy("col");
    TExec *ex2 = new TExec("ex2","Pal0();");
    ex2->Draw();
    h2dAccBkgSum->SetContour(500);
    h2dAccBkgSum->DrawCopy("same colz");
    h2dAccBkgSum->DrawCopy("same axis");

    // top frame is blocked. Now redraw it.
    TLine *line = new TLine;
    //line->DrawLine(1.3,10.6, 10.1,10.6);
    //line->DrawLine(10.1,10.6, 10.1,1.3);

    TPaveLabel *label = new TPaveLabel(9.0,8.6,9.8,10,"b");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.65);
    label->Draw();
    ff.Close();
  }


}
