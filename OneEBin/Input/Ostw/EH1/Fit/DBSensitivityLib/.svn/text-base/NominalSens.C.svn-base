void NominalSens()
{
  gSystem->Load("libDBSensitivityLib.so");
  
  ReactorCore *DBCore_1 = new ReactorCore();
  ReactorCore *DBCore_2 = new ReactorCore();
  ReactorCore *LACore1_1 = new ReactorCore();
  ReactorCore *LACore1_2 = new ReactorCore();
  ReactorCore *LACore2_1 = new ReactorCore();
  ReactorCore *LACore2_2 = new ReactorCore();
  
  double ntarget=7.31e28*20;//number (per ton) from Doc-2546
  double livetimefactor=(300./365.);//because we assume 300 'live' days per year - this makes a livetime fraction of about 0.82 which matches a calculation in Doc-2546
  double timeinyears = 3.;
  
  Detector *NearDB_1 = new Detector("NearDB_1");
  NearDB_1->AddCore(DBCore_1,370.1.,timeinyears*livetimefactor);
  NearDB_1->AddCore(DBCore_2,360.7.,timeinyears*livetimefactor);
  NearDB_1->AddCore(LACore1_1,814.0,timeinyears*livetimefactor);
  NearDB_1->AddCore(LACore1_2,900.4,timeinyears*livetimefactor);
  NearDB_1->AddCore(LACore2_1,1262.4,timeinyears*livetimefactor);
  NearDB_1->AddCore(LACore2_2,1350.7,timeinyears*livetimefactor);
  NearDB_1->SetSigma_s(0.003);
  NearDB_1->SetEfficiency(0.609);
  NearDB_1->SetNtargetnuclei(ntarget);
  
  Detector *NearDB_2 = new Detector("NearDB_2");
  NearDB_2->AddCore(DBCore_1,366.7,timeinyears*livetimefactor);
  NearDB_2->AddCore(DBCore_2,356.2,timeinyears*livetimefactor);
  NearDB_2->AddCore(LACore1_1,813.7,timeinyears*livetimefactor);
  NearDB_2->AddCore(LACore1_2,900.3,timeinyears*livetimefactor);
  NearDB_2->AddCore(LACore2_1,1263.0,timeinyears*livetimefactor);
  NearDB_2->AddCore(LACore2_2,1351.4,timeinyears*livetimefactor);
  NearDB_2->SetSigma_s(0.003);
  NearDB_2->SetEfficiency(0.609);
  NearDB_2->SetNtargetnuclei(ntarget);
  
  Detector *NearLA_1 = new Detector("NearLA_1");
  NearLA_1->AddCore(DBCore_1,1362.7,timeinyears*livetimefactor);
  NearLA_1->AddCore(DBCore_2,1337.2,timeinyears*livetimefactor);
  NearLA_1->AddCore(LACore1_1,495.3,timeinyears*livetimefactor);
  NearLA_1->AddCore(LACore1_2,472.4,timeinyears*livetimefactor);
  NearLA_1->AddCore(LACore2_1,498.4,timeinyears*livetimefactor);
  NearLA_1->AddCore(LACore2_2,555.9,timeinyears*livetimefactor);
  NearLA_1->SetSigma_s(0.003);
  NearLA_1->SetEfficiency(0.690);
  NearLA_1->SetNtargetnuclei(ntarget);
  
  Detector *NearLA_2 = new Detector("NearLA_2");
  NearLA_2->AddCore(DBCore_1,1357.9,timeinyears*livetimefactor);
  NearLA_2->AddCore(DBCore_2,1332.2,timeinyears*livetimefactor);
  NearLA_2->AddCore(LACore1_1,489.5,timeinyears*livetimefactor);
  NearLA_2->AddCore(LACore1_2,467.0,timeinyears*livetimefactor);
  NearLA_2->AddCore(LACore2_1,496.6,timeinyears*livetimefactor);
  NearLA_2->AddCore(LACore2_2,554.8,timeinyears*livetimefactor);
  NearLA_2->SetSigma_s(0.003);
  NearLA_2->SetEfficiency(0.690);
  NearLA_2->SetNtargetnuclei(ntarget);
  
  Detector *Far_1 = new Detector("Far_1");
  Far_1->AddCore(DBCore_1,1974.4,timeinyears*livetimefactor);
  Far_1->AddCore(DBCore_2,2001.5,timeinyears*livetimefactor);
  Far_1->AddCore(LACore1_1,1622.8,timeinyears*livetimefactor);
  Far_1->AddCore(LACore1_2,1621.3,timeinyears*livetimefactor);
  Far_1->AddCore(LACore2_1,1605.4,timeinyears*livetimefactor);
  Far_1->AddCore(LACore2_2,1629.5,timeinyears*livetimefactor);
  Far_1->SetSigma_s(0.001);
  Far_1->SetNtargetnuclei(ntarget);
  Far_1->SetEfficiency(0.804);
  
  Detector *Far_2 = new Detector("Far_2");
  Far_2->AddCore(DBCore_1,1976.7,timeinyears*livetimefactor);
  Far_2->AddCore(DBCore_2,2003.6,timeinyears*livetimefactor);
  Far_2->AddCore(LACore1_1,1621.5,timeinyears*livetimefactor);
  Far_2->AddCore(LACore1_2,1619.7,timeinyears*livetimefactor);
  Far_2->AddCore(LACore2_1,1602.5,timeinyears*livetimefactor);
  Far_2->AddCore(LACore2_2,1626.3,timeinyears*livetimefactor);
  Far_2->SetSigma_s(0.001);
  Far_2->SetNtargetnuclei(ntarget);
  Far_2->SetEfficiency(0.804);
  
  Detector *Far_3 = new Detector("Far_3");
  Far_3->AddCore(DBCore_1,1968.9,timeinyears*livetimefactor);
  Far_3->AddCore(DBCore_2,1995.9,timeinyears*livetimefactor);
  Far_3->AddCore(LACore1_1,1616.9,timeinyears*livetimefactor);
  Far_3->AddCore(LACore1_2,1615.5,timeinyears*livetimefactor);
  Far_3->AddCore(LACore2_1,1600.2,timeinyears*livetimefactor);
  Far_3->AddCore(LACore2_2,1624.4,timeinyears*livetimefactor);
  Far_3->SetSigma_s(0.001);
  Far_3->SetNtargetnuclei(ntarget);
  Far_3->SetEfficiency(0.804);
  
  Detector *Far_4 = new Detector("Far_4");
  Far_4->AddCore(DBCore_1,1971.2,timeinyears*livetimefactor);
  Far_4->AddCore(DBCore_2,1997.9,timeinyears*livetimefactor);
  Far_4->AddCore(LACore1_1,1615.7,timeinyears*livetimefactor);
  Far_4->AddCore(LACore1_2,1614.0,timeinyears*livetimefactor);
  Far_4->AddCore(LACore2_1,1597.2,timeinyears*livetimefactor);
  Far_4->AddCore(LACore2_2,1621.2,timeinyears*livetimefactor);
  Far_4->SetSigma_s(0.001);
  Far_4->SetNtargetnuclei(ntarget);
  Far_4->SetEfficiency(0.804);
  
  Experiment *DB = new Experiment();
  DB->AddDetector(NearDB_1);
  DB->AddDetector(NearDB_2);
  DB->AddDetector(NearLA_1);
  DB->AddDetector(NearLA_2);
  DB->AddDetector(Far_1);
  DB->AddDetector(Far_2);
  DB->AddDetector(Far_3);
  DB->AddDetector(Far_4);
  
  DB->MakeSensitivityPlot(0.008,"NominalSens");
  
  return;

}
