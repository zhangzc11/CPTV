double CBShape(double *x,double *par)
{
  double N     = par[0];
  double mean  = par[1];
  double sigma = par[2];
  double a     = par[3];
  double n     = par[4];

  double e = x[0];
  a = abs(a);

  double pdf = 0;
  if( (e-mean)/sigma > -a )  {
    pdf = exp( - 1/2.0*pow((e-mean)/sigma,2) );
  } else {
    pdf = pow(n/a,n)*exp(-1/2.0*a*a) / pow(n/a-a-(e-mean)/sigma,n);
  }

  return N*pdf;
}
