#define ReactorCore_C

#include "ReactorCore.h"

ClassImp(ReactorCore)

ReactorCore::ReactorCore()
{
  fFractionU235=0.58;
  fFractionU238=0.07;
  fFractionPu239=0.30;
  fFractionPu241=0.05;
  
  fVEFluxParU235[0]=0.870;
  fVEFluxParU235[1]=-0.160;
  fVEFluxParU235[2]=-0.0910;
  fVEFluxParU238[0]=0.976;
  fVEFluxParU238[1]=-0.162;
  fVEFluxParU238[2]=-0.0790;
  fVEFluxParPu239[0]=0.896;
  fVEFluxParPu239[1]=-0.239;
  fVEFluxParPu239[2]=-0.0981;
  fVEFluxParPu241[0]=0.793;
  fVEFluxParPu241[1]=-0.080;
  fVEFluxParPu241[2]=-0.1085;
  
  fHSFluxParU235[0]=3.519;
  fHSFluxParU235[1]=-3.517;
  fHSFluxParU235[2]=1.595;
  fHSFluxParU235[3]=-4.171e-1;
  fHSFluxParU235[4]=5.004e-2;
  fHSFluxParU235[5]=-2.303e-3;
  fHSFluxParU238[0]=fVEFluxParU238[0];
  fHSFluxParU238[1]=fVEFluxParU238[1];
  fHSFluxParU238[2]=fVEFluxParU238[2];
  fHSFluxParU238[3]=0;
  fHSFluxParU238[4]=0;
  fHSFluxParU238[5]=0;
  fHSFluxParPu239[0]=2.560;
  fHSFluxParPu239[1]=-2.654;
  fHSFluxParPu239[2]=1.256;
  fHSFluxParPu239[3]=-3.617e-1;
  fHSFluxParPu239[4]=4.547e-2;
  fHSFluxParPu239[5]=-2.143e-3;
  fHSFluxParPu241[0]=1.487;
  fHSFluxParPu241[1]=-1.038;
  fHSFluxParPu241[2]=4.130e-1;
  fHSFluxParPu241[3]=-1.423e-1;
  fHSFluxParPu241[4]=1.866e-2;
  fHSFluxParPu241[5]=-9.229e-4;
  
  fModel = "HS";
  
  fExpectedPower = 2.9;//GW
  fActualPower = 2.9;//GW
  
  fFissionspersecondGW  = 3.1e19;//fissions/(second*GW)
  
  fSigma_r = 0.02;//from TDR
  
  BuilddNdE();
  
}
ReactorCore::~ReactorCore()
{
}
void ReactorCore::BuilddNdE()
{
  if(fModel!="VE" && fModel!="HS")
  {
    cout<<"Error: please choose 'VE' or 'HS' as the model"<<endl;
    return;
  }
  
  if(fModel=="VE")
  {
    dNdE_Expected = new TF1("dNdE_Expected","([0]*(exp(pol2(1))) + [4]*(exp(pol2(5))) + [8]*(exp(pol2(9))) + [12]*(exp(pol2(13))))*[16]*[17]",0.0,10.0);
    
    dNdE_Expected->SetParameter(0,fFractionU235);
    dNdE_Expected->SetParameter(1,fVEFluxParU235[0]);
    dNdE_Expected->SetParameter(2,fVEFluxParU235[1]);
    dNdE_Expected->SetParameter(3,fVEFluxParU235[2]);
  
    dNdE_Expected->SetParameter(4,fFractionU238);
    dNdE_Expected->SetParameter(5,fVEFluxParU238[0]);
    dNdE_Expected->SetParameter(6,fVEFluxParU238[1]);
    dNdE_Expected->SetParameter(7,fVEFluxParU238[2]);
  
    dNdE_Expected->SetParameter(8,fFractionPu239);
    dNdE_Expected->SetParameter(9,fVEFluxParPu239[0]);
    dNdE_Expected->SetParameter(10,fVEFluxParPu239[1]);
    dNdE_Expected->SetParameter(11,fVEFluxParPu239[2]);
  
    dNdE_Expected->SetParameter(12,fFractionPu241);
    dNdE_Expected->SetParameter(13,fVEFluxParPu241[0]);
    dNdE_Expected->SetParameter(14,fVEFluxParPu241[1]);
    dNdE_Expected->SetParameter(15,fVEFluxParPu241[2]);
    
    dNdE_Expected->SetParameter(16,fFissionspersecondGW );
  
    dNdE_Expected->SetParameter(17,fExpectedPower);
    
    dNdE_Actual = new TF1("dNdE_Actual","([0]*(exp(pol2(1))) + [4]*(exp(pol2(5))) + [8]*(exp(pol2(9))) + [12]*(exp(pol2(13))))*[16]*[17]",0.0,10.0);
    
    dNdE_Actual->SetParameter(0,fFractionU235);
    dNdE_Actual->SetParameter(1,fVEFluxParU235[0]);
    dNdE_Actual->SetParameter(2,fVEFluxParU235[1]);
    dNdE_Actual->SetParameter(3,fVEFluxParU235[2]);
  
    dNdE_Actual->SetParameter(4,fFractionU238);
    dNdE_Actual->SetParameter(5,fVEFluxParU238[0]);
    dNdE_Actual->SetParameter(6,fVEFluxParU238[1]);
    dNdE_Actual->SetParameter(7,fVEFluxParU238[2]);
  
    dNdE_Actual->SetParameter(8,fFractionPu239);
    dNdE_Actual->SetParameter(9,fVEFluxParPu239[0]);
    dNdE_Actual->SetParameter(10,fVEFluxParPu239[1]);
    dNdE_Actual->SetParameter(11,fVEFluxParPu239[2]);
  
    dNdE_Actual->SetParameter(12,fFractionPu241);
    dNdE_Actual->SetParameter(13,fVEFluxParPu241[0]);
    dNdE_Actual->SetParameter(14,fVEFluxParPu241[1]);
    dNdE_Actual->SetParameter(15,fVEFluxParPu241[2]);
    
    dNdE_Actual->SetParameter(16,fFissionspersecondGW );
  
    dNdE_Actual->SetParameter(17,fActualPower);
  }
  
  if(fModel=="HS")
  {
    dNdE_Expected = new TF1("dNdE_Expected","([0]*(exp(pol5(1))) + [7]*(exp(pol5(8))) + [14]*(exp(pol5(15))) + [21]*(exp(pol5(22))))*[28]*[29]",0.0,10.0);
    
    dNdE_Expected->SetParameter(0,fFractionU235);
    dNdE_Expected->SetParameter(1,fHSFluxParU235[0]);
    dNdE_Expected->SetParameter(2,fHSFluxParU235[1]);
    dNdE_Expected->SetParameter(3,fHSFluxParU235[2]);
    dNdE_Expected->SetParameter(4,fHSFluxParU235[3]);
    dNdE_Expected->SetParameter(5,fHSFluxParU235[4]);
    dNdE_Expected->SetParameter(6,fHSFluxParU235[5]);
  
    dNdE_Expected->SetParameter(7,fFractionU238);
    dNdE_Expected->SetParameter(8,fHSFluxParU238[0]);
    dNdE_Expected->SetParameter(9,fHSFluxParU238[1]);
    dNdE_Expected->SetParameter(10,fHSFluxParU238[2]);
    dNdE_Expected->SetParameter(11,fHSFluxParU238[3]);
    dNdE_Expected->SetParameter(12,fHSFluxParU238[4]);
    dNdE_Expected->SetParameter(13,fHSFluxParU238[5]);
  
    dNdE_Expected->SetParameter(14,fFractionPu239);
    dNdE_Expected->SetParameter(15,fHSFluxParPu239[0]);
    dNdE_Expected->SetParameter(16,fHSFluxParPu239[1]);
    dNdE_Expected->SetParameter(17,fHSFluxParPu239[2]);
    dNdE_Expected->SetParameter(18,fHSFluxParPu239[3]);
    dNdE_Expected->SetParameter(19,fHSFluxParPu239[4]);
    dNdE_Expected->SetParameter(20,fHSFluxParPu239[5]);
  
    dNdE_Expected->SetParameter(21,fFractionPu241);
    dNdE_Expected->SetParameter(22,fHSFluxParPu241[0]);
    dNdE_Expected->SetParameter(23,fHSFluxParPu241[1]);
    dNdE_Expected->SetParameter(24,fHSFluxParPu241[2]);
    dNdE_Expected->SetParameter(25,fHSFluxParPu241[3]);
    dNdE_Expected->SetParameter(26,fHSFluxParPu241[4]);
    dNdE_Expected->SetParameter(27,fHSFluxParPu241[5]);
    
    dNdE_Expected->SetParameter(28,fFissionspersecondGW );
  
    dNdE_Expected->SetParameter(29,fExpectedPower);
    
    dNdE_Actual = new TF1("dNdE_Actual","([0]*(exp(pol5(1))) + [7]*(exp(pol5(8))) + [14]*(exp(pol5(15))) + [21]*(exp(pol5(22))))*[28]*[29]",0.0,10.0);
    
    dNdE_Actual->SetParameter(0,fFractionU235);
    dNdE_Actual->SetParameter(1,fHSFluxParU235[0]);
    dNdE_Actual->SetParameter(2,fHSFluxParU235[1]);
    dNdE_Actual->SetParameter(3,fHSFluxParU235[2]);
    dNdE_Actual->SetParameter(4,fHSFluxParU235[3]);
    dNdE_Actual->SetParameter(5,fHSFluxParU235[4]);
    dNdE_Actual->SetParameter(6,fHSFluxParU235[5]);
  
    dNdE_Actual->SetParameter(7,fFractionU238);
    dNdE_Actual->SetParameter(8,fHSFluxParU238[0]);
    dNdE_Actual->SetParameter(9,fHSFluxParU238[1]);
    dNdE_Actual->SetParameter(10,fHSFluxParU238[2]);
    dNdE_Actual->SetParameter(11,fHSFluxParU238[3]);
    dNdE_Actual->SetParameter(12,fHSFluxParU238[4]);
    dNdE_Actual->SetParameter(13,fHSFluxParU238[5]);
  
    dNdE_Actual->SetParameter(14,fFractionPu239);
    dNdE_Actual->SetParameter(15,fHSFluxParPu239[0]);
    dNdE_Actual->SetParameter(16,fHSFluxParPu239[1]);
    dNdE_Actual->SetParameter(17,fHSFluxParPu239[2]);
    dNdE_Actual->SetParameter(18,fHSFluxParPu239[3]);
    dNdE_Actual->SetParameter(19,fHSFluxParPu239[4]);
    dNdE_Actual->SetParameter(20,fHSFluxParPu239[5]);
  
    dNdE_Actual->SetParameter(21,fFractionPu241);
    dNdE_Actual->SetParameter(22,fHSFluxParPu241[0]);
    dNdE_Actual->SetParameter(23,fHSFluxParPu241[1]);
    dNdE_Actual->SetParameter(24,fHSFluxParPu241[2]);
    dNdE_Actual->SetParameter(25,fHSFluxParPu241[3]);
    dNdE_Actual->SetParameter(26,fHSFluxParPu241[4]);
    dNdE_Actual->SetParameter(27,fHSFluxParPu241[5]);
    
    dNdE_Actual->SetParameter(28,fFissionspersecondGW );
  
    dNdE_Actual->SetParameter(29,fActualPower);
  }
  
  return;
}
void ReactorCore::SetFractions(Double_t frac_U235,Double_t frac_U238,Double_t frac_Pu239,Double_t frac_Pu241)
{
  if(TMath::Abs(frac_U235+frac_U238+frac_Pu239+frac_Pu241-1.0)>1e-6)
  {
    cout<<"Error in ReactorCore::SetFractions - input fractions don't add up to 1!  USING DEFAULT FRACTION VALUES."<<endl;
    return;
  }
  fFractionU235=frac_U235;
  fFractionU238=frac_U238;
  fFractionPu239=frac_Pu239;
  fFractionPu241=frac_Pu241;
  
  BuilddNdE();
  
  return;
}
void ReactorCore::SetVEFluxPars(string isotope, Double_t fpar[3])
{
  int i;
  if(isotope=="U235")
  {
    for(i=0;i<3;i++)
    {
      fVEFluxParU235[i]=fpar[i];
    }
  }
  else if(isotope=="U238")
  {
    for(i=0;i<3;i++)
    {
      fVEFluxParU238[i]=fpar[i];
    }
  }
  else if(isotope=="Pu239")
  {
    for(i=0;i<3;i++)
    {
      fVEFluxParPu239[i]=fpar[i];
    }
  }
  else if(isotope=="Pu241")
  {
    for(i=0;i<3;i++)
    {
      fVEFluxParPu241[i]=fpar[i];
    }
  }
  else
  {
    cout<<"Error in ReactorCore::SetVEFluxPars(string isotope, Double_t fpar[3]): isotope must be 'U235', 'U238', 'Pu239', or 'Pu241'."<<endl;
    return;
  }
  
  BuilddNdE();
  
  return;
}
void ReactorCore::SetHSFluxPars(string isotope, Double_t fpar[6])
{
  int i;
  if(isotope=="U235")
  {
    for(i=0;i<6;i++)
    {
      fHSFluxParU235[i]=fpar[i];
    }
  }
  else if(isotope=="U238")
  {
    for(i=0;i<6;i++)
    {
      fHSFluxParU238[i]=fpar[i];
    }
  }
  else if(isotope=="Pu239")
  {
    for(i=0;i<6;i++)
    {
      fHSFluxParPu239[i]=fpar[i];
    }
  }
  else if(isotope=="Pu241")
  {
    for(i=0;i<6;i++)
    {
      fHSFluxParPu241[i]=fpar[i];
    }
  }
  else
  {
    cout<<"Error in ReactorCore::SetHSFluxPars(string isotope, Double_t fpar[6]): isotope must be 'U235', 'U238', 'Pu239', or 'Pu241'."<<endl;
    return;
  }
  
  BuilddNdE();
  
  return;
}
void ReactorCore::SetModel(string model)
{
  fModel = model;
  
  BuilddNdE();
  
  return;
}
void ReactorCore::SetExpectedPower(Double_t power)
{
  fExpectedPower=power;
  
  BuilddNdE();
  
  return;
}
void ReactorCore::SetActualPower(Double_t power)
{
  fActualPower=power;
  
  BuilddNdE();
  
  return;
}
void ReactorCore::SetFissionsPerSecondGW(Double_t f)
{
  fFissionspersecondGW=f;
  
  BuilddNdE();
  
  return;
}
void ReactorCore::SetSigma_r(Double_t sigma)
{
  fSigma_r = sigma;
  
  return;
}
Double_t ReactorCore::GetFraction(string isotope)
{
  if(isotope=="U235")
  {
    return fFractionU235;
  }
  else if(isotope=="U238")
  {
    return fFractionU238;
  }
  else if(isotope=="Pu239")
  {
    return fFractionPu239;
  }
  else if(isotope=="Pu241")
  {
    return fFractionPu241;
  }
  else
  {
    cout<<"Error in ReactorCore::GetFraction(string isotope): isotope must be 'U235', 'U238', 'Pu239', or 'Pu241'."<<endl;
    return -1;
  }
}
Double_t ReactorCore::GetVEFluxPars(string isotope,Int_t parno)
{
  if(parno<0 || parno>2)
  {
    cout<<"Error in ReactorCore::GetVEFluxPars(string isotope,Int_t parno): parno must be 0,1,2 (parameters for calculation of reactor neutrino flux by Vogel and Engel)"<<endl;
  }
  if(isotope=="U235")
  {
    return fVEFluxParU235[parno];
  }
  else if(isotope=="U238")
  {
    return fVEFluxParU238[parno];
  }
  else if(isotope=="Pu239")
  {
    return fVEFluxParPu239[parno];
  }
  else if(isotope=="Pu241")
  {
    return fVEFluxParPu241[parno];
  }
  else
  {
    cout<<"Error in ReactorCore::GetVEFluxPars(string isotope,Int_t parno): isotope must be 'U235', 'U238', 'Pu239', or 'Pu241'."<<endl;
    return -1;
  }
}
Double_t ReactorCore::GetHSFluxPars(string isotope,Int_t parno)
{
  if(parno<0 || parno>5)
  {
    cout<<"Error in ReactorCore::GetVEFluxPars(string isotope,Int_t parno): parno must be 0,1,2,3,4,5 (parameters for calculation of reactor neutrino flux by Huber and Schwetz)"<<endl;
  }
  if(isotope=="U235")
  {
    return fHSFluxParU235[parno];
  }
  else if(isotope=="U238")
  {
    return fHSFluxParU238[parno];
  }
  else if(isotope=="Pu239")
  {
    return fHSFluxParPu239[parno];
  }
  else if(isotope=="Pu241")
  {
    return fHSFluxParPu241[parno];
  }
  else
  {
    cout<<"Error in ReactorCore::GetHSFluxPars(string isotope,Int_t parno): isotope must be 'U235', 'U238', 'Pu239', or 'Pu241'."<<endl;
    return -1;
  }
}
void ReactorCore::PrintModel()
{
  cout<<"fModel = "<<fModel<<endl;
  
  return;
}
Double_t ReactorCore::GetExpectedPower()
{
  return fExpectedPower;
}
Double_t ReactorCore::GetActualPower()
{
  return fActualPower;
}
Double_t ReactorCore::GetFissionsPerSecondGW()
{
  return fFissionspersecondGW;
}
Double_t ReactorCore::GetSigma_r()
{
  return fSigma_r;
}

