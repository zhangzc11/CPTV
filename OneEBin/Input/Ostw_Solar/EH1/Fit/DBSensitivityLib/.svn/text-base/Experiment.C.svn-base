#define Experiment_C

#include "Experiment.h"

ClassImp(Experiment)

extern void FittingFCN(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  Int_t idet,icore,ibin;
  double fcn=0.0;
  double reactorterm=0.0;
  double num=0.0,den=0.0;
  
  Experiment *a = (Experiment*)gMinuit->GetObjectFit();
  
  for(idet=0;idet<a->GetNDetectors();idet++)
  {
    Detector *dtemp = (Detector*)a->fDetectors->At(idet);
    reactorterm=0.0;
    for(icore=0;icore<dtemp->GetNCores();icore++)
    {
      reactorterm+=dtemp->GetCoreWeight(icore)*par[a->alpha_r(icore)];
    }
    for(ibin=0;ibin<a->GetNBins();ibin++)
    {
      num=0.0;
      den=0.0;
      if(a->BinInFit(ibin))
      {
        num+=a->Measured[idet].at(ibin);
        num-=a->True[idet].at(ibin)*(1 + par[a->alpha_c()] + reactorterm + par[a->beta(ibin)] + par[a->epsilon_D()] + par[a->epsilon_d(idet)]);
        num-=par[a->eta_f(idet)]*a->FastNeutron[idet].at(ibin);
        num-=par[a->eta_n(idet)]*a->Accidental[idet].at(ibin);
        num-=par[a->eta_s(idet)]*a->Li9[idet].at(ibin);
        num=num*num;
        den+=a->True[idet].at(ibin);
        den+=a->GetSigma_b2b()*a->GetSigma_b2b()*a->True[idet].at(ibin)*a->True[idet].at(ibin);
        fcn+=(num/den);
      }
    }
    fcn+=par[a->epsilon_d(idet)]*par[a->epsilon_d(idet)]/(dtemp->GetSigma_d()*dtemp->GetSigma_d());
    fcn+=par[a->eta_f(idet)]*par[a->eta_f(idet)]/(dtemp->GetSigma_f()*dtemp->GetSigma_f());
    fcn+=par[a->eta_n(idet)]*par[a->eta_n(idet)]/(dtemp->GetSigma_n()*dtemp->GetSigma_n());
    fcn+=par[a->eta_s(idet)]*par[a->eta_s(idet)]/(dtemp->GetSigma_s()*dtemp->GetSigma_s());
  }
  
  fcn+=par[a->alpha_c()]*par[a->alpha_c()]/(a->GetSigma_c()*a->GetSigma_c());
  
  Detector *dtemp = (Detector*)a->fDetectors->At(0);
  for(icore=0;icore<dtemp->GetNCores();icore++)
  {
    ReactorCore *rtemp = (ReactorCore*)dtemp->fCores->At(icore);
    fcn+=par[a->alpha_r(icore)]*par[a->alpha_r(icore)]/(rtemp->GetSigma_r()*rtemp->GetSigma_r());
  }
  
  for(ibin=0;ibin<a->GetNBins();ibin++)
  {
    if(a->BinInFit(ibin))
    {
      fcn+=par[a->beta(ibin)]*par[a->beta(ibin)]/(a->GetSigma_shape()*a->GetSigma_shape());
    }
  }
  
  fcn+=par[a->epsilon_D()]*par[a->epsilon_D()]/(a->GetSigma_D()*a->GetSigma_D());
  
  f=fcn;
}
Experiment::Experiment()
{
  fNDetectors=0;
  fDetectors = new TList();
  
  //from TDR
  SetSigma_c(0.02);
  SetSigma_shape(0.02);
  SetSigma_D(0.02);
  SetSigma_b2b(0.003);
  
  SetSinSq2Theta13(0.0);
  SetDeltaMSq31(2.5e-3);
  
  SetTrueSinSq2Theta13(0.0);
  SetTrueDeltaMSq31(2.5e-3);
  
  fSetup=false;
  
  fPrintFit = false;
 
}
Experiment::~Experiment()
{
}
void Experiment::SetNPar()
{
  int icore,idet,ibin;
  int inc=0;
  
  fNPar=0;
  fParNames.clear();
  alpha_r_parno.clear();
  beta_parno.clear();
  epsilon_d_parno.clear();
  eta_f_parno.clear();
  eta_n_parno.clear();
  eta_s_parno.clear();
  
  alpha_c_parno = fNPar;
  fParNames.push_back("alpha_c");
  fNPar++;
  
  inc=0;
  if(fNDetectors>0)
  {
    Detector *dtemp = (Detector*)fDetectors->At(0);
    for(icore=0;icore<dtemp->GetNCores();icore++)
    {
      alpha_r_parno.push_back(fNPar);
      fNPar++;
      stringstream number;
      number<<inc;
      fParNames.push_back("alpha_r_"+number.str());
      inc++;
    }
  }
  
  inc=0;
  for(ibin=0;ibin<fNBins;ibin++)
  {
    beta_parno.push_back(fNPar);
    fNPar++;
    stringstream number;
    number<<inc;
    fParNames.push_back("beta_"+number.str());
    inc++;
  }
  
  epsilon_D_parno = fNPar;
  fParNames.push_back("epsilon_D");
  fNPar++;
  
  inc=0;
  for(idet=0;idet<fNDetectors;idet++)
  {
    epsilon_d_parno.push_back(fNPar);
    fNPar++;
    stringstream number;
    number<<inc;
    fParNames.push_back("epsilon_d_"+number.str());
    inc++;
  }
  
  inc=0;
  for(idet=0;idet<fNDetectors;idet++)
  {
    eta_f_parno.push_back(fNPar);
    fNPar++;
    stringstream number;
    number<<inc;
    fParNames.push_back("eta_f_"+number.str());
    inc++;
  }
  
  inc=0;
  for(idet=0;idet<fNDetectors;idet++)
  {
    eta_n_parno.push_back(fNPar);
    fNPar++;
    stringstream number;
    number<<inc;
    fParNames.push_back("eta_n_"+number.str());
    inc++;
  }
  
  inc=0;
  for(idet=0;idet<fNDetectors;idet++)
  {
    eta_s_parno.push_back(fNPar);
    fNPar++;
    stringstream number;
    number<<inc;
    fParNames.push_back("eta_s_"+number.str());
    inc++;
  }
  
  return;
}
void Experiment::AddDetector(Detector *Det)
{
  fSetup=false;
  fDetectors->AddLast(Det);
  fNDetectors++;
  SetNBins();
  SetNPar();
  Measured.push_back( vector<Double_t>() );
  True.push_back( vector<Double_t>() );
  Li9.push_back( vector<Double_t>() );
  FastNeutron.push_back( vector<Double_t>() );
  Accidental.push_back( vector<Double_t>() );
  
  return;
}
void Experiment::SetupTrueSpectrum()
{
  Int_t idet,ibin,jbin;
  Double_t temp=0.0;
  for(idet=0;idet<fNDetectors;idet++)
  {
    True[idet].clear();
  }
  for(idet=0;idet<fNDetectors;idet++)
  {
    Detector *dtemp = (Detector*)fDetectors->At(idet);
    dtemp->SetSinSq2Theta13(ffSsq2T13);
    dtemp->SetDeltaMSq31(ffDMsq31);
    dtemp->BuildSpectrum(true);
    for(ibin=0;ibin<fNBins;ibin++)
    {
      temp=0.0;
      for(jbin=0;jbin<dtemp->GetNBins();jbin++)
      {
        if(dtemp->PromptSpectrum->GetBinCenter(jbin+1)>fEdges.at(ibin) && dtemp->PromptSpectrum->GetBinCenter(jbin+1)<fEdges.at(ibin+1))
        {
          temp+=dtemp->PromptSpectrum->GetBinContent(jbin+1);
        }
      }
      True[idet].push_back(temp);
    }
  }
  
  return;
}
void Experiment::SetupSpectrums()
{
  if(fSetup)
  {
    return;//only need to do this once
  }
  
  Int_t idet,ibin,jbin;
  Double_t temp=0.0;
  fBin.clear();
  for(ibin=0;ibin<fNBins;ibin++)
  {
    fBin.push_back(true);
  }
  for(idet=0;idet<fNDetectors;idet++)
  {
    Measured[idet].clear();
    Li9[idet].clear();
    FastNeutron[idet].clear();
    Accidental[idet].clear();
  }
  
  for(idet=0;idet<fNDetectors;idet++)
  {
    Detector *dtemp = (Detector*)fDetectors->At(idet);
    dtemp->SetSinSq2Theta13(fTrueSsq2T13);
    dtemp->SetDeltaMSq31(fTrueDMsq31);
    dtemp->BuildSpectrum(false);
    for(ibin=0;ibin<fNBins;ibin++)
    {
      temp=0.0;
      for(jbin=0;jbin<dtemp->GetNBins();jbin++)
      {
        if(dtemp->PromptSpectrum->GetBinCenter(jbin+1)>fEdges.at(ibin) && dtemp->PromptSpectrum->GetBinCenter(jbin+1)<fEdges.at(ibin+1))
        {
          temp+=dtemp->PromptSpectrum->GetBinContent(jbin+1);
        }
      }
      Measured[idet].push_back(temp);
    }
    
    for(ibin=0;ibin<fNBins;ibin++)
    {
      temp=0.0;
      for(jbin=0;jbin<dtemp->GetNBins();jbin++)
      {
        if(dtemp->Li9Bkgd->GetBinCenter(jbin+1)>fEdges.at(ibin) && dtemp->Li9Bkgd->GetBinCenter(jbin+1)<fEdges.at(ibin+1))
        {
          temp+=dtemp->Li9Bkgd->GetBinContent(jbin+1);
        }
      }
      Li9[idet].push_back(temp);
    }
    
    for(ibin=0;ibin<fNBins;ibin++)
    {
      temp=0.0;
      for(jbin=0;jbin<dtemp->GetNBins();jbin++)
      {
        if(dtemp->FastNeutronBkgd->GetBinCenter(jbin+1)>fEdges.at(ibin) && dtemp->FastNeutronBkgd->GetBinCenter(jbin+1)<fEdges.at(ibin+1))
        {
          temp+=dtemp->FastNeutronBkgd->GetBinContent(jbin+1);
        }
      }
      FastNeutron[idet].push_back(temp);
    }
    
    for(ibin=0;ibin<fNBins;ibin++)
    {
      temp=0.0;
      for(jbin=0;jbin<dtemp->GetNBins();jbin++)
      {
        if(dtemp->AccidentalBkgd->GetBinCenter(jbin+1)>fEdges.at(ibin) && dtemp->AccidentalBkgd->GetBinCenter(jbin+1)<fEdges.at(ibin+1))
        {
          temp+=dtemp->AccidentalBkgd->GetBinContent(jbin+1);
        }
      }
      Accidental[idet].push_back(temp);
    }
    
    for(ibin=0;ibin<fNBins;ibin++)
    {
      if(Measured[idet].at(ibin)<1)
      {
        fBin.at(ibin)=false;
      }
    }
  }
  
  SetNPar();
  
  fSetup=true;
  
  return;
}
void Experiment::DrawSpectrums(Bool_t save)
{
  SetupSpectrums();
  SetupTrueSpectrum();
  
  Int_t ibin;
  const Int_t nedges = fEdges.size();
  Double_t xbins[nedges];
  for(ibin=0;ibin<nedges;ibin++)
  {
    xbins[ibin] = fEdges.at(ibin);
  }
  
  const Int_t ndet = fNDetectors;
  TH1D *M[ndet], *T[ndet], *L[ndet], *F[ndet], *A[ndet];
  TCanvas *cM[ndet],*cT[ndet],*cL[ndet],*cF[ndet],*cA[ndet];
  Int_t idet;
  TString name;
  for(idet=0;idet<ndet;idet++)
  {
    Detector *dtemp = (Detector*)fDetectors->At(idet);
    name.Form("M_%s",dtemp->GetName());
    M[idet] = new TH1D(name,"",fNBins,xbins);
    name.Form("T_%s",dtemp->GetName());
    T[idet] = new TH1D(name,"",fNBins,xbins);
    name.Form("L_%s",dtemp->GetName());
    L[idet] = new TH1D(name,"",fNBins,xbins);
    name.Form("F_%s",dtemp->GetName());
    F[idet] = new TH1D(name,"",fNBins,xbins);
    name.Form("A_%s",dtemp->GetName());
    A[idet] = new TH1D(name,"",fNBins,xbins);
    for(ibin=0;ibin<fNBins;ibin++)
    {
      M[idet]->SetBinContent(ibin+1,Measured[idet].at(ibin));
      T[idet]->SetBinContent(ibin+1,True[idet].at(ibin));
      L[idet]->SetBinContent(ibin+1,Li9[idet].at(ibin));
      F[idet]->SetBinContent(ibin+1,FastNeutron[idet].at(ibin));
      A[idet]->SetBinContent(ibin+1,Accidental[idet].at(ibin));
    }
    cM[idet] = new TCanvas();
    M[idet]->Draw();
    cT[idet] = new TCanvas();
    T[idet]->Draw();
    cL[idet] = new TCanvas();
    L[idet]->Draw();
    cF[idet] = new TCanvas();
    F[idet]->Draw();
    cA[idet] = new TCanvas();
    A[idet]->Draw();
  }
  
  if(save)
  {
    Detector *dtemp = (Detector*)fDetectors->At(0);
    name.Form("spectrums_%.3f_%.2f_%.0f_%ibins.root",ffSsq2T13,ffDMsq31*1e3,dtemp->GetEnergyRes()*100.,fNBins);
    TFile *f = new TFile(name,"RECREATE");
    for(idet=0;idet<ndet;idet++)
    {
      M[idet]->Write();
      T[idet]->Write();
    }
    f->Write();
    f->Close();
  }
  
  return;
}
Double_t Experiment::Minimize()
{
  SetupSpectrums();
  SetupTrueSpectrum();
  
  TMinuit *gMinuit = new TMinuit(fNPar);
  gMinuit->SetFCN(FittingFCN);
  //gMinuit->SetErrorDef(1.0);
  gMinuit->SetObjectFit(this);
  gMinuit->SetPrintLevel(-1);
  
  Double_t arglist[10];
  Int_t ierflg=0;
  
  Int_t ipar;
  for(ipar=0;ipar<fNPar;ipar++)
  {
    gMinuit->mnparm(ipar,fParNames[ipar],0.0,1e-7,0.0,0.0,ierflg);//param #, param name, start, step, low limit, up limit, error flag
  }
  
  Int_t ibin;
  for(ibin=0;ibin<fNBins;ibin++)
  {
    if(!fBin.at(ibin))
    {
      gMinuit->FixParameter(beta_parno[ibin]);
    }
  }
  
  arglist[0] = 2000;
  arglist[1] = 1.;
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
  
  arglist[0] = 2000;
  arglist[1] = 1.;  
  gMinuit->mnexcm("HESSE",arglist,1,ierflg);
  
  Double_t fmin,fedm,errdef;
  Int_t npari,nparx,istat;
  gMinuit->mnstat(fmin,fedm,errdef,npari,nparx,istat);
  if(istat!=3)
  {
    cout<<"Covariance matrix is not accurate!"<<endl;
  }
  
  Double_t finalpar[fNPar],finalerr;
  for(ipar=0;ipar<fNPar;ipar++)
  {
    gMinuit->GetParameter(ipar,finalpar[ipar],finalerr);
  }
  Double_t *grad=NULL;
  Double_t fcnval=0.0;
  gMinuit->Eval(gMinuit->GetNumFreePars(),grad,fcnval,finalpar,ierflg);
  
  if(fPrintFit)
  {
    for(ipar=0;ipar<fNPar;ipar++)
    {
      cout<<fParNames.at(ipar)<<" = "<<finalpar[ipar]<<endl;
    }
  }
  
  delete gMinuit;
  
  return fcnval;
}
void Experiment::MakeSensitivityPlot(Double_t guess,char *filename)
{
  Int_t im;
  Double_t dm=2.5e-5;//deltam2 steps
  Double_t mend=5e-3;//deltam2 ending value
  Double_t mstart = 0.5e-3;//deltam2 starting value
  const Int_t msteps=(Int_t)((mend-mstart)/dm);
  cout<<msteps<<" steps in Delta m^2 from "<<mstart<<" to "<<mend<<endl;
  Double_t m,s,g;
  Double_t ssens[msteps],msens[msteps];
  Int_t npts=0;
  for(im=0;im<msteps;im++)
  {
    if(im==0)
    {
      g = guess;
    }
    else
    {
      g=ssens[im-1];
    }
    
    m = 5e-3 - im*dm;
    s=GetSensitivityAt(m,g);
    if(s==-1)
    {
      if(im==0)
      {
        return;
      }
      
      if(ssens[npts-1]>0.9)//last point getting close to physical limit, you can quit here
      {
        break;
      }
      
      continue;
    }
    
    ssens[npts]=s;
    msens[npts]=m;
    npts++;
  }
  
  TGraph *sens = new TGraph(npts,ssens,msens);
  int n = sens->GetN();
  int i;
  double x,y;
  for(i=0;i<n;i++)
  {
    sens->GetPoint(i,x,y);
    y=y*1e3;
    sens->SetPoint(i,x,y);
  }
  TCanvas *csens = new TCanvas("csens","csens",600,600);
  sens->SetName("sens");
  sens->SetTitle("");
  sens->SetLineWidth(4);
  sens->SetMinimum(0.5);
  sens->SetMaximum(5);
  sens->GetXaxis()->SetLimits(3e-3,0.5);
  sens->GetXaxis()->SetTitle("sin^{2}(2#theta_{13})");
  sens->GetYaxis()->SetTitle("#Delta m^{2}_{31} (#times 10^{-3} eV^{2})");
  sens->GetYaxis()->SetTitleOffset(1.3);
  csens->SetLogx();
  csens->SetGridx();
  csens->SetGridy();
  sens->SetMarkerStyle(20);
  sens->Draw("al");
  TString name;
  name.Form("%s.eps",filename);
  csens->SaveAs(name);
  
  name.Form("%s.root",filename);
  TFile *f = new TFile(name,"RECREATE");
  sens->Write();
  f->Write();
  f->Close();
  
  return;
}
Double_t Experiment::GetSensitivityAt(Double_t deltamsq31,Double_t guess)
{
  SetDeltaMSq31(deltamsq31);
  
  SetSinSq2Theta13(0.0);
  Double_t chi2_nom = Minimize();
  Double_t contourlvl = 2.71 + chi2_nom;
  
  Int_t is;
  Double_t s=0.0;
  Double_t ds = 0.001;
  Double_t chi2=0.0;
  Double_t sbest=0.1,chi2best=50.;
  Double_t sprevbest=10.0;
  Bool_t ok=false;
  
  ok=false;
  
  for(is=-10;is<11;is++)
  {
    s = guess + is*ds;
    if(s>=0 && s<1)
    {
      SetSinSq2Theta13(s);
      chi2 = Minimize();
      if(fabs(chi2-contourlvl)<fabs(chi2best-contourlvl))
      {
        chi2best = chi2;
        sbest = s;
        ok=true;
      }
    }
  }
  if(!ok)
  {
    cout<<"did not find contour, try another guess for sin^2(2theta_13)"<<endl;
    cout<<"best chi2 = "<<chi2best<<", contour = "<<contourlvl<<endl;
    
    return -1.;
  }
  
  again:

      ds = 0.0001;
  guess = sbest;
  for(is=-10;is<11;is++)
  {
    s = guess + is*ds;
    if(s>=0 && s<1)
    {
      SetSinSq2Theta13(s);
      chi2 = Minimize();
      if(fabs(chi2-contourlvl)<fabs(chi2best-contourlvl))
      {
        chi2best = chi2;
        sbest = s;
      }
    }
  }
  
  ds = 0.00001;
  guess = sbest;
  for(is=-10;is<11;is++)
  {
    s = guess + is*ds;
    if(s>=0 && s<1)
    {
      SetSinSq2Theta13(s);
      chi2 = Minimize();
      if(fabs(chi2-contourlvl)<fabs(chi2best-contourlvl))
      {
        chi2best = chi2;
        sbest = s;
      }
    }
  }
  
  ds = 0.000001;
  guess = sbest;
  for(is=-10;is<11;is++)
  {
    s = guess + is*ds;
    if(s>=0 && s<1)
    {
      SetSinSq2Theta13(s);
      chi2 = Minimize();
      if(fabs(chi2-contourlvl)<fabs(chi2best-contourlvl))
      {
        chi2best = chi2;
        sbest = s;
      }
    }
  }
  
  if(fabs(chi2best - contourlvl)>0.01)
  {
    if(sprevbest==sbest)
    {
      cout<<"no improvement, best s = "<<sbest<<" at m = "<<deltamsq31<<", chi2 = "<<chi2best<<endl;
      return -1;
    }
    ds = 0.001;
    guess = sbest;
    sprevbest = sbest;
    for(is=-50;is<51;is++)
    {
      s = guess + is*ds;
      if(s>=0 && s<1)
      {
        SetSinSq2Theta13(s);
        chi2 = Minimize();
        if(fabs(chi2-contourlvl)<fabs(chi2best-contourlvl))
        {
          chi2best = chi2;
          sbest = s;
        }
      }
    }
    goto again;
    
  }
  
  cout<<"best s = "<<sbest<<", at m = "<<deltamsq31<<", chi2 = "<<chi2best<<endl;

  return sbest;
}
void Experiment::SetSigma_c(Double_t sigma)
{
  fSigma_c = sigma;
  return;
}
void Experiment::SetSigma_shape(Double_t sigma)
{
  fSigma_shape = sigma;
  return;
}
void Experiment::SetSigma_D(Double_t sigma)
{
  fSigma_D = sigma;
  return;
}
void Experiment::SetSigma_b2b(Double_t sigma)
{
  fSigma_b2b = sigma;
  return;
}
void Experiment::SetSinSq2Theta13(Double_t sinsq2theta13)
{
  ffSsq2T13 = sinsq2theta13;
  return;
}
void Experiment::SetDeltaMSq31(Double_t deltamsq31)
{
  ffDMsq31 = deltamsq31;
  return;
}
void Experiment::SetTrueSinSq2Theta13(Double_t truesinsq2theta13)
{
  fTrueSsq2T13 = truesinsq2theta13;
  return;
}
void Experiment::SetTrueDeltaMSq31(Double_t truedeltamsq31)
{
  fTrueDMsq31 = truedeltamsq31;
  return;
}
void Experiment::SetPrintFit(bool printfit)
{
  fPrintFit = printfit;
  return;
}
void Experiment::SetNBins(Int_t bins)
{
  if(fNDetectors==0)
  {
    cout<<"Error in Experiment::SetNBins() - please use Experiment::AddDetector() before calling this function"<<endl;
    return;
  }
  
  Detector *dtemp = (Detector*)fDetectors->At(0);
  
  Double_t detbins_d = (8.0-1.0)/dtemp->GetBinWidth();
  Int_t detbins = (Int_t)(detbins_d);
  if(fabs(detbins_d - detbins)>=0.5)//round it correctly
  {
    detbins++;
  }
  //detbins is number of detector bins from 1.0 to 8.0 MeV
  //this assumes that the bin width is a number that divides nicely into 1 MeV
//   cout<<"number of det bins 1-8 = "<<detbins<<endl;
  Int_t newwidth;
  Double_t newwidth_d;
//   cout<<"detbins%bins = "<<detbins%bins<<endl;
  if(detbins%bins==0)
  {
    newwidth = detbins/bins;
  }
  else
  {
    newwidth_d = ((Double_t)detbins/bins);
//     cout<<"newwidth_d = "<<newwidth_d<<endl;
    newwidth = (Int_t)newwidth_d;
    if(fabs(newwidth_d - newwidth)>=0.5)//round it correctly
    {
      newwidth++;
    }
  }
//   cout<<"width in # detector bins = "<<newwidth<<endl;
  Int_t nbins_out = detbins/newwidth;
//   cout<<"nbins = "<<nbins_out<<endl;
  
  Double_t binwidth = newwidth*dtemp->GetBinWidth();
//   cout<<"bin width = "<<binwidth<<endl;

  Int_t ibin;
  Double_t be;
  fEdges.clear();
  
  for(ibin=0;ibin<nbins_out;ibin++)
  {
    be = 1.0 + ibin*binwidth;
    fEdges.push_back(be);
  }
  fEdges.push_back(8.0);
  
//   cout<<"edges"<<endl;
//   for(ibin=0;ibin<nbins_out+1;ibin++)
//   {
//     cout<<fEdges.at(ibin)<<endl;
//   }
  
  fNBins=nbins_out;
  
  return;
}
Int_t Experiment::GetNDetectors()
{
  return fNDetectors;
}
Int_t Experiment::GetNBins()
{
  return fNBins;
}
Bool_t Experiment::BinInFit(Int_t bin)
{
  return fBin.at(bin);
}
Double_t Experiment::GetSigma_c()
{
  return fSigma_c;
}
Double_t Experiment::GetSigma_shape()
{
  return fSigma_shape;
}
Double_t Experiment::GetSigma_D()
{
  return fSigma_D;
}
Double_t Experiment::GetSigma_b2b()
{
  return fSigma_b2b;
}
Int_t Experiment::GetNPar()
{
  return fNPar;
}
Double_t Experiment::GetSinSq2Theta13()
{
  return ffSsq2T13;
}
Double_t Experiment::GetDeltaMSq31()
{
  return ffDMsq31;
}
Int_t Experiment::alpha_c()
{
  return alpha_c_parno;
}
Int_t Experiment:: alpha_r(Int_t core)
{
  return alpha_r_parno.at(core);
}
Int_t Experiment::beta(Int_t bin)
{
  return beta_parno.at(bin);
}
Int_t Experiment::epsilon_D()
{
  return epsilon_D_parno;
}
Int_t Experiment::epsilon_d(Int_t det)
{
  return epsilon_d_parno.at(det);
}
Int_t Experiment::eta_f(Int_t det)
{
  return eta_f_parno.at(det);
}
Int_t Experiment::eta_n(Int_t det)
{
  return eta_n_parno.at(det);
}
Int_t Experiment::eta_s(Int_t det)
{
  return eta_s_parno.at(det);
}

