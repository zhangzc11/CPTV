void Dist()
{
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetFrameLineWidth(1);
  
  TCanvas *c1 = new TCanvas("c1","multipads",700,500);
  gPad->SetLeftMargin(0.15);
  
  TLegend* leg = new TLegend(0.35, 0.12, 0.7, 0.22);
  leg-> SetNColumns(2);
  leg->SetHeader("After Sub.:");

  TFile f("../../data/Sample/Distance/P12e_1.5MeV/H5m/Near.root");
  TH1F* Near = (TH1F*)f.Get("h1dDistAccSum");
  Near->GetYaxis()->SetRangeUser(-3000,12000);
  Near->SetLineColor(4);
  Near->GetYaxis()->SetTitleOffset(1.5);
  //Near->Rebin(5);
  Near->DrawCopy();
  leg->AddEntry( Near, "Near site", "lep" );

  TFile f("../../data/Sample/Distance/P12e_1.5MeV/H5m/EH3.root");
  TH1F* Far = (TH1F*)f.Get("h1dDistAccSum");
  Far->SetLineColor(2);
  Far->GetYaxis()->SetTitleOffset(1.5);
  //Far->Rebin(5);
  Far->DrawCopy("same");
  leg->AddEntry( Far, "Far site", "lep" );

  leg->SetFillColor(0);
  leg->Draw();
  TLine line;
  line.SetLineStyle(2);
  line.DrawLine(0,0,5000,0);

  //h1dDistAccSum->Fit("pol0","","",2000,5000);
  {
    TFile f("../../data/Sample/Distance/P12e_1.5MeV/H5m/Near.root");

    TLegend* leg = new TLegend(0.51, 0.22, 0.80, 0.53);

    TPad* pad = new TPad("name","Title",0.3,0.3,0.935,0.935);
    pad->SetTopMargin(0.05);
    pad->SetBottomMargin(0.2);
    pad->SetLeftMargin(0.2);
    pad->SetRightMargin(0.05);
    pad->Draw();
    pad->cd();
    
    h1dDistVtxSum->SetLineColor(4);
    h1dDistVtxSum->GetYaxis()->SetTitleOffset(1.6);
    h1dDistVtxSum->GetYaxis()->SetLabelSize(0.06);
    h1dDistVtxSum->GetYaxis()->SetTitleSize(0.06);
    h1dDistVtxSum->GetYaxis()->SetNdivisions(405);
    
    h1dDistVtxSum->GetXaxis()->SetNdivisions(405);
    h1dDistVtxSum->GetXaxis()->SetLabelSize(0.06);
    h1dDistVtxSum->GetXaxis()->SetTitleSize(0.06);

    h1dDistVtxSum->DrawCopy();
    h1dDistBkgSum->SetLineColor(1);
    h1dDistBkgSum->DrawCopy("same");
    
    TLine line;
    line.SetLineStyle(2);
    line.DrawLine(2000,0,2000,22250);

    leg->SetHeader("Near site:");
    leg->AddEntry( h1dDistVtxSum, "Before Sub.", "lep" );
    leg->AddEntry( h1dDistBkgSum, "Accidental", "lep" );
    leg->SetFillColor(0);
    leg->Draw();
      
    /*
      label->AddText("Subtraction");
      label->AddText("Validation");
      label->SetFillColor(0);
      label->SetShadowColor(0);
      label->SetBorderSize(1);
      label->Draw();
    */
  }
}
