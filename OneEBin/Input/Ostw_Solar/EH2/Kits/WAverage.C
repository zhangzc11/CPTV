double WAverage()
{
  double a, ea, wa;
  double b, eb, wb;
  
  a = 0.087;
  ea = 0.010;

  b = 0.088;
  eb = 0.011;

  wa = 1/(ea*ea);
  wb = 1/(eb*eb);

  double ave = ( a * wa + b * wb )/( wa + wb );

  double err = sqrt( 1/(wa + wb) );
 
  cout << ave <<"+/-"<< err <<endl;

  return 1;
}
