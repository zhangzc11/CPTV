//
//  Author: Hanyu Wei
//  Summer of 2011
// 
//  Adopted by Zhe Wang 
//  Apr. 7, 2012
//
#include "TMinuit.h"
#include "TF1.h"
#include "unistd.h"
#include "TFormula.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "stdio.h"
#include "math.h"
#include "TGraph.h"

#define n_bins_ 30
#define widen_nbins 100
#define power 2.9
#define mtarget 20
#define nreactor 2.0

   Double_t dybsite[n_bins_];
   Double_t dybsite_DYB[n_bins_];
   Double_t dybsite_LA[n_bins_];
   Double_t dybsite_LAII[n_bins_];

   Double_t lasite[n_bins_];
   Double_t lasite_DYB[n_bins_];
   Double_t lasite_LA[n_bins_];
   Double_t lasite_LAII[n_bins_];

   Double_t farsite[n_bins_];
   Double_t farsite_DYB[n_bins_];
   Double_t farsite_LA[n_bins_];
   Double_t farsite_LAII[n_bins_];

   Double_t dybsite0[n_bins_];
   Double_t dybsite_DYB0[n_bins_];
   Double_t dybsite_LA0[n_bins_];
   Double_t dybsite_LAII0[n_bins_];

   Double_t lasite0[n_bins_];
   Double_t lasite_DYB0[n_bins_];
   Double_t lasite_LA0[n_bins_];
   Double_t lasite_LAII0[n_bins_];

   Double_t farsite0[n_bins_];
   Double_t farsite_DYB0[n_bins_];
   Double_t farsite_LA0[n_bins_];
   Double_t farsite_LAII0[n_bins_];


   Double_t dybbkg_li9[n_bins_];
   Double_t dybbkg_fastn[n_bins_];
   Double_t dybbkg_acd[n_bins_];

   Double_t labkg_li9[n_bins_];
   Double_t labkg_fastn[n_bins_];
   Double_t labkg_acd[n_bins_];

   Double_t farbkg_li9[n_bins_];
   Double_t farbkg_fastn[n_bins_];
   Double_t farbkg_acd[n_bins_];

   Double_t dybbkg_li90[n_bins_];
   Double_t dybbkg_fastn0[n_bins_];
   Double_t dybbkg_acd0[n_bins_];

   Double_t labkg_li90[n_bins_];
   Double_t labkg_fastn0[n_bins_];
   Double_t labkg_acd0[n_bins_];

   Double_t farbkg_li90[n_bins_];
   Double_t farbkg_fastn0[n_bins_];
   Double_t farbkg_acd0[n_bins_];

   Int_t u_bins_;
   Int_t d_bins_;
   Double_t er_c=0.02;
   Double_t er_r=0.02;
   Double_t er_D=0.02;
   Double_t er_shp=0.02;
   Double_t er_d=0.0038;
   Double_t er_F=1.0;
   Double_t er_N=1.0;
   Double_t er_S=1.0;

   Double_t factor;


   Double_t func(Double_t *x,Double_t *par){
      Double_t xx=x[0];
      Double_t f;
      f=1-par[0]*sin(1.267e+3*par[1]*par[2]/xx)*sin(1.267e+3*par[1]*par[2]/xx);
      return f;
   }

   Double_t events[n_bins_];
   Double_t energy[n_bins_];
   Double_t wbins=8.2/n_bins_;

