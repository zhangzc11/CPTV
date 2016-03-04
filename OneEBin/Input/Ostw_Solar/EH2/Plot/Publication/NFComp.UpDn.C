
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

void NFComp()
{
  TCanvas *c1 = new TCanvas("c1","multipads",1400,600);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetFrameLineWidth(1);

  c1->Divide(3,2,0.001,0.000001);


  c1->cd(1);

  gPad->SetTopMargin(0.2);
  gPad->SetBottomMargin(0.0);
  gPad->SetRightMargin(0.15);
  /// Near site
  {
    TFile f("../../data/Sample/P12e_1.5MeV/H/Near.root");
    
    h2dAccSum->GetXaxis()->SetRangeUser(1.3,10);
    h2dAccSum->GetYaxis()->SetRangeUser(1.3,10.5);
    //h2dAccSum->GetZaxis()->SetRangeUser(-20,1.5308177e+03);

    h2dAccSum->GetYaxis()->SetLabelSize(0.06);
    h2dAccSum->GetYaxis()->SetTitleSize(0.06);
    h2dAccSum->GetYaxis()->SetTitleOffset(0.55);
    h2dAccSum->GetZaxis()->SetLabelSize(0.05);
    h2dAccSum->GetZaxis()->SetTitleSize(0.05);

    //h2dAccSum->SetMinimum(0);
    // What is this principle?
    h2dAccSum->DrawCopy("col");
    TExec *ex1 = new TExec("ex1","Pal1();");
    ex1->Draw();
    h2dAccSum->SetContour(500);
    h2dAccSum->DrawCopy("colz same");
    h2dAccSum->DrawCopy("same axis");    


    // top frame is blocked. Now redraw it.
    TLine *line = new TLine;
    line->DrawLine(1.3,10.6, 10.1,10.6);
    line->DrawLine(10.1,10.6, 10.1,1.3);

    TPaveLabel *label = new TPaveLabel(7.5,8.7,10,10.2,"a, Near site");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.5);
    label->Draw();

    f.Close();
  }

  c1->cd(4);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.15);
  gPad->SetBottomMargin(0.2);
  /// Far site
  {
    TFile ff("../../data/Sample/P12e_1.5MeV/H/EH3.root");
    
    h2dAccSum->GetXaxis()->SetRangeUser(1.3,10);
    h2dAccSum->GetYaxis()->SetRangeUser(1.3,10.5);

    h2dAccSum->GetXaxis()->SetLabelSize(0.06);
    h2dAccSum->GetXaxis()->SetTitleSize(0.06);
    h2dAccSum->GetYaxis()->SetLabelSize(0.06);
    h2dAccSum->GetYaxis()->SetTitleSize(0.06);
    h2dAccSum->GetYaxis()->SetTitleOffset(0.55);
    h2dAccSum->GetZaxis()->SetLabelSize(0.05);
    h2dAccSum->GetZaxis()->SetTitleSize(0.05);

    // What is this principle?
    h2dAccSum->DrawCopy("col");
    TExec *ex2 = new TExec("ex2","Pal2();");
    ex2->Draw();
    h2dAccSum->SetContour(500);
    h2dAccSum->DrawCopy("same colz");
    h2dAccSum->DrawCopy("same axis");

    // top frame is blocked. Now redraw it.
    TLine *line = new TLine;
    line->DrawLine(1.3,10.6, 10.1,10.6);
    line->DrawLine(10.1,10.6, 10.1,1.3);

    TPaveLabel *label = new TPaveLabel(7.5,8.7,10,10.2,"d, Far site");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.5);
    label->Draw();
    ff.Close();
  }

  /////////////////////////////////////////////////////////////////
  c1->cd(2);

  gPad->SetTopMargin(0.2);
  gPad->SetBottomMargin(0.0);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.05);
  /// Near site
  {
    TFile f("../../data/Sample/P12e_1.5MeV/H/Near.root");

    h1dNeutronSum->GetXaxis()->SetRangeUser(1.3, 10.5);
    h1dNeutronSum->GetYaxis()->SetLabelSize(0.06);
    h1dNeutronSum->GetYaxis()->SetTitleSize(0.06);
    h1dNeutronSum->GetYaxis()->SetTitleOffset(1.3);

    h1dNeutronSum->DrawCopy("");

    TLine *line = new TLine;
    line->DrawLine(1.3,0.0, 10.5,0.0);

    TPaveLabel *label = new TPaveLabel(9,4400,10,5200,"b");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.5);
    label->Draw();

    f.Close();
  }

  c1->cd(3);
  gPad->SetTopMargin(0.2);
  gPad->SetBottomMargin(0.0);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.1);
  /// Far site
  {
    TFile ff("../../data/Sample/P12e_1.5MeV/H/EH3.root");

    h1dNeutronSum->GetXaxis()->SetRangeUser(1.3, 10.5);
    h1dNeutronSum->GetXaxis()->SetLabelSize(0.06);
    h1dNeutronSum->GetXaxis()->SetTitleSize(0.06);
    h1dNeutronSum->GetYaxis()->SetLabelSize(0.06);
    h1dNeutronSum->GetYaxis()->SetTitleSize(0.06);
    h1dNeutronSum->GetYaxis()->SetTitleOffset(1.3);

    h1dNeutronSum->DrawCopy("");

    TLine *line = new TLine;
    line->DrawLine(1.3,0.0, 10.5,0.0);

    TPaveLabel *label = new TPaveLabel(9,650,10,800,"e");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.5);
    label->Draw();
    ff.Close();
  }
  
  /////////////////////////////////////////////////////////////////
  /*
  c1->cd(3);

  gPad->SetTopMargin(0.2);
  gPad->SetBottomMargin(0.0);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.1);
  /// Near site
  {
    TFile f("../../data/Sample/P12e_1.5MeV/H/Near.root");

    h2dZR2AccSum->GetXaxis()->SetLabelOffset(10000);
    h2dZR2AccSum->Rebin2D(4,4);
    h2dZR2AccSum->GetYaxis()->SetRangeUser(-2100,2100);
    h2dZR2AccSum->GetYaxis()->SetLabelSize(0.06);
    h2dZR2AccSum->GetYaxis()->SetTitleSize(0.06);
    h2dZR2AccSum->GetYaxis()->SetTitleOffset(1.3);    

    h2dZR2AccSum->DrawCopy("box");

    TLine *line = new TLine;
    line->DrawLine(1.3,0.0, 10.5,0.0);

    TPaveLabel *label = new TPaveLabel(3900e3,1400,4450e3,2000,"c");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.5);
    label->Draw();

    f.Close();
  }
  */
  
  c1->cd(6);
  gPad->SetTopMargin(0.1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.1);
  gPad->SetBottomMargin(0.2);
  /// Far site
  {
    TFile ff("../../data/Sample/P12e_1.5MeV/H/EH3.root");
    
    h2dZR2AccSum->Rebin2D(4,4);
    h2dZR2AccSum->GetYaxis()->SetRangeUser(-2100,2100);
    h2dZR2AccSum->GetXaxis()->SetLabelSize(0.06);
    h2dZR2AccSum->GetXaxis()->SetTitleSize(0.06);
    h2dZR2AccSum->GetYaxis()->SetLabelSize(0.06);
    h2dZR2AccSum->GetYaxis()->SetTitleSize(0.06);
    h2dZR2AccSum->GetYaxis()->SetTitleOffset(1.3);

    h2dZR2AccSum->DrawCopy("box");
    
    TLine *line = new TLine;
    line->DrawLine(1.3,0.0, 10.5,0.0);

    TPaveLabel *label = new TPaveLabel(3900e3,1400,4450e3,2000,"f");
    label->SetFillColor(0);
    label->SetShadowColor(0);
    label->SetTextSize(0.5);
    label->Draw();
    ff.Close();
  }


}
