
void FFTTest()
{
	Int_t N = 30; 
	Double_t in[30] ={1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2,1.0,1.2};
	
	TVirtualFFT *fftr2c = TVirtualFFT::FFT(1, &N, "R2C");
	fftr2c->SetPoints(in);
	fftr2c->Transform();

	Double_t re, im,rin,rout;
	Int_t row;

	TFile *f = new TFile("FFT.root","recreate");
	TTree *FFTtree = new TTree("FFTtree","FFT tree");
	FFTtree->Branch("input",&rin,"rin/D");
	FFTtree->Branch("output",&rout,"rout/D");
	FFTtree->Branch("row",&row,"row/I");

	for (Int_t i=0; i<N; i++)
	{
		fftr2c->GetPointComplex(i, re, im);
		rout=sqrt(pow(re,2)+pow(im,2));
		cout<<rout<<endl;
		rin=in[i];
		row=i;
		FFTtree->Fill();		
	}	
	FFTtree->Write();
	
	TCanvas *myC1 = new TCanvas("Input","Input",10,10,800,600);
	FFTtree->SetMarkerStyle(20);
	FFTtree->Draw("input:row");
	TCanvas *myC2 = new TCanvas("Output","Output",10,10,800,600);
	FFTtree->Draw("output:row");
	
	
}
