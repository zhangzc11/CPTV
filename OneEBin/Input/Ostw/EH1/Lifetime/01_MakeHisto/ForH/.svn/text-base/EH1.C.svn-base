{

TChain Event("Event");

Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021221.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021228.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021235.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021344.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021349.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021358.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021367.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021374.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021505.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021508.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021520.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021530.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021540.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021651.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021653.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021660.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021678.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021690.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021804.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021810.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021829.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021850.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021861.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021868.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021872.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021960.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021974.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0021982.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022002.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022008.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022111.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022118.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022128.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022138.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022141.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022243.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022261.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022266.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH1/0022278.TWin.root");

   TFile* fEH1_AD1 = new TFile( "EH1_AD1.root", "recreate" );
   Event->Draw("TrigSec[1]-TrigSec[0]+(TrigNano[1]-TrigNano[0])*1e-9 >> h(500,0,1000e-6)",
	       "(X[0]*X[0]+Y[0]*Y[0]>2800e3) && Fold==2 && E[0]<12 && E[0]>3.5 && E[1]>1.8 && E[1]<2.8 && Det==1" );
   h->Write();
   fEH1_AD1->Close();


   TFile* fEH1_AD2 = new TFile( "EH1_AD2.root", "recreate" );
   Event->Draw("TrigSec[1]-TrigSec[0]+(TrigNano[1]-TrigNano[0])*1e-9 >> h(500,0,1000e-6)",
	       "(X[0]*X[0]+Y[0]*Y[0]>2800e3) && Fold==2 && E[0]<12 && E[0]>3.5 && E[1]>1.8 && E[1]<2.8 && Det==2" );
   h->Write();
   fEH1_AD2->Close();

}