void spectrum(){
   
   Int_t i;
   Int_t j;
//  TCanvas *c=new TCanvas("c","neutrino spectrum",100,100,800,1000);
//   c->cd();

//   TH1F *hf1=new TH1F("hf1","hf1",n_bins_,1.8,10);
//   TH1F *hf2=new TH1F("hf2","hf2",n_bins_,1.8,10);

   TF1 *neutrino_f=new TF1("neutrino_f","0.58*exp(0.870-0.160*x-0.0910*x*x)+0.3*exp(0.896-0.239*x-0.0981*x*x)+0.07*exp(0.976-0.162*x-0.0790*x*x)+0.05*exp(0.793-0.080*x-0.1085*x*x)",0,12);
   
   TFormula *positron_m=new TFormula("positron_m","sqrt((x-1.2933)*(x-1.2933)-0.511*0.511)");
     
   TF1 *cross_section=new TF1("cross_section","0.0952*(x-1.2933)*positron_m",1,10);
  
   TF1 *neutrino_sp=new TF1("neutrino_sp","neutrino_f*cross_section",1,10);
   
   Double_t C;
   C=0.76/neutrino_sp->Integral(1.8,10);
   TF1 *dneutrino_sp=new TF1("dneutrino_sp","[0]*neutrino_sp",1,10);
   dneutrino_sp->SetParameter(0,C);


   for(j=1;j<=n_bins_;j++){
     energy[j-1]=1.8+wbins*(j-0.5);
     events[j-1]=dneutrino_sp->Integral(1.8+(j-1)*wbins,1.8+j*wbins);
//     hf1->SetBinContent(j,events[j-1]);
      }     
//      hf1->Draw(); 
  
   for(j=1;j<=n_bins_;j++){
      events[j-1]=0;
   }

   Double_t widen_wbins=8.2/widen_nbins;
   Double_t mean;
   Double_t sigma;
   Double_t cef;
   
   for(i=1;i<=widen_nbins;i++){
      mean=1.8+widen_wbins*(i-0.5);
      sigma=0.12*sqrt(mean);      
      TF1 *widen_g=new TF1("widen_g","exp(-(x-[0])*(x-[0])/(2*[1]*[1]))",1,12);
      widen_g->SetParameters(mean,sigma);
      cef=dneutrino_sp->Integral(1.8+(i-1)*widen_wbins,1.8+i*widen_wbins)/widen_g->Integral(1,12); 
      TF1 *widen=new TF1("widen","[0]*widen_g",1,12);
      widen->SetParameter(0,cef);
      for(j=1;j<=n_bins_;j++){
        events[j-1]+=widen->Integral(1.8+(j-1)*wbins,1.8+j*wbins);
      }     
   }
/*
   for(j=1;j<=n_bins_;j++){
     hf2->SetBinContent(j,events[j-1]);
   }     
 
   hf2->SetLineColor(kRed);   
   hf2->Draw("same");
*/ 
}




void sp(Double_t s2,Double_t d_m,Double_t rundays,Double_t *dyb,Double_t *dyb_DYB,Double_t *dyb_LA,Double_t *dyb_LAII,Double_t *la,Double_t *la_DYB,Double_t *la_LA,Double_t *la_LAII,Double_t *far,Double_t *far_DYB,Double_t *far_LA,Double_t *far_LAII,Double_t *dybbkg_li9,Double_t *dybbkg_fastn,Double_t *dybbkg_acd,Double_t *labkg_li9,Double_t *labkg_fastn,Double_t *labkg_acd,Double_t *farbkg_li9,Double_t *farbkg_fastn,Double_t *farbkg_acd){
   Int_t i;

   Double_t dyb1[]={s2,d_m,0.363};
   for(i=1;i<=n_bins_;i++){
      dyb_DYB[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],dyb1)*events[i-1]/(0.363*0.363);  
   }   
   Double_t dyb2[]={s2,d_m,0.857};
   for(i=1;i<=n_bins_;i++){
      dyb_LA[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],dyb2)*events[i-1]/(0.857*0.857);
   } 
   Double_t dyb3[]={s2,d_m,1.307};
   for(i=1;i<=n_bins_;i++){
      dyb_LAII[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],dyb3)*events[i-1]/(1.307*1.307);
   } 
   for(i=1;i<=n_bins_;i++){
      dyb[i-1]=0.75*(dyb_DYB[i-1]+dyb_LA[i-1]+dyb_LAII[i-1]);
   }
   


   Double_t la1[]={s2,d_m,1.347};
   for(i=1;i<=n_bins_;i++){
      la_DYB[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],la1)*events[i-1]/(1.347*1.347);
   }
   Double_t la2[]={s2,d_m,0.481};
   for(i=1;i<=n_bins_;i++){
      la_LA[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],la2)*events[i-1]/(0.481*0.481);
   }
   Double_t la3[]={s2,d_m,0.526};
   for(i=1;i<=n_bins_;i++){
      la_LAII[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],la3)*events[i-1]/(0.526*0.526);
   }
   for(i=1;i<=n_bins_;i++){
      la[i-1]=0.85*(la_DYB[i-1]+la_LA[i-1]+la_LAII[i-1]);
   }


   Double_t far1[]={s2,d_m,1.985};
   for(i=1;i<=n_bins_;i++){
      far_DYB[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],far1)*events[i-1]/(1.985*1.985);
   }
   Double_t far2[]={s2,d_m,1.618};
   for(i=1;i<=n_bins_;i++){
      far_LA[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],far2)*events[i-1]/(1.618*1.618);
   }
   Double_t far3[]={s2,d_m,1.613};
   for(i=1;i<=n_bins_;i++){
      far_LAII[i-1]=rundays*power*mtarget*nreactor*func(&energy[i-1],far3)*events[i-1]/(1.613*1.613);
   }
   for(i=1;i<=n_bins_;i++){
      far[i-1]=0.99*(far_DYB[i-1]+far_LA[i-1]+far_LAII[i-1]);
   }

 
   Double_t C1,C2,C3;
   Double_t sum=0;
   for(i=1;i<=n_bins_;i++){
     sum+=dyb[i-1];
   }
   C1=sum;
 
   sum=0;
   for(i=1;i<=n_bins_;i++){
     sum+=la[i-1];
   }
   C2=sum;
   sum=0;
   for(i=1;i<=n_bins_;i++){
     sum+=far[i-1];
   }
   C3=sum;
