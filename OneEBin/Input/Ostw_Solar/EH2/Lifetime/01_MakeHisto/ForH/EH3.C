/*
  root[0] .L EH3.C+
  root[1] EH3()
*/

#include "TChain.h"
#include "TFile.h"
#include "TH1F.h"
void EH3()
{
TChain Event("Event");

Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021223.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021232.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021241.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021355.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021364.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021373.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021375.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021396.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021502.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021514.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021525.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021526.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021527.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021536.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021546.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021644.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021662.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021669.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021670.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021680.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021691.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021807.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021818.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021821.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021825.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021836.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021837.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021838.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021842.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021846.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021852.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021857.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021867.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021963.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021979.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021988.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0021995.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022003.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022004.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022005.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022014.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022115.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022124.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022125.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022134.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022135.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022148.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022152.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022254.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022263.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022272.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022273.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022274.TWin.root");
Event.Add("~/data/TWin/06_P12b_AdScaled_OWSNhit15_Tc1000us/H/EH3/0022284.TWin.root");

 { // All
 TFile f1("EH3_all.root","RECREATE");
 TH1F h1("h","h",500,0,1000e-6);
 Event.Project("h","TrigSec[1]-TrigSec[0]+(TrigNano[1]-TrigNano[0])*1e-9",
	       "(X[0]*X[0]+Y[0]*Y[0]>2800e3) && Fold==2 && E[0]<12 && E[0]>3.5 && E[1]>1.8 && E[1]<2.8" );
 h1.Write();
 f1.Close();
 }



 {
 TFile f1("EH3_AD1.root","RECREATE");
 TH1F h1("h","h",500,0,1000e-6);
 Event.Project("h","TrigSec[1]-TrigSec[0]+(TrigNano[1]-TrigNano[0])*1e-9",
	       "(X[0]*X[0]+Y[0]*Y[0]>2800e3) && Fold==2 && E[0]<12 && E[0]>3.5 && E[1]>1.8 && E[1]<2.8 && Det==1" );
 h1.Write();
 f1.Close();
 }


 {
 TFile f2("EH3_AD2.root","RECREATE");
 TH1F h2("h","h",500,0,1000e-6);
 Event.Project("h","TrigSec[1]-TrigSec[0]+(TrigNano[1]-TrigNano[0])*1e-9",
	       "(X[0]*X[0]+Y[0]*Y[0]>2800e3) && Fold==2 && E[0]<12 && E[0]>3.5 && E[1]>1.8 && E[1]<2.8 && Det==2" );

 h2.Write();
 f2.Close();
 }

 {
 TFile f3("EH3_AD3.root","RECREATE");
 TH1F h3("h","h",500,0,1000e-6);
 Event.Project("h","TrigSec[1]-TrigSec[0]+(TrigNano[1]-TrigNano[0])*1e-9",
	       "(X[0]*X[0]+Y[0]*Y[0]>2800e3) && Fold==2 && E[0]<12 && E[0]>3.5 && E[1]>1.8 && E[1]<2.8 && Det==3" );
 h3.Write();
 f3.Close();
 }


}

