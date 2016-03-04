
#include <ctime>
#include <cstdlib>

#include <math.h>
#include "TMinuit.h"

void MC_Test()
{
	TRandom *myRandom = new TRandom(unsigned(time(0)));
	TH1F *myTH1F1 = new TH1F("MCtest1","MCtest1",100.,-10.,10.);
	TH1F *myTH1F2 = new TH1F("MCtest2","MCtest2",100.,-10.,10.);
	TH1F *myTH1F3 = new TH1F("MCtest3","MCtest3",100.,-10.,10.);

	double v1,v2;
	for(int i=0;i<100000;i++)
	{
		v1 = myRandom->Gaus(1.0,0.4);
		v2 = myRandom->Gaus(1.0,0.3);
		myTH1F1->Fill(v1);
		myTH1F2->Fill(v2);
		myTH1F3->Fill(v1*v2);
	}

	myTH1F3->Draw();
}