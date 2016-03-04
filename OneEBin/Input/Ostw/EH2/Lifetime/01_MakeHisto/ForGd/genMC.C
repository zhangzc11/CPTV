{
  gROOT->ProcessLine(".L GenHisto.C+");
  GenHisto( "MC.list", 0 );
}
