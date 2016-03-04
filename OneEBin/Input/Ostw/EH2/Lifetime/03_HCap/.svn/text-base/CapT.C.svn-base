double CapT(double *x,double *par)
{
  double N     = par[0];
  double LCap  = par[1];
  double FlatB = par[2];

  double t = x[0];

  double NDensity = N * LCap * exp(-LCap*t) + FlatB;

  return NDensity;
}
