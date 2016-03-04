double CapT(double *x,double *par)
{
  double N     = par[0];
  double Alpha = par[1];
  double LCap  = par[2];
  double LGen  = par[3];
  double FlatB = par[4];

  double t = x[0];

  double NDensity = N*( (1+Alpha)*LCap*exp(-LCap*t) - Alpha*LGen*exp(-LGen*t) ) + FlatB;

  return NDensity;
}
