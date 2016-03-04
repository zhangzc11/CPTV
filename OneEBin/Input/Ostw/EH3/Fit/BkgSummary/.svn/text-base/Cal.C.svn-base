{
  double OstwEff[6] = {0.9840, 0.9842, 0.9846, 0.9835, 0.9832, 0.9831};

  {
    /// Fast neutron -- Start from number of background with all nominal 2.2 MeV cut
    double Bkg[6] = { 0.96, 0.96, 0.68, 0.06, 0.06, 0.06 };
    double Err[6] = { 0.51, 0.51, 0.35, 0.04, 0.04, 0.04 };

    cout.precision(2);
    cout<<fixed;
    for( int ad=0; ad<6; ad++ ) {
      cout<< "$"<<Bkg[ad]/OstwEff[ad] << "\\pm" << Err[ad]/OstwEff[ad] <<"$ & ";
    }
    cout<<endl;
  }

  /// Calculate the real background number used in the fit
  {
    //// Li9 -- Start from the real daily yield
    double Bkg[6] = { 3.35, 3.35, 4.28, 0.76, 0.76, 0.76 };
    double Err[6] = { 0.77, 0.77, 2.12, 0.15, 0.15, 0.15 };

    double eff = 0.7*0.7*0.8843;

    cout.precision(2);
    cout<<fixed;
    for( int ad=0; ad<6; ad++ ) {
      cout<< "$"<<Bkg[ad]*eff << "\\pm" << Err[ad]*eff <<"$ & ";
    }
    cout<<endl;

    cout<< 3.75*eff<<" "<<1.15*eff<<endl;
  }

  {
    /// Am-C -- Start from number of background with all nominal 2.2 MeV cut
    double Bkg[6] = { 0.10, 0.10, 0.10, 0.08, 0.08, 0.08 };
    double Err[6] = { 0.03, 0.03, 0.03, 0.02, 0.02, 0.02 };

    cout.precision(2);
    cout<<fixed;
    for( int ad=0; ad<6; ad++ ) {
      cout<< "$"<<Bkg[ad]/OstwEff[ad] << "\\pm" << Err[ad]/OstwEff[ad] <<"$ & ";
    }
    cout<<endl;
  }
}
