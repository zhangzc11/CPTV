{
  gROOT->ProcessLine(".L GenHistoNoVtx.C+");
  GenHisto( "MCNoVtx.list", 0 );
}
