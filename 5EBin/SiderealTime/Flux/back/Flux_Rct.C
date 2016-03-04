
#include "math.h"
#include "TMatrixT.h"
#include "TMatrixTSym.h"
#include "TMatrixTLazy.h"
#include "TMatrixTCramerInv.h"
#include "TDecompLU.h"
#include "TMatrixDEigen.h"
#include "TClass.h"
#include "TMath.h"

Double_t Baseline(int AD,int Rct);//AD 1->8,Rct 1->6, in unit of meter

Double_t PositionRctX[6]={	359.2029,	448.0015,	-319.666,	-267.0633,	-543.284,	-490.6906};
Double_t PositionRctY[6]={	411.4896,	411.0017,	-540.7481,	-469.2051,	-954.7018,	-883.152};
Double_t PositionRctZ[6]={	-40.2308,	 -40.2392,	 -39.7296,	-39.723,	 -39.7987,	-39.7884};
Double_t PositionAdX[8]={	362.8329,	358.8044,	7.6518,		9.5968,		936.7486,	941.4493,	940.4612,	945.1678};
Double_t PositionAdY[8]={    50.4206,   54.8583,	-873.4882,  -879.149,	-1419.013,	-1415.305,  -1423.737,	-1420.0282};
Double_t PositionAdZ[8]={	-70.8174,	-70.8135,	-67.5241,	-67.5202,	-66.4852,	-66.4966,	-66.4965,	-66.4851};

void Flux_Rct()
{
	TMatrixT<double> L2(6,6);// = new *TMatrix(6,6);
	TMatrixT<double> UnitM(6,6);
	for(int AD=0;AD<6;AD++)
	{
		for(int Rct=0;Rct<6;Rct++)
		{
			L2(AD,Rct)= 1.0/pow(1e-3*Baseline(AD+1,Rct+1),2.0);
			cout<<L2(AD,Rct)<<"      ";//<<1e-3*Baseline(AD+1,Rct+1)<<"      ";
			if(AD==Rct)
			{
				UnitM(AD,Rct)=1.0;
			}
			else
			{
				UnitM(AD,Rct)=0.0;
			}
		}
		cout<<endl;
	}
	

	TMatrixT<double> L2_Inverse(6,6);

	L2_Inverse = operator+(UnitM,L2);
	for(int Rct = 0;Rct<6;Rct++)
	{
		for(AD=0;AD<6;AD++)
		{
			cout<<L2_Inverse(Rct,AD)<<"      ";
		}
		cout<<endl;
	}
}

Double_t Baseline(int AD,int Rct)//AD 1->8, Rct 1->6
{
	return pow(pow(PositionRctX[Rct-1]-PositionAdX[AD-1],2)+pow(PositionRctY[Rct-1]-PositionAdY[AD-1],2)+pow(PositionRctZ[Rct-1]-PositionAdZ[AD-1],2),0.5);
}