/*   
   cout<<"dyb:"<<C1<<endl;
   cout<<"la:"<<C2<<endl;
   cout<<"far:"<<C3<<endl;
*/

   TF1 *Li_9=new TF1("Li_9","[0]*exp(-0.5*((x-[1])/[2])**2)+[3]*exp(-0.5*((x-[4])/[5])**2)+[6]*exp(-0.5*((x-[7])/[8])**2)",0,10);
   Li_9->SetParameter(0,-3.46940e-02);
   Li_9->SetParameter(1,2.61314e+00);
   Li_9->SetParameter(2,5.06524e+00);
   Li_9->SetParameter(3,1.71599e-01);
   Li_9->SetParameter(4,4.05220e+00);
   Li_9->SetParameter(5,2.17596e+00);
   Li_9->SetParameter(6,9.03400e-02);
   Li_9->SetParameter(7,7.25785e+00);
   Li_9->SetParameter(8,-1.69872e+00);

   TF1 *fastn=new TF1("fastn","1",0,10);

   TF1 *acd=new TF1("acd","exp(-x)",0,10);


   Double_t C;
   TF1 *dybLi_9=new TF1("dybLi_9","[0]*Li_9",1.8,10);
   C=0.003*C1/Li_9->Integral(1.8,10);   
   dybLi_9->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     dybbkg_li9[i-1]=dybLi_9->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       


   TF1 *dybfastn=new TF1("dybfastn","[0]*fastn",1.8,10);
   C=0.001*C1/fastn->Integral(1.8,10);   
   dybfastn->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     dybbkg_fastn[i-1]=dybfastn->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       

 
   TF1 *dybacd=new TF1("dybacd","[0]*acd",1.8,10);
   C=0.002*C1/acd->Integral(1.8,10);   
   dybacd->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     dybbkg_acd[i-1]=dybacd->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       


   TF1 *laLi_9=new TF1("laLi_9","[0]*Li_9",1.8,10);
   C=0.002*C2/Li_9->Integral(1.8,10);   
   laLi_9->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     labkg_li9[i-1]=laLi_9->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       


   TF1 *lafastn=new TF1("lafastn","[0]*fastn",1.8,10);
   C=0.001*C2/fastn->Integral(1.8,10);   
   lafastn->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     labkg_fastn[i-1]=lafastn->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       

 
   TF1 *laacd=new TF1("laacd","[0]*acd",1.8,10);
   C=0.002*C2/acd->Integral(1.8,10);   
   laacd->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     labkg_acd[i-1]=laacd->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       




   TF1 *farLi_9=new TF1("farLi_9","[0]*Li_9",1.8,10);
   C=0.002*C3/Li_9->Integral(1.8,10);   
   farLi_9->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     farbkg_li9[i-1]=farLi_9->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       


   TF1 *farfastn=new TF1("farfastn","[0]*fastn",1.8,10);
   C=0.001*C3/fastn->Integral(1.8,10);   
   farfastn->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     farbkg_fastn[i-1]=farfastn->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       

 
   TF1 *faracd=new TF1("faracd","[0]*acd",1.8,10);
   C=0.001*C3/acd->Integral(1.8,10);   
   faracd->SetParameter(0,C);

   for(i=1;i<=n_bins_;i++){
     farbkg_acd[i-1]=faracd->Integral(1.8+(i-1)*wbins,1.8+i*wbins);
   }       
   
