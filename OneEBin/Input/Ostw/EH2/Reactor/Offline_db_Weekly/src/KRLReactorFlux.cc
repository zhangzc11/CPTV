#include "KRLReactorFlux.hh"

#include "genDbi/GReactor.h"

#include "Conventions/Site.h"
#include "Conventions/SimFlag.h"
#include "Context/TimeStamp.h"
#include "Context/ServiceMode.h"

#include "DatabaseInterface/Dbi.h"
#include "DatabaseInterface/DbiResultAgg.h"
#include "DatabaseInterface/DbiCascader.h"
#include "DatabaseInterface/DbiConfigSet.h"
#include "DatabaseInterface/DbiLogEntry.h"
#include "DatabaseInterface/DbiResultKey.h"
#include "DatabaseInterface/DbiResultNonAgg.h"
#include "DatabaseInterface/DbiResultPtr.h"
#include "DatabaseInterface/DbiResultSet.h"
#include "DatabaseInterface/DbiServices.h"
#include "DatabaseInterface/DbiValRecSet.h"
#include "DatabaseInterface/DbiLog.h"
#include "DatabaseInterface/DbiCache.h"
#include "DatabaseInterface/DbiSqlContext.h"
 
#include <iostream>
#include <math.h> 
using namespace ROOT;

KRLReactorFlux* gReactorFlux;

KRLReactorFlux::KRLReactorFlux() {
}

void KRLReactorFlux::SetContext(){
  TimeStamp timeStamp(fTime);
  Context context;
  context.SetSite(Site::kAll);
  context.SetSimFlag(SimFlag::kData);
  context.SetTimeStamp(timeStamp);
  int task = 0;
  ServiceMode svcMode(context, task);
  readReactorTable(svcMode);
}

int KRLReactorFlux::readReactorTable(const ServiceMode& serviceMode) {
  if(serviceMode.context() == fluxLastContext){
    return 2;    
  }
  fluxLastContext = serviceMode.context(); 
  
  DbiResultPtr<GReactor> pr("Reactor", fluxLastContext);
  // Check whether the result is the same as the last one
  const DbiResultKey* thisResult= pr.GetKey(); 
  if(fluxLastResult == 0)  {          
    fluxLastResult = thisResult;
    //  }else if(thisResult->IsEqualTo(fluxLastResult))  {
    //    return 2;
  }else{
    fluxLastResult = thisResult;
  }

  // Check number of entires in result set
  unsigned int numRows = pr.GetNumRows();

  const GReactor* row ;
  
  int ReactorID = 0;
  int Quality = 0;
  for (unsigned int idx=0; idx < numRows; idx++) {
    row = pr.GetRowByIndex(idx);

    if(row->GetReactorId() == 1) ReactorID = 0;
    if(row->GetReactorId() == 2) ReactorID = 1;
    if(row->GetReactorId() == 4) ReactorID = 2;
    if(row->GetReactorId() == 8) ReactorID = 3;
    if(row->GetReactorId() == 16) ReactorID = 4;
    if(row->GetReactorId() == 32) ReactorID = 5;

    Quality = row->GetQuality();
    if(Quality == 0) {
      for(int i = 0; i < 33; i++) {
        fEPointsFlux[ReactorID][i] = 0.;
      }
    }
    else {
      fEPointsFlux[ReactorID][0] = row->GetSpec_1500keV();
      fEPointsFlux[ReactorID][1] = row->GetSpec_1750keV();
      fEPointsFlux[ReactorID][2] = row->GetSpec_2000keV();
      fEPointsFlux[ReactorID][3] = row->GetSpec_2250keV();
      fEPointsFlux[ReactorID][4] = row->GetSpec_2500keV();
      fEPointsFlux[ReactorID][5] = row->GetSpec_2750keV();
      fEPointsFlux[ReactorID][6] = row->GetSpec_3000keV();
      fEPointsFlux[ReactorID][7] = row->GetSpec_3250keV();
      fEPointsFlux[ReactorID][8] = row->GetSpec_3500keV();
      fEPointsFlux[ReactorID][9] = row->GetSpec_3750keV();
      fEPointsFlux[ReactorID][10] = row->GetSpec_4000keV();
      fEPointsFlux[ReactorID][11] = row->GetSpec_4250keV();
      fEPointsFlux[ReactorID][12] = row->GetSpec_4500keV();
      fEPointsFlux[ReactorID][13] = row->GetSpec_4750keV();
      fEPointsFlux[ReactorID][14] = row->GetSpec_5000keV();
      fEPointsFlux[ReactorID][15] = row->GetSpec_5250keV();
      fEPointsFlux[ReactorID][16] = row->GetSpec_5500keV();
      fEPointsFlux[ReactorID][17] = row->GetSpec_5750keV();
      fEPointsFlux[ReactorID][18] = row->GetSpec_6000keV();
      fEPointsFlux[ReactorID][19] = row->GetSpec_6250keV();
      fEPointsFlux[ReactorID][20] = row->GetSpec_6500keV();
      fEPointsFlux[ReactorID][21] = row->GetSpec_6750keV();
      fEPointsFlux[ReactorID][22] = row->GetSpec_7000keV();
      fEPointsFlux[ReactorID][23] = row->GetSpec_7250keV();
      fEPointsFlux[ReactorID][24] = row->GetSpec_7500keV();
      fEPointsFlux[ReactorID][25] = row->GetSpec_7750keV();
      fEPointsFlux[ReactorID][26] = row->GetSpec_8000keV();
      fEPointsFlux[ReactorID][27] = row->GetSpec_8250keV();
      fEPointsFlux[ReactorID][28] = row->GetSpec_8500keV();
      fEPointsFlux[ReactorID][29] = row->GetSpec_8750keV();
      fEPointsFlux[ReactorID][30] = row->GetSpec_9000keV();
      fEPointsFlux[ReactorID][31] = row->GetSpec_9250keV();
      fEPointsFlux[ReactorID][32] = row->GetSpec_9500keV();
      fTotalNumber[ReactorID]     = row->GetTotalNumber();
    }
  }
  
  return 1;
}

