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

void ShortNF()
{
  TCanvas *c1 = new TCanvas("c1","multipads",600,700);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  //gStyle->SetFrameLineWidth(1);

  c1->Divide(1,2,0.001,0.000001);

  c1->cd(1);

  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.0);
  gPad->SetLeftMargin(0.13);
  gPad->SetRightMargin(0.13);
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
    NVtx->GetXaxis()->SetRangeUser(1.3,10.05);
    NVtx->GetYaxis()->SetRangeUser(1.3, 9.05);
    //h2dAccSum->GetZaxis()->SetRangeUser(-10,40);

    NVtx->GetYaxis()->SetLabelSize(0.06);
    NVtx->GetYaxis()->SetTitleSize(0.06);
    NVtx->GetYaxis()->SetTitleOffset(0.9);
    NVtx->GetZaxis()->SetLabelSize(0.05);
    NVtx->GetZaxis()->SetTitleSize(0.05);

    NVtx->GetYaxis()->SetTitle("E_{p} [MeV]");

    //NVtx->SetMinimum(0);
    // What is this principle?
    NVtx->DrawCopy("col");
    TExec *ex1 = new TExec("ex1","Pal0();");
    ex1->Draw();
    NVtx->SetContour(500);
    NVtx->DrawCopy("colz same");
    NVtx->DrawCopy("same axis");
    
    // top frame is blocked. Now redraw it.
    TLine *line = new TLine;
    //line->DrawLine(1.3,10.6, 10.1,10.6);
    //line->DrawLine(10.1,10.6, 10.1,1.3);

    f.Close();
  }
  

  
  c1->cd(2);
  gPad->SetTopMargin(0.0);
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.13);
  gPad->SetRightMargin(0.13);
  /// Far site
  {
    TFile ff("../../data/Sample/P12e_1.5MeV/H/EH3.root");

    h1dNeutronSum->GetXaxis()->SetRangeUser(1.3, 10.05);
    h1dNeutronSum->GetXaxis()->SetLabelSize(0.06);
    h1dNeutronSum->GetXaxis()->SetTitleSize(0.06);
    
    h1dNeutronSum->GetYaxis()->SetRangeUser(-50, 1050);
    h1dNeutronSum->GetYaxis()->SetLabelSize(0.06);
    h1dNeutronSum->GetYaxis()->SetTitleSize(0.06);
    h1dNeutronSum->GetYaxis()->SetTitleOffset(0.9);
    
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

    TLine *line = new TLine;
    line->DrawLine(1.3,0.0, 10.05,0.0);
    
    /*
    line->DrawLine(3.6,700.0, 4.4,700.0);
    line->SetLineColor(kRed);
    line->DrawLine(3.6,580.0, 4.4,580.0);
    */
  }

  // Small pad
  {
    TPad* pad = new TPad("name","Title",0.5,0.5,0.82,0.99);
    pad->SetTopMargin(0.05);
    pad->SetBottomMargin(0.20);
    pad->SetLeftMargin(0.20);
    pad->SetRightMargin(0.0);
    pad->Draw();
    pad->cd();

    TFile ff("../../data/Sample/P12e_1.5MeV/H/EH3.root");

    h2dAccBkgSum->Rebin2D(3,3);
    h2dAccBkgSum->GetXaxis()->SetRangeUser(1.3, 3.9);
    h2dAccBkgSum->GetYaxis()->SetRangeUser(1.3, 3.9);

    h2dAccBkgSum->GetXaxis()->SetLabelSize(0.1);
    h2dAccBkgSum->GetXaxis()->SetTitleSize(0.1);

    h2dAccBkgSum->GetYaxis()->SetLabelSize(0.1);
    h2dAccBkgSum->GetYaxis()->SetTitleSize(0.1);

    h2dAccBkgSum->GetXaxis()->SetTitleOffset(0.9);
    h2dAccBkgSum->GetYaxis()->SetTitleOffset(0.8);

    h2dAccBkgSum->GetZaxis()->SetLabelSize(0.05);
    h2dAccBkgSum->GetZaxis()->SetTitleSize(0.05);

    h2dAccBkgSum->GetXaxis()->SetTitle("E_{d} [MeV]");
    h2dAccBkgSum->GetYaxis()->SetTitle("E_{p} [MeV]");
    

    // What is this principle?
    h2dAccBkgSum->DrawCopy("col");
    TExec *ex2 = new TExec("ex2","Pal0();");
    ex2->Draw();
    h2dAccBkgSum->SetContour(500);
    h2dAccBkgSum->DrawCopy("same col");
    h2dAccBkgSum->DrawCopy("same axis");

    // top frame is blocked. Now redraw it.
    TLine *line = new TLine;
    line->DrawLine(1.3,10.6, 10.1,10.6);
    line->DrawLine(10.1,10.6, 10.1,1.3);

    TPaveLabel *label = new TPaveLabel(8.8,8.7,9.8,10.2,"b");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.5);
    label->Draw();
    ff.Close();
  }


}