/*
   for(i=24;i<=30;i++){

     dyb[i-1]=dyb[i-1]*factor;
     dyb_DYB[i-1]=dyb_DYB[i-1]*factor;
     dyb_LA[i-1]=dyb_LA[i-1]*factor;
     dyb_LAII[i-1]=dyb_LAII[i-1]*factor;
     la[i-1]=la[i-1]*factor;
     la_DYB[i-1]=la_DYB[i-1]*factor;
     la_LA[i-1]=la_LA[i-1]*factor;
     la_LAII[i-1]=la_LAII[i-1]*factor;
     far[i-1]=far[i-1]*factor;
     far_DYB[i-1]=far_DYB[i-1]*factor;
     far_LA[i-1]=far_LA[i-1]*factor;
     far_LAII[i-1]=far_LAII[i-1]*factor;
   }
*/
/*
    for(i=24;i<=30;i++){
      
     dybbkg_li9[i-1]=dybbkg_li9[i-1]*factor;
     dybbkg_fastn[i-1]=dybbkg_fastn[i-1]*factor;
     dybbkg_acd[i-1]=dybbkg_acd[i-1]*factor;

     labkg_li9[i-1]=labkg_li9[i-1]*factor;
     labkg_fastn[i-1]=labkg_fastn[i-1]*factor;
     labkg_acd[i-1]=labkg_acd[i-1]*factor;

     farbkg_li9[i-1]=farbkg_li9[i-1]*factor;
     farbkg_fastn[i-1]=farbkg_fastn[i-1]*factor;
     farbkg_acd[i-1]=farbkg_acd[i-1]*factor;
    }
*/   
}  



