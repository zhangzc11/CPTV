void CheckRate()
{
  gSystem->Load("lib/libDBSensitivityLib.so");
  
  ReactorCore *Core = new ReactorCore();
  Core->SetExpectedPower(1.0);
  double ntarget=7.31e28;//number from Christine's Doc-2546
  cout<<ntarget<<" target nuclei"<<endl;
  Detector *Det = new Detector("Det");
  Det->SetNtargetnuclei(ntarget);
  Det->SetEfficiency(1.0);
  Det->AddCore(Core,1000,1./365.25);
  cout<<Det->PromptSpectrum->Integral()<<" antinus per day per GW per ton at 1 km (100% eff)"<<endl;
  cout<<"TDR gives 1"<<endl;
  cout<<endl;
  
  ReactorCore *DBCore_1 = new ReactorCore();
  ReactorCore *DBCore_2 = new ReactorCore();
  ReactorCore *LACore1_1 = new ReactorCore();
  ReactorCore *LACore1_2 = new ReactorCore();
  ReactorCore *LACore2_1 = new ReactorCore();
  ReactorCore *LACore2_2 = new ReactorCore();
  
  ntarget = 7.31e28*20;//takes in targets/20 tons
  double livetimefactor = 1;//assume live time the whole day
  double timeinyears = 1./365.25;
  
  Detector *NearDB_1 = new Detector("NearDB_1");
  NearDB_1->AddCore(DBCore_1,364.,livetimefactor*timeinyears);
  NearDB_1->AddCore(DBCore_2,364.,livetimefactor*timeinyears);
  NearDB_1->AddCore(LACore1_1,857.,livetimefactor*timeinyears);
  NearDB_1->AddCore(LACore1_2,857.,livetimefactor*timeinyears);
  NearDB_1->AddCore(LACore2_1,1307.,livetimefactor*timeinyears);
  NearDB_1->AddCore(LACore2_2,1307.,livetimefactor*timeinyears);
  NearDB_1->SetEfficiency(0.81);
  NearDB_1->SetNtargetnuclei(ntarget);
  
  cout<<NearDB_1->PromptSpectrum->Integral()<<" antinu interactions per day per module at Daya Bay site"<<endl;
  
  Detector *NearLA_1 = new Detector("NearLA_1");
  NearLA_1->AddCore(DBCore_1,1347.,livetimefactor*timeinyears);
  NearLA_1->AddCore(DBCore_2,1347.,livetimefactor*timeinyears);
  NearLA_1->AddCore(LACore1_1,481.,livetimefactor*timeinyears);
  NearLA_1->AddCore(LACore1_2,481.,livetimefactor*timeinyears);
  NearLA_1->AddCore(LACore2_1,526.,livetimefactor*timeinyears);
  NearLA_1->AddCore(LACore2_2,526.,livetimefactor*timeinyears);
  NearLA_1->SetEfficiency(0.81);
  NearLA_1->SetNtargetnuclei(ntarget);
  
  cout<<NearLA_1->PromptSpectrum->Integral()<<" antinu interactions per day per module at Ling Ao site"<<endl;
  
  Detector *Far_1 = new Detector("Far_1");
  Far_1->AddCore(DBCore_1,1985.,livetimefactor*timeinyears);
  Far_1->AddCore(DBCore_2,1985.,livetimefactor*timeinyears);
  Far_1->AddCore(LACore1_1,1618.,livetimefactor*timeinyears);
  Far_1->AddCore(LACore1_2,1618.,livetimefactor*timeinyears);
  Far_1->AddCore(LACore2_1,1613.,livetimefactor*timeinyears);
  Far_1->AddCore(LACore2_2,1613.,livetimefactor*timeinyears);
  Far_1->SetNtargetnuclei(ntarget);
  Far_1->SetEfficiency(0.81);
  
  cout<<Far_1->PromptSpectrum->Integral()<<" antinu interactions per day per module at Far site"<<endl;
  
  cout<<"Official numbers are 840, 740, and 90"<<endl;
  
  return;
}
