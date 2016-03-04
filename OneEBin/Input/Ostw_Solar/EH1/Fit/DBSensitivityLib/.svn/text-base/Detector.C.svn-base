#define Detector_C

#include "Detector.h"

ClassImp(Detector)

Detector::Detector(const char *name)
{
  SetName(name);
  
  fNCores=0;
  
  //from TDR
  fSigma_d = 0.0038;
  fSigma_f = 1.0;
  fSigma_n = 1.0;
  fSigma_s = 0.003;//near detector only
  
  fSsq2T13=0.0;
  fDMsq31=2.5e-3;
  
  fNtargetnuclei=1.5827e30;//this # targets per 20 ton detector matches rates /day/module from TDR
  
  fEfficiency = 0.78;//neutron detection efficiency from TDR
  
  fEnergyRes = 0.12;//positron energy resolution at 1 MeV from TDR
  
  fNbins=260;
  fEnuMax=13.;
  
  fSecinYear=3.156e7;

  fCores = new TList();
  
  gMixingMatrix = new MixingMatrix();
  
  fXSec=false;
  fSpec=false;
  fLi9=false;
  fFast=false;
  fAcc=false;
  
  //from TDR
  fS2B_Li9=3e-3;
  fS2B_Fast=1e-3;
  fS2B_Acc=2e-3;
  
  Int_t ibin;
  for(ibin=0;ibin<fNbins;ibin++)
  {
    Enu.push_back((ibin+0.5)*fEnuMax/fNbins);
  }
  
  TString hname;
  
  hname.Form("EnuSpectrum_%s",GetName());
  EnuSpectrum = new TH1D(hname,"Neutrino Energy Spectrum",fNbins,0.0,fEnuMax);
  hname.Form("PromptSpectrum_%s",GetName());
  PromptSpectrum = new TH1D(hname,"Prompt Energy Spectrum",fNbins,0.0,fEnuMax);
  
  hname.Form("Li9_%s",GetName());
  Li9Bkgd = new TH1D(hname,"Li9 Spectrum",fNbins,0.0,fEnuMax);
  
  hname.Form("FastNeutron_%s",GetName());
  FastNeutronBkgd = new TH1D(hname,"Fast Neutron Spectrum",fNbins,0.0,fEnuMax);
  
  hname.Form("Accidental_%s",GetName());
  AccidentalBkgd = new TH1D(hname,"Accidental Spectrum",fNbins,0.0,fEnuMax);
  
  hname.Form("Flux_%s",GetName());
  Flux = new TH1D(hname,"Flux",fNbins,0.0,fEnuMax);
  
  hname.Form("Temp_%s",GetName());
  TempHist = new TH1D(hname,"Temp",fNbins,0.0,fEnuMax);
  
  hname.Form("ERes_%s",GetName());
  Double_t binwidth = fEnuMax/fNbins;
  Double_t range = 5.0+binwidth/2.;
  Double_t neresbinsd = 10./binwidth + 1;
  Int_t neresbins = (Int_t)(neresbinsd);
  if(fabs(neresbinsd-neresbins)>=0.5)
  {
    neresbins++;
  }
  ERes = new TH1D(hname,"ERes",neresbins,-1.*range,range);
  
}
Detector::~Detector()
{
}
void Detector::AddCore(ReactorCore *Core, Double_t distance, Double_t time)
{
  
  fSpec=false;
  fLi9=false;
  fFast=false;
  fAcc=false;
  
  fCores->AddLast(Core);
  fCoreDistance.push_back(distance);
  fCoreTime.push_back(time*fSecinYear);//in seconds
  fNCores++;
  
  Int_t icore,ibin;
  Double_t y;
  Double_t dFlux_percore[fNCores],dFlux_total=0.0;
  for(icore=0;icore<fNCores;icore++)
  {
    dFlux_percore[icore]=0.0;
  }
  
  for(ibin=0;ibin<fNbins;ibin++)
  {
    for(icore=0;icore<fNCores;icore++)
    {
      ReactorCore *rtemp = (ReactorCore*)fCores->At(icore);
      y=fCoreTime.at(icore)*rtemp->dNdE_Expected->Eval(Enu.at(ibin))/(4.*TMath::Pi()*fCoreDistance.at(icore)*fCoreDistance.at(icore));
      
      dFlux_percore[icore]+=y;
      dFlux_total+=y;
    }
  }
  
  fCoreWeight.clear();
  for(icore=0;icore<fNCores;icore++)
  {
    fCoreWeight.push_back(dFlux_percore[icore]/dFlux_total);
  }
  
  BuildSpectrum(true);
  BuildLi9Spectrum();
  BuildFastNeutronSpectrum();
  BuildAccidentalSpectrum();
  
  return;
}
void Detector::BuilddFluxdE(bool oscillated,bool useexpected)
{
  Int_t icore,ibin;
  Double_t y,temp;
  
  gMixingMatrix->SetSin2_2Theta13(fSsq2T13);
  gMixingMatrix->SetDM2_21_31(gMixingMatrix->GetDeltaM2_21(),fDMsq31);
  //gMixingMatrix->SetDM2_31(fDMsq31);
  Double_t survivalProb=1.0;
  
  dFlux.clear();
  
  for(ibin=0;ibin<fNbins;ibin++)
  {
    temp=0.0;
    for(icore=0;icore<fNCores;icore++)
    {
      survivalProb=1.0;
      if(oscillated)
      {
        survivalProb = gMixingMatrix->SurvivalProb(Enu.at(ibin),fCoreDistance.at(icore));
      }
      ReactorCore *rtemp = (ReactorCore*)fCores->At(icore);
      if(useexpected)
      {
        y=fCoreTime.at(icore)*survivalProb*rtemp->dNdE_Expected->Eval(Enu.at(ibin))/(4.*TMath::Pi()*fCoreDistance.at(icore)*fCoreDistance.at(icore));
      }
      else
      {
        y=fCoreTime.at(icore)*survivalProb*rtemp->dNdE_Actual->Eval(Enu.at(ibin))/(4.*TMath::Pi()*fCoreDistance.at(icore)*fCoreDistance.at(icore));
      }
      temp+=y;
    }
    dFlux.push_back(temp);
  }
  
  return;
}
void Detector::BuildFlux(bool oscillated, bool useexpected)
{
  BuilddFluxdE(oscillated,useexpected);
  
  Int_t ibin;
  Double_t binwidth = fEnuMax/fNbins;
  
  for(ibin=0;ibin<fNbins;ibin++)
  {
    Flux->SetBinContent(ibin+1,dFlux.at(ibin)*binwidth);
  }
  Flux->GetXaxis()->SetTitle("Antineutrino energy (MeV)");
  Flux->GetYaxis()->SetTitle("Flux antineutrinos/m^{2}");
  
  return;
}
void Detector::BuildCrossSection()
{
  if(fXSec)
  {
    return;
  }
  
  if( gInverseBeta==NULL ) gInverseBeta = new InverseBetaCS();
  int ibin;
  XSec.clear();
  for(ibin=0;ibin<fNbins;ibin++)
  {
    XSec.push_back(gInverseBeta->SigmaTot(Enu.at(ibin))*1e-46);
  }
  
  fXSec=true;
  
  return;
}
void Detector::BuildERes(Double_t energy)
{
  ERes->Reset();
  
  Double_t sigma = fEnergyRes/sqrt(energy);
  
  Int_t ibin;
  Double_t deltaE,val;
  for(ibin=0;ibin<ERes->GetNbinsX();ibin++)
  {
    deltaE = ERes->GetBinCenter(ibin+1);
    val = TMath::Gaus(deltaE,0,sigma);
    ERes->Fill(deltaE,val);
  }
  ERes->Scale(1./ERes->Integral());
  
  return;
}
void Detector::BuildSpectrum(bool useexpected)
{
  BuilddFluxdE(true,useexpected);
  
  BuildCrossSection();
  
  EnuSpectrum->Reset();
  PromptSpectrum->Reset();
  
  Int_t ibin,jbin;
  Double_t binwidth = (Double_t)(fEnuMax/fNbins);
  Double_t shiftMeV = 0.8;//neglecting recoil energy of neutron, the prompt energy is 0.8 MeV less than the incident neutrino energy
  Double_t shiftd = (shiftMeV/binwidth);
  Int_t shift = (Int_t)shiftd;
  if(fabs(shiftd-shift)>=0.5)//round it correctly
  {
    shift++;
  }
  
  for(ibin=0;ibin<fNbins;ibin++)
  {
    EnuSpectrum->SetBinContent(ibin+1,dFlux.at(ibin)*XSec.at(ibin)*binwidth*fNtargetnuclei*fEfficiency);
  }
  
  TempHist->Reset();
  for(ibin=0;ibin<fNbins;ibin++)
  {
    if(ibin+1+shift<=fNbins)
    {
      TempHist->SetBinContent(ibin+1,EnuSpectrum->GetBinContent(ibin+1+shift));
    }
  }
  
  EnuSpectrum->GetXaxis()->SetTitle("Antineutrino energy (MeV)");
  EnuSpectrum->GetYaxis()->SetTitle("number of interactions");
  PromptSpectrum->GetXaxis()->SetTitle("prompt energy (MeV)");
  PromptSpectrum->GetYaxis()->SetTitle("number of interactions");
  
  if(fEnergyRes==0.0)
  {
    PromptSpectrum->Add(TempHist,1.0);
    return;
  }
  
  Double_t deltaE,E,Enew,frac;
  for(ibin=0;ibin<fNbins;ibin++)
  {
    E = TempHist->GetBinCenter(ibin+1);
    BuildERes(E);
    for(jbin=0;jbin<ERes->GetNbinsX();jbin++)
    {
      
      deltaE = ERes->GetBinCenter(jbin+1);
      Enew = E + deltaE;
      frac = ERes->GetBinContent(jbin+1);
      if(Enew>0.0 && Enew<fEnuMax)
      {
        if(frac<1e-10)
        {
          frac=0.0;
        }
        PromptSpectrum->Fill(Enew,frac*TempHist->GetBinContent(ibin+1));
      }
    }
  }
  
  return;
}
void Detector::BuildLi9Spectrum()
{
  if(fLi9)
  {
    return;
  }
  
  Li9Bkgd->Reset();
  
  TF1 *f_li9 = new TF1("f_li9","[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*exp(-0.5*((x-[4])/[5])**2) + [6]*exp(-0.5*((x-[7])/[8])**2)",-100,100);
  f_li9->SetParameter(0,-3.46940e-02);
  f_li9->SetParameter(1,2.61314e+00);
  f_li9->SetParameter(2,5.06524e+00);
  f_li9->SetParameter(3,1.71599e-01);
  f_li9->SetParameter(4,4.05220e+00);
  f_li9->SetParameter(5,2.17596e+00);
  f_li9->SetParameter(6,9.03400e-02);
  f_li9->SetParameter(7,7.25785e+00);
  f_li9->SetParameter(8,-1.69872e+00);
  
  Int_t ibin;
  Double_t e;
  for(ibin=0;ibin<fNbins;ibin++)
  {
    e=(ibin+0.5)*fEnuMax/fNbins;
    Li9Bkgd->SetBinContent(ibin+1,f_li9->Eval(e));
  }
  Double_t a=1./Li9Bkgd->Integral();
  Li9Bkgd->Scale(a);
  Li9Bkgd->GetXaxis()->SetTitle("Energy (MeV)");
  Li9Bkgd->GetYaxis()->SetTitle("arbitrary units");
  
  BuildSpectrum(true);
  Li9Bkgd->Scale(fS2B_Li9*PromptSpectrum->Integral());
  
  fLi9=true;
  
  return;
}
void Detector::BuildFastNeutronSpectrum()
{
  if(fFast)
  {
    return;
  }
  
  FastNeutronBkgd->Reset();
  
  Int_t ibin;
  for(ibin=0;ibin<fNbins;ibin++)
  {
    FastNeutronBkgd->SetBinContent(ibin+1,1.0/fNbins);
  }
  FastNeutronBkgd->GetXaxis()->SetTitle("Energy (MeV)");
  FastNeutronBkgd->GetYaxis()->SetTitle("arbitrary units");
  
  BuildSpectrum(true);
  FastNeutronBkgd->Scale(fS2B_Fast*PromptSpectrum->Integral());
  
  fFast=true;
  
  return;
}
void Detector::BuildAccidentalSpectrum()
{
  if(fAcc)
  {
    return;
  }
  
  AccidentalBkgd->Reset();
  
  Int_t ibin;
  Double_t e,y;
  for(ibin=0;ibin<fNbins;ibin++)
  {
    e=(ibin+0.5)*fEnuMax/fNbins;
    y=TMath::Exp(-1.*e);
    AccidentalBkgd->SetBinContent(ibin+1,y);
  }
  Double_t a=1./AccidentalBkgd->Integral();
  AccidentalBkgd->Scale(a);
  AccidentalBkgd->GetXaxis()->SetTitle("Energy (MeV)");
  AccidentalBkgd->GetYaxis()->SetTitle("arbitrary units");
  
  BuildSpectrum(true);
  AccidentalBkgd->Scale(fS2B_Acc*PromptSpectrum->Integral());
  
  fAcc=true;
  
  return;
}
void Detector::DrawdFluxdE(bool oscillated)
{
  BuilddFluxdE(oscillated,true);
  
  Int_t ibin;
  Double_t x[fNbins],y[fNbins];
  for(ibin=0;ibin<fNbins;ibin++)
  {
    x[ibin]=Enu.at(ibin);
    y[ibin]=dFlux.at(ibin);
  }
  
  TString hname;
  hname.Form("dFluxdE_%s",GetName());
  TGraph *dFluxdE = new TGraph(fNbins,x,y);
  dFluxdE->SetNameTitle(hname,"dFlux/dE");
  dFluxdE->GetXaxis()->SetTitle("Antineutrino energy (MeV)");
  dFluxdE->GetYaxis()->SetTitle("dFlux/dE antineutrinos/(MeV #times m^{2})");
  dFluxdE->SetMarkerStyle(20);
  
  dFluxdE->Draw("ap");
  
  return;
}
void Detector::DrawFlux(bool oscillated)
{
  BuildFlux(oscillated,true);
  
  Flux->Draw();
  
  return;
}
void Detector::DrawCrossSection()
{
  BuildCrossSection();
  
  Int_t ibin;
  Double_t x[fNbins],y[fNbins];
  for(ibin=0;ibin<fNbins;ibin++)
  {
    x[ibin]=Enu.at(ibin);
    y[ibin]=XSec.at(ibin)*1e46;
  }
  
  TString hname;
  hname.Form("CrossSection_%s",GetName());
  TGraph *CrossSection = new TGraph(fNbins,x,y);
  CrossSection->SetNameTitle(hname,"Inverse Beta Decay Cross Section");
  CrossSection->GetXaxis()->SetTitle("Antineutrino energy (MeV)");
  CrossSection->GetYaxis()->SetTitle("Inverse Beta Decay Cross Section (10^{-42} cm^{2})");
  CrossSection->SetMarkerStyle(20);
  
  CrossSection->Draw("ap");
  
  return;
}
void Detector::SetSigma_d(Double_t sigma)
{
  fSigma_d = sigma;
  return;
}
void Detector::SetSigma_f(Double_t sigma)
{
  fSigma_f = sigma;
  return;
}
void Detector::SetSigma_n(Double_t sigma)
{
  fSigma_n = sigma;
  return;
}
void Detector::SetSigma_s(Double_t sigma)
{
  fSigma_s = sigma;
  return;
}
void Detector::SetSinSq2Theta13(Double_t sinsq2theta13)
{
  fSsq2T13 = sinsq2theta13;
  return;
}
void Detector::SetDeltaMSq31(Double_t deltamsq31)
{
  fDMsq31 = deltamsq31;
  return;
}
void Detector::SetNtargetnuclei(Double_t n)
{
  fNtargetnuclei=n;
  
  fSpec=false;
  fLi9=false;
  fFast=false;
  fAcc=false;
  
  BuildSpectrum(true);
  BuildLi9Spectrum();
  BuildFastNeutronSpectrum();
  BuildAccidentalSpectrum();
  
  return;
}
void Detector::SetEfficiency(Double_t eff)
{
  fEfficiency = eff;
  
  fSpec=false;
  fLi9=false;
  fFast=false;
  fAcc=false;
  
  BuildSpectrum(true);
  BuildLi9Spectrum();
  BuildFastNeutronSpectrum();
  BuildAccidentalSpectrum();
  
  return;
}
void Detector::SetEnergyRes(Double_t eres)
{
  fEnergyRes = eres;
  
  fSpec=false;
  fLi9=false;
  fFast=false;
  fAcc=false;
  
  BuildSpectrum(true);
  BuildLi9Spectrum();
  BuildFastNeutronSpectrum();
  BuildAccidentalSpectrum();
  
  return;
}
void Detector::SetSigtoBkgd_Li9(Double_t s2b)
{
  fS2B_Li9=s2b;
  
  fSpec=false;
  fLi9=false;
  fFast=false;
  fAcc=false;
  
  BuildSpectrum(true);
  BuildLi9Spectrum();
  BuildFastNeutronSpectrum();
  BuildAccidentalSpectrum();
  
  return;
}
void Detector::SetSigtoBkgd_Fast(Double_t s2b)
{
  fS2B_Fast=s2b;
  
  fSpec=false;
  fLi9=false;
  fFast=false;
  fAcc=false;
  
  BuildSpectrum(true);
  BuildLi9Spectrum();
  BuildFastNeutronSpectrum();
  BuildAccidentalSpectrum();
  
  return;
}
void Detector::SetSigtoBkgd_Acc(Double_t s2b)
{
  fS2B_Acc=s2b;
  
  fSpec=false;
  fLi9=false;
  fFast=false;
  fAcc=false;
  
  BuildSpectrum(true);
  BuildLi9Spectrum();
  BuildFastNeutronSpectrum();
  BuildAccidentalSpectrum();
  
  return;
}
Int_t Detector::GetNCores()
{
  return fNCores;
}
Double_t Detector::GetCoreWeight(Int_t core)
{
  return fCoreWeight.at(core);
}
Double_t Detector::GetCoreDistance(Int_t core)
{
  return fCoreDistance.at(core);
}
Double_t Detector::GetCoreTime(Int_t core)
{
  return fCoreTime.at(core)/fSecinYear;//return value in years
}
Double_t Detector::GetSigma_d()
{
  return fSigma_d;
}
Double_t Detector::GetSigma_f()
{
  return fSigma_f;
}
Double_t Detector::GetSigma_n()
{
  return fSigma_n;
}
Double_t Detector::GetSigma_s()
{
  return fSigma_s;
}
Double_t Detector::GetSinSq2Theta13()
{
  return fSsq2T13;
}
Double_t Detector::GetDeltaMSq31()
{
  return fDMsq31;
}
Double_t Detector::GetNtargetnuclei()
{
  return fNtargetnuclei;
}
Double_t Detector::GetEfficiency()
{
  return fEfficiency;
}
Double_t Detector::GetEnergyRes()
{
  return fEnergyRes;
}
Double_t Detector::GetSigtoBkgd_Li9()
{
  return fS2B_Li9;
}
Double_t Detector::GetSigtoBkgd_Fast()
{
  return fS2B_Fast;
}
Double_t Detector::GetSigtoBkgd_Acc()
{
  return fS2B_Acc;
}
Int_t Detector::GetNBins()
{
  return fNbins;
}
Double_t Detector::GetBinWidth()
{
  return fEnuMax/fNbins;
}