void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag){
   Int_t A;
   Int_t i;
   Int_t r;
 
   Double_t chisq=0.0;
   Double_t delta=0.0;
   Double_t Sigma_wr;
   for(A=1;A<=8;A++){
     if(A==1||A==2){
       for(i=d_bins_;i<=u_bins_;i++){
          if(dybsite[i-1]!=0){
          Sigma_wr=par[1]*dybsite_DYB[i-1]/dybsite[i-1]+par[2]*dybsite_DYB[i-1]/dybsite[i-1]+par[3]*dybsite_LA[i-1]/dybsite[i-1]+par[4]*dybsite_LA[i-1]/dybsite[i-1]+par[5]*dybsite_LAII[i-1]/dybsite[i-1]+par[6]*dybsite_LAII[i-1]/dybsite[i-1];
          delta=dybsite0[i-1]-dybsite[i-1]*(1+par[0]+0.75*0.5*Sigma_wr+par[i-d_bins_+40]+par[7]+par[A+7])-par[A+15]*dybbkg_fastn[i-1]-par[A+23]*dybbkg_acd[i-1]-par[A+31]*dybbkg_li9[i-1];
          chisq+=delta*delta/(dybsite[i-1]+0.003*0.003*dybsite[i-1]*dybsite[i-1]);
          }     
       }
       chisq+=(par[A+7]/er_d)*(par[A+7]/er_d)+par[A+15]*par[A+15]/(er_F*er_F)+par[A+23]*par[A+23]/(er_N*er_N)+par[A+31]*par[A+31]/(er_S*er_S);
     }
     if(A==3||A==4){ 
       for(i=d_bins_;i<=u_bins_;i++){
          if(lasite[i-1]!=0){
          Sigma_wr=par[1]*lasite_DYB[i-1]/lasite[i-1]+par[2]*lasite_DYB[i-1]/lasite[i-1]+par[3]*lasite_LA[i-1]/lasite[i-1]+par[4]*lasite_LA[i-1]/lasite[i-1]+par[5]*lasite_LAII[i-1]/lasite[i-1]+par[6]*lasite_LAII[i-1]/lasite[i-1];
          delta=lasite0[i-1]-lasite[i-1]*(1+par[0]+0.85*0.5*Sigma_wr+par[i-d_bins_+40]+par[7]+par[A+7])-par[A+15]*labkg_fastn[i-1]-par[A+23]*labkg_acd[i-1]-par[A+31]*labkg_li9[i-1];
          chisq+=delta*delta/(lasite[i-1]+0.003*0.003*lasite[i-1]*lasite[i-1]);
          }
       }
       chisq+=(par[A+7]/er_d)*(par[A+7]/er_d)+par[A+15]*par[A+15]/(er_F*er_F)+par[A+23]*par[A+23]/(er_N*er_N)+par[A+31]*par[A+31]/(er_S*er_S);
     }

     if(A==5||A==6||A==7||A==8){ 
       for(i=d_bins_;i<=u_bins_;i++){
          if(farsite[i-1]!=0){
          Sigma_wr=par[1]*farsite_DYB[i-1]/farsite[i-1]+par[2]*farsite_DYB[i-1]/farsite[i-1]+par[3]*farsite_LA[i-1]/farsite[i-1]+par[4]*farsite_LA[i-1]/farsite[i-1]+par[5]*farsite_LAII[i-1]/farsite[i-1]+par[6]*farsite_LAII[i-1]/farsite[i-1];
          delta=farsite0[i-1]-farsite[i-1]*(1+par[0]+0.99*0.5*Sigma_wr+par[i-d_bins_+40]+par[7]+par[A+7])-par[A+15]*farbkg_fastn[i-1]-par[A+23]*farbkg_acd[i-1]-par[A+31]*farbkg_li9[i-1];
          chisq+=delta*delta/(farsite[i-1]+0.003*0.003*farsite[i-1]*farsite[i-1]);
          }
       }
       chisq+=(par[A+7]/er_d)*(par[A+7]/er_d)+par[A+15]*par[A+15]/(er_F*er_F)+par[A+23]*par[A+23]/(er_N*er_N)+par[A+31]*par[A+31]/(er_S*er_S);
     }     
   }
   
   for(i=d_bins_;i<=u_bins_;i++){
     chisq+=par[40+i-d_bins_]*par[40+i-d_bins_]/(er_shp*er_shp);
   }
   
   for(r=1;r<=6;r++){
     chisq+=(par[r]/er_r)*(par[r]/er_r);
   }
   
   chisq+=par[0]*par[0]/(er_c*er_c)+par[7]*par[7]/(er_D*er_D);
   f=chisq;
}     



Double_t  minuit(){
   TMinuit *gMinuit=new TMinuit(u_bins_-d_bins_+1+40);   
   gMinuit->SetFCN(fcn);

   Double_t arglist[10]; 
   Int_t ierflg=0;
  
   arglist[0]=1;
   gMinuit->mnexcm("SET ERR",arglist,1,ierflg);   
   
   Double_t vstart=0.0;
   Double_t step=1.0e-8;

   TString s1;
   TString s2;
   TString s3;
   TString s4;
   s1=80;

   for(Int_t i=1;i<=u_bins_-d_bins_+1+40;i++){
    if(i<10){
    s2=48+i;
    gMinuit->mnparm(i-1,s1+s2,vstart,step,-1,1,ierflg);
    }
    if(i>=10&&i<100){
    s3=i%10+48;
    s2=(i-i%10)/10+48;
    gMinuit->mnparm(i-1,s1+s2+s3,vstart,step,-1,1,ierflg);
    }
    if(i>=100){
    Int_t a,b,c;
    a=i%10;
    b=(i-a)%100/10;
    c=(i-b*10-a)/100;
    s4=a+48;
    s3=b+48;
    s2=c+48;
    gMinuit->mnparm(i-1,s1+s2+s3+s4,vstart,step,-1,1,ierflg);
    }
   }

   arglist[0]=10000;
   gMinuit->mnexcm("MIGRAD",arglist,1,ierflg);
   if(ierflg==4){
     cout<<"MIGRAD ERROR!"<<endl;
     exit(0);
   }   
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

/*   Double_t parv;
   Double_t parerr;
   for(Int_t i=0;i<n_bins_+40;i++){
      gMinuit->GetParameter(i,parv,parerr);
      cout<<"p"<<i<<":"<<parv<<"   "<<parerr<<endl;
   }
*/
   return amin;
}

