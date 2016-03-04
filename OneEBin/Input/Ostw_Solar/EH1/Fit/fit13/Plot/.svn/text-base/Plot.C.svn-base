{
  TFile *f = TFile::Open("../result.root");
    
  ////  Muon efficiency plots
  TCanvas MVEffC("MVEffC","MVEffC");
  TMultiGraph *mgMVEff = new TMultiGraph();
  
  MVEff1_0->SetMarkerStyle(20);
  MVEff1_0->SetMarkerColor(2);
  mgMVEff->Add(MVEff1_0);
  MVEff2_0->SetMarkerStyle(20);
  MVEff2_0->SetMarkerColor(3);
  mgMVEff->Add(MVEff2_0);
  MVEff3_0->SetMarkerStyle(20);
  MVEff3_0->SetMarkerColor(4);
  mgMVEff->Add(MVEff3_0);

  MVEff4_0->SetMarkerStyle(4);
  MVEff4_0->SetMarkerColor(2);
  mgMVEff->Add(MVEff4_0);
  MVEff5_0->SetMarkerStyle(4);
  MVEff5_0->SetMarkerColor(3);
  mgMVEff->Add(MVEff5_0);
  MVEff6_0->SetMarkerStyle(4);
  MVEff6_0->SetMarkerColor(4);
  mgMVEff->Add(MVEff6_0);
  mgMVEff->Draw("A");

  mgMVEff->GetXaxis();
  mgMVEff->GetXaxis()->SetTitle("Date");
  mgMVEff->GetXaxis()->SetTimeDisplay(1);
  mgMVEff->GetXaxis()->SetTimeFormat("%d/%m/%y%F1970-01-01 00:00:00");
  
  mgMVEff->GetYaxis()->SetTitle("Efficiency");
  
  mgMVEff->Draw("ALP");
  
  TLegend*  legMVEff = new TLegend(0.3,0.5,0.48,0.8);
  //legMVEff->SetHeader("Poisson Distribution");
  legMVEff->AddEntry(MVEff1_0,"AD1" ,"lep");
  legMVEff->AddEntry(MVEff2_0,"AD2" ,"lep");
  legMVEff->AddEntry(MVEff3_0,"AD3" ,"lep");
  legMVEff->AddEntry(MVEff4_0,"AD4" ,"lep");
  legMVEff->AddEntry(MVEff5_0,"AD5" ,"lep");
  legMVEff->AddEntry(MVEff6_0,"AD6" ,"lep");
  legMVEff->SetTextSize(0.04);
  legMVEff->Draw();
  MVEffC->Print("MVEff.ps");
  
  //// Muon rate plots
  TCanvas RMuonC("RMuonC","RMuonC");
  TMultiGraph *mgRMuon = new TMultiGraph();

  RMuon1_0->SetMarkerStyle(20);
  RMuon1_0->SetMarkerColor(2);
  mgRMuon->Add(RMuon1_0);
  RMuon2_0->SetMarkerStyle(20);
  RMuon2_0->SetMarkerColor(3);
  mgRMuon->Add(RMuon2_0);
  RMuon3_0->SetMarkerStyle(20);
  RMuon3_0->SetMarkerColor(4);
  mgRMuon->Add(RMuon3_0);

  RMuon4_0->SetMarkerStyle(4);
  RMuon4_0->SetMarkerColor(2);
  mgRMuon->Add(RMuon4_0);
  RMuon5_0->SetMarkerStyle(4);
  RMuon5_0->SetMarkerColor(3);
  mgRMuon->Add(RMuon5_0);
  RMuon6_0->SetMarkerStyle(4);
  RMuon6_0->SetMarkerColor(4);
  mgRMuon->Add(RMuon6_0);
  mgRMuon->Draw("A");

  mgRMuon->GetXaxis();
  mgRMuon->GetXaxis()->SetTitle("Date");
  mgRMuon->GetXaxis()->SetTimeDisplay(1);
  mgRMuon->GetXaxis()->SetTimeFormat("%d/%m/%y%F1970-01-01 00:00:00");

  mgRMuon->GetYaxis()->SetTitle("Muon Rate [Hz]");

  mgRMuon->Draw("ALP");

  TLegend*  legRMuon = new TLegend(0.3,0.3,0.48,0.6);
  //leg->SetHeader("Poisson Distribution");
  legRMuon->AddEntry(RMuon1_0,"AD1" ,"lep");
  legRMuon->AddEntry(RMuon2_0,"AD2" ,"lep");
  legRMuon->AddEntry(RMuon3_0,"AD3" ,"lep");
  legRMuon->AddEntry(RMuon4_0,"AD4" ,"lep");
  legRMuon->AddEntry(RMuon5_0,"AD5" ,"lep");
  legRMuon->AddEntry(RMuon6_0,"AD6" ,"lep");
  legRMuon->SetTextSize(0.04);
  legRMuon->Draw();
  RMuonC->Print("RMuon.ps");


  //// Multiplicity cut efficiency plots
  TCanvas MultiEC("MultiEC","MultiEC");
  TMultiGraph *mgMultiE = new TMultiGraph();

  MultiE1_0->SetMarkerStyle(20);
  MultiE1_0->SetMarkerColor(2);
  mgMultiE->Add(MultiE1_0);
  MultiE2_0->SetMarkerStyle(20);
  MultiE2_0->SetMarkerColor(3);
  mgMultiE->Add(MultiE2_0);
  MultiE3_0->SetMarkerStyle(20);
  MultiE3_0->SetMarkerColor(4);
  mgMultiE->Add(MultiE3_0);

  MultiE4_0->SetMarkerStyle(4);
  MultiE4_0->SetMarkerColor(2);
  mgMultiE->Add(MultiE4_0);
  MultiE5_0->SetMarkerStyle(4);
  MultiE5_0->SetMarkerColor(3);
  mgMultiE->Add(MultiE5_0);
  MultiE6_0->SetMarkerStyle(4);
  MultiE6_0->SetMarkerColor(4);
  mgMultiE->Add(MultiE6_0);
  mgMultiE->Draw("A");

  mgMultiE->GetXaxis();
  mgMultiE->GetXaxis()->SetTitle("Date");
  mgMultiE->GetXaxis()->SetTimeDisplay(1);
  mgMultiE->GetXaxis()->SetTimeFormat("%d/%m/%y%F1970-01-01 00:00:00");

  mgMultiE->GetYaxis()->SetTitle("Multiplicity cut efficiency");

  mgMultiE->Draw("ALP");

  TLegend*  legMultiE = new TLegend(0.3,0.3,0.48,0.6);
  //leg->SetHeader("Poisson Distribution");
  legMultiE->AddEntry(MultiE1_0,"AD1" ,"lep");
  legMultiE->AddEntry(MultiE2_0,"AD2" ,"lep");
  legMultiE->AddEntry(MultiE3_0,"AD3" ,"lep");
  legMultiE->AddEntry(MultiE4_0,"AD4" ,"lep");
  legMultiE->AddEntry(MultiE5_0,"AD5" ,"lep");
  legMultiE->AddEntry(MultiE6_0,"AD6" ,"lep");
  legMultiE->SetTextSize(0.04);
  legMultiE->Draw();
  MultiEC->Print("MultiE.ps");

  
  //// Single's rate plots
  TCanvas RSingsC("RSingsC","RSingsC");
  TMultiGraph *mgRSings = new TMultiGraph();

  RSings1_0->SetMarkerStyle(20);
  RSings1_0->SetMarkerColor(2);
  mgRSings->Add(RSings1_0);
  RSings2_0->SetMarkerStyle(20);
  RSings2_0->SetMarkerColor(3);
  mgRSings->Add(RSings2_0);
  RSings3_0->SetMarkerStyle(20);
  RSings3_0->SetMarkerColor(4);
  mgRSings->Add(RSings3_0);

  RSings4_0->SetMarkerStyle(4);
  RSings4_0->SetMarkerColor(2);
  mgRSings->Add(RSings4_0);
  RSings5_0->SetMarkerStyle(4);
  RSings5_0->SetMarkerColor(3);
  mgRSings->Add(RSings5_0);
  RSings6_0->SetMarkerStyle(4);
  RSings6_0->SetMarkerColor(4);
  mgRSings->Add(RSings6_0);
  mgRSings->Draw("A");

  mgRSings->GetXaxis();
  mgRSings->GetXaxis()->SetTitle("Date");
  mgRSings->GetXaxis()->SetTimeDisplay(1);
  mgRSings->GetXaxis()->SetTimeFormat("%d/%m/%y%F1970-01-01 00:00:00");

  mgRSings->GetYaxis()->SetTitle("Single's rate [Hz]");

  mgRSings->Draw("ALP");

  TLegend*  legRSings = new TLegend(0.6,0.5,0.78,0.8);
  //leg->SetHeader("Poisson Distribution");
  legRSings->AddEntry(RSings1_0,"AD1" ,"lep");
  legRSings->AddEntry(RSings2_0,"AD2" ,"lep");
  legRSings->AddEntry(RSings3_0,"AD3" ,"lep");
  legRSings->AddEntry(RSings4_0,"AD4" ,"lep");
  legRSings->AddEntry(RSings5_0,"AD5" ,"lep");
  legRSings->AddEntry(RSings6_0,"AD6" ,"lep");
  legRSings->SetTextSize(0.04);
  legRSings->Draw();
  RSingsC->Print("RSings.ps");


  //// IBD event rate plots
  TCanvas REvtC("REvtC","REvtC");
  TMultiGraph *mgREvt = new TMultiGraph();

  REvt1_0->SetMarkerStyle(20);
  REvt1_0->SetMarkerColor(2);
  mgREvt->Add(REvt1_0);
  REvt2_0->SetMarkerStyle(20);
  REvt2_0->SetMarkerColor(3);
  mgREvt->Add(REvt2_0);
  REvt3_0->SetMarkerStyle(20);
  REvt3_0->SetMarkerColor(4);
  mgREvt->Add(REvt3_0);
  mgREvt->Draw("A");

  mgREvt->GetXaxis();
  mgREvt->GetXaxis()->SetTitle("Date");
  mgREvt->GetXaxis()->SetTimeDisplay(1);
  mgREvt->GetXaxis()->SetTimeFormat("%d/%m/%y%F1970-01-01 00:00:00");

  mgREvt->GetYaxis()->SetTitle("IBD event daily rate [day^{-1}]");

  mgREvt->Draw("ALP");

  TLegend*  legREvt = new TLegend(0.6,0.5,0.78,0.8);
  //leg->SetHeader("Poisson Distribution");
  legREvt->AddEntry(REvt1_0,"AD1" ,"lep");
  legREvt->AddEntry(REvt2_0,"AD2" ,"lep");
  legREvt->AddEntry(REvt3_0,"AD3" ,"lep");
  legREvt->SetTextSize(0.04);
  legREvt->Draw();
  REvtC->Print("REvt.ps");


  /// N IBD
  TCanvas NIBDC("NIBDC","NIBDC");
  TMultiGraph *mgNIBD = new TMultiGraph();

  NIBD1_0->SetMarkerStyle(20);
  NIBD1_0->SetMarkerColor(2);
  mgNIBD->Add(NIBD1_0);
  NIBD2_0->SetMarkerStyle(20);
  NIBD2_0->SetMarkerColor(3);
  mgNIBD->Add(NIBD2_0);
  NIBD3_0->SetMarkerStyle(20);
  NIBD3_0->SetMarkerColor(4);
  mgNIBD->Add(NIBD3_0);

  NIBD4_0->SetMarkerStyle(4);
  NIBD4_0->SetMarkerColor(2);
  mgNIBD->Add(NIBD4_0);
  NIBD5_0->SetMarkerStyle(4);
  NIBD5_0->SetMarkerColor(3);
  mgNIBD->Add(NIBD5_0);
  NIBD6_0->SetMarkerStyle(4);
  NIBD6_0->SetMarkerColor(4);
  mgNIBD->Add(NIBD6_0);
  mgNIBD->Draw("A");

  mgNIBD->GetXaxis();
  mgNIBD->GetXaxis()->SetTitle("Date");
  mgNIBD->GetXaxis()->SetTimeDisplay(1);
  mgNIBD->GetXaxis()->SetTimeFormat("%d/%m/%y%F1970-01-01 00:00:00");

  mgNIBD->GetYaxis()->SetTitle("Number of IBD in each day");

  mgNIBD->Draw("ALP");

  TLegend*  legNIBD = new TLegend(0.6,0.5,0.78,0.8);
  //leg->SetHeader("Poisson Distribution");
  legNIBD->AddEntry(NIBD1_0,"AD1" ,"lep");
  legNIBD->AddEntry(NIBD2_0,"AD2" ,"lep");
  legNIBD->AddEntry(NIBD3_0,"AD3" ,"lep");
  legNIBD->AddEntry(NIBD4_0,"AD4" ,"lep");
  legNIBD->AddEntry(NIBD5_0,"AD5" ,"lep");
  legNIBD->AddEntry(NIBD6_0,"AD6" ,"lep");
  legNIBD->SetTextSize(0.04);
  legNIBD->Draw();
  NIBDC->Print("NIBD.ps");

  /// N IBD-far
  TCanvas NIBDFarC("NIBDFarC","NIBDFarC");
  TMultiGraph *mgNIBDFar = new TMultiGraph();

  NIBD4_0->SetMarkerStyle(20);
  NIBD4_0->SetMarkerColor(2);
  mgNIBDFar->Add(NIBD4_0);
  NIBD5_0->SetMarkerStyle(20);
  NIBD5_0->SetMarkerColor(3);
  mgNIBDFar->Add(NIBD5_0);
  NIBD6_0->SetMarkerStyle(20);
  NIBD6_0->SetMarkerColor(4);
  mgNIBDFar->Add(NIBD6_0);
  mgNIBDFar->Draw("A");

  mgNIBDFar->GetXaxis();
  mgNIBDFar->GetXaxis()->SetTitle("Date");
  mgNIBDFar->GetXaxis()->SetTimeDisplay(1);
  mgNIBDFar->GetXaxis()->SetTimeFormat("%d/%m/%y%F1970-01-01 00:00:00");

  mgNIBDFar->GetYaxis()->SetTitle("Number of IBD in each day");

  mgNIBDFar->Draw("ALP");

  TLegend*  legNIBDFar = new TLegend(0.6,0.5,0.78,0.8);
  //leg->SetHeader("Poisson Distribution");
  legNIBDFar->AddEntry(NIBD4_0,"AD4" ,"lep");
  legNIBDFar->AddEntry(NIBD5_0,"AD5" ,"lep");
  legNIBDFar->AddEntry(NIBD6_0,"AD6" ,"lep");
  legNIBDFar->SetTextSize(0.04);
  legNIBDFar->Draw();
  NIBDFarC->Print("NIBDFar.ps");


  /// R IBD
  TCanvas RIBDC("RIBDC","RIBDC");
  TMultiGraph *mgRIBD = new TMultiGraph();

  RIBD1_0->SetMarkerStyle(20);
  RIBD1_0->SetMarkerColor(2);
  mgRIBD->Add(RIBD1_0);
  RIBD2_0->SetMarkerStyle(20);
  RIBD2_0->SetMarkerColor(3);
  mgRIBD->Add(RIBD2_0);
  RIBD3_0->SetMarkerStyle(20);
  RIBD3_0->SetMarkerColor(4);
  mgRIBD->Add(RIBD3_0);

  RIBD4_0->SetMarkerStyle(4);
  RIBD4_0->SetMarkerColor(2);
  mgRIBD->Add(RIBD4_0);
  RIBD5_0->SetMarkerStyle(4);
  RIBD5_0->SetMarkerColor(3);
  mgRIBD->Add(RIBD5_0);
  RIBD6_0->SetMarkerStyle(4);
  RIBD6_0->SetMarkerColor(4);
  mgRIBD->Add(RIBD6_0);
  mgRIBD->Draw("A");

  mgRIBD->GetXaxis();
  mgRIBD->GetXaxis()->SetTitle("Date");
  mgRIBD->GetXaxis()->SetTimeDisplay(1);
  mgRIBD->GetXaxis()->SetTimeFormat("%d/%m/%y%F1970-01-01 00:00:00");

  mgRIBD->GetYaxis()->SetTitle("Rate of IBD [day^{-1}]");

  mgRIBD->Draw("ALP");

  TLegend*  legRIBD = new TLegend(0.6,0.5,0.78,0.8);
  //leg->SetHeader("Poisson Distribution"); 
  legRIBD->AddEntry(RIBD1_0,"AD1" ,"lep");
  legRIBD->AddEntry(RIBD2_0,"AD2" ,"lep");
  legRIBD->AddEntry(RIBD3_0,"AD3" ,"lep");
  legRIBD->AddEntry(RIBD4_0,"AD4" ,"lep");
  legRIBD->AddEntry(RIBD5_0,"AD5" ,"lep");
  legRIBD->AddEntry(RIBD6_0,"AD6" ,"lep");
  legRIBD->SetTextSize(0.04);
  legRIBD->Draw();
  RIBDC->Print("RIBD.ps");

}
