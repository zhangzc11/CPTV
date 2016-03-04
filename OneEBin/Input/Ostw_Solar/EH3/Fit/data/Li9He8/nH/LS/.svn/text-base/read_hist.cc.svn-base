void read_hist()
{
  ///
  file_canv_merged_nH_hist_Epp_EH1 
    = new TFile("canv_merged_nH_hist_Epp_EH1.root");

  ///
  canv_merged_nH_hist_Epp_EH1 
    = (TCanvas*)file_canv_merged_nH_hist_Epp_EH1->Get("canv_merged_nH_hist_Epp_EH1");

  ///
  merged_nH_hist_Epp_EH1 
    = (TH1F*)canv_merged_nH_hist_Epp_EH1->GetPrimitive("merged_nH_hist_Epp_EH1");

  ///
  canv_test = new TCanvas("canv_test","canv_test",800,600);

  merged_nH_hist_Epp_EH1->DrawNormalized();

}