Double_t sens(Double_t s2_13,Double_t delta_m2,Double_t rundays){
   
   
   sp(s2_13,delta_m2,rundays,dybsite0,dybsite_DYB0,dybsite_LA0,dybsite_LAII0,lasite0,lasite_DYB0,lasite_LA0,lasite_LAII0,farsite0,farsite_DYB0,farsite_LA0,farsite_LAII0,dybbkg_li90,dybbkg_fastn0,dybbkg_acd0,labkg_li90,labkg_fastn0,labkg_acd0,farbkg_li90,farbkg_fastn0,farbkg_acd0);   

/*   TCanvas *b=new TCanvas("b","bkg",100,100,600,400);
   b->cd();
   Double_t sum1=0,sum2=0,sum3=0;
   hf=new TH1F("hf","bkg",n_bins_,1,10);
   for(Int_t i=1;i<=n_bins_;i++){
      hf->SetBinContent(i,dybbkg_li9[i-1]+dybbkg_fastn[i-1]+dybbkg_acd[i-1]);
      sum1+=dybbkg_li9[i-1];
      sum2+=dybbkg_fastn[i-1];
      sum3+=dybbkg_acd[i-1];
   }
   hf->Draw();
   cout<<"li9:"<<sum1<<endl;
   cout<<"fastn:"<<sum2<<endl;
   cout<<"acd:"<<sum3<<endl;
*/
   Double_t er=1e-06;
   Double_t a=s2_13,b=s2_13+0.01;
   Double_t Chisq;
    
   sp(b,delta_m2,rundays,dybsite,dybsite_DYB,dybsite_LA,dybsite_LAII,lasite,lasite_DYB,lasite_LA,lasite_LAII,farsite,farsite_DYB,farsite_LA,farsite_LAII,dybbkg_li9,dybbkg_fastn,dybbkg_acd,labkg_li9,labkg_fastn,labkg_acd,farbkg_li9,farbkg_fastn,farbkg_acd);
   Chisq=minuit();
   while(Chisq<2.71){
     b+=0.01;
     sp(b,delta_m2,rundays,dybsite,dybsite_DYB,dybsite_LA,dybsite_LAII,lasite,lasite_DYB,lasite_LA,lasite_LAII,farsite,farsite_DYB,farsite_LA,farsite_LAII,dybbkg_li9,dybbkg_fastn,dybbkg_acd,labkg_li9,labkg_fastn,labkg_acd,farbkg_li9,farbkg_fastn,farbkg_acd);
     Chisq=minuit();  
   }

   while(fabs(b-a)>er){     

     sp((a+b)/2.0,delta_m2,rundays,dybsite,dybsite_DYB,dybsite_LA,dybsite_LAII,lasite,lasite_DYB,lasite_LA,lasite_LAII,farsite,farsite_DYB,farsite_LA,farsite_LAII,dybbkg_li9,dybbkg_fastn,dybbkg_acd,labkg_li9,labkg_fastn,labkg_acd,farbkg_li9,farbkg_fastn,farbkg_acd);
     Chisq=minuit();
/*     cout<<"a:"<<a<<endl;
     cout<<"b:"<<b<<endl;
     cout<<"s2_13:"<<(a+b)/2.0<<endl; 
     cout<<"chisq:"<<Chisq<<endl;
     sleep(1);
*/
     if(Chisq>2.71){
       b=(a+b)/2.0;
     }
     if(Chisq<=2.71){
       a=(a+b)/2.0;
     }

   }
/* 
   Double_t s[20];
   Double_t c[20];
   Double_t t=a/2.0;
   Double_t dt=(b+0.01)/20.0;
   for(Int_t i=0;i<10;i++){
     sp(dybsite,dybsite_DYB,dybsite_LA,dybsite_LAII,lasite,lasite_DYB,lasite_LA,lasite_LAII,farsite,farsite_DYB,farsite_LA,farsite_LAII,t,delta_m2,dybbkg_li9,dybbkg_fastn,dybbkg_acd,labkg_li9,labkg_fastn,labkg_acd,farbkg_li9,farbkg_fastn,farbkg_acd);
     Chisq=minuit();  
     s[i]=t;
     c[i]=Chisq;
     t+=dt;
   }
     

   for(Int_t i=0;i<10;i++){
     cout<<s[i]<<"     "<<c[i]<<endl;
   }
*/
//  cout<<"sensitivity:"<<(a+b)/2.0<<endli;
  sleep(1);
  return (a+b)/2.0-s2_13;
}

