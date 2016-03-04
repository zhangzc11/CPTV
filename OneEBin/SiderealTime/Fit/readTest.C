

void readTest()
{

cout<<"hello..."<<endl;
 
TFile *f_Tsinghua = new TFile("Final_Tsinghua.root");
TFile *f_Houston = new TFile("Final_Houston.root");

TH1D *h_EH1_Tsinghua = (TH1D*)f_Tsinghua->Get("hEH1");
TH1D *h_EH2_Tsinghua = (TH1D*)f_Tsinghua->Get("hEH2");
TH1D *h_EH3_Tsinghua = (TH1D*)f_Tsinghua->Get("hEH3");


TH1D *h_EH1_Houston = (TH1D*)f_Houston->Get("hEH1");
TH1D *h_EH2_Houston = (TH1D*)f_Houston->Get("hEH2");
TH1D *h_EH3_Houston = (TH1D*)f_Houston->Get("hEH3");

h_EH1_Tsinghua->Draw();


cout<<h_EH1_Tsinghua->GetBinContent(2)<<endl;
cout<<h_EH1_Tsinghua->GetBinError(2)<<endl;

}