void gsens(){

     spectrum();
     u_bins_=30;
     d_bins_=1;
/*
     Double_t b[20];
     Double_t sensitivity[20];
     for(Int_t i=0;i<20;i++)
     { 
        d_bins_=1+i;
        b[i]=1.8+8.2/n_bins_*(i+0.5);
        sensitivity[i]=sens(0.0,2.5e-3,900);      
     }
     for(Int_t i=0;i<20;i++)
     {
        cout<<b[i]<<"   "<<sensitivity[i]<<endl; 
     }
*/

/*
//     Double_t er=er_N;
     Double_t s1;
//     Double_t s2;
//     er_N=0.5*er;
     s1=sens(0.0,2.5e-3,900);
//     er_N=1.5*er;
//     s2=sens(0.0,2.5e-3,900);
     cout<<"   "<<s1<<endl;     
//     cout<<"  "<<(s2-s1)/er<<endl; 
*/
/*     
     Double_t sensitivity[7];
     Double_t f[7]={0.1,0.2,0.5,1,2,5,10};
     for(Int_t i=0;i<7;i++){
        factor=f[i];
        sensitivity[i]=sens(0.0,2.5e-3,900);
     }
     for(Int_t i=0;i<7;i++){
        cout<<f[i]<<"   "<<sensitivity[i]<<endl;
     }
*/

//       Double_t er[11]={0.001,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02};  
//       Double_t er[10]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
//     Double_t er[10]={0.00001,0.00002,0.0001,0.0002,0.0005,0.0006,0.0007,0.0008,0.0009,0.001};
     Double_t d[14]={0.1,0.2,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0};
//     Double_t d[20]={1,2,5,10,20,50,100,200,300,400,600,800,1000,1200,1400,1600,1800,2000,2200,2500};
//     Double_t m[20]={0.5,0.6,0.8,1,1.2,1.5,1.8,2,2.2,2.5,2.8,3,3.2,3.4,3.5,3.7,3.8,4,4.5,5};
     Double_t sensitivity[14];
     for(Int_t i=0;i<14;i++){     
//       sensitivity[i]=sens(2.5e-03,d[i]*300);
//       er_d=er[i];
       sensitivity[i]=sens(0.0,2.5e-03,d[i]*300);
     } 
     for(Int_t i=0;i<14;i++){
        cout<<d[i]<<"    "<<"sensitivity:"<<sensitivity[i]<<endl;
     }
/*
 FILE *fp;
 if((fp=fopen("bs224.TXT","a+"))==NULL)
 {
   printf("Cannot open this file!\n");
   exit(0);
 }
 for(Int_t i=0;i<10;i++){
   fprintf(fp,"%f",sensitivity[i]);
   fputs("\n",fp);
 }
 fclose(fp);
*/

     TCanvas *c1=new TCanvas("c1","sensitivity",100,100,1200,800);
     c1->cd();
     c1->SetGrid();
     TGraph *gr=new TGraph(14,d,sensitivity);
//     gr->SetName("Sensitivity vs Starting Energy");
     gr->SetLineColor(2);
     gr->SetLineWidth(2);
//     gr->GetXaxis()->SetTitle("Starting Energy (MeV)");
//     gr->GetYaxis()->SetTitle("Sensitivity (90% C.L.");
//     gr->GetXaxis()->SetTitle("#sigma_{d}");
//     gr->GetYaxis()->SetTitle("Sensitivity (90% C.L.");

     gr->GetXaxis()->SetTitle("Experiment time (yrs)");
     gr->GetYaxis()->SetTitle("Sensitivity (90% C.L.");
     gr->Draw("AL*P"); 

//   sp(0,2.5e-3,1,dybsite,dybsite_DYB,dybsite_LA,dybsite_LAII,lasite,lasite_DYB,lasite_LA,lasite_LAII,farsite,farsite_DYB,farsite_LA,farsite_LAII,dybbkg_li9,dybbkg_fastn,dybbkg_acd,labkg_li9,labkg_fastn,labkg_acd,farbkg_li9,farbkg_fastn,farbkg_acd);
}
