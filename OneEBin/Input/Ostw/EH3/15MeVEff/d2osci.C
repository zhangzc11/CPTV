{
  TF1 *neutrino_f=new TF1("neutrino_f","0.58*exp(0.870-0.160*x-0.0910*x*x)+0.3*exp(0.896-0.239*x-0.0981*x*x)+0.07*exp(0.976-0.162*x-0.0790*x*x)+0.05*exp(0.793-0.080*x-0.1085*x*x)",0,12);
  
  TFormula *positron_m=new TFormula("positron_m","sqrt((x-1.2933)*(x-1.2933)-0.511*0.511)");
  
  TF1 *cross_section=new TF1("cross_section","0.0952*(x-1.2933)*positron_m",1.5,8);
  
  TF1 *neutrino_sp=new TF1("neutrino_sp","neutrino_f*cross_section",1.5,8);


  double t13=0.152;  // 8.7 degree
  double t12=0.586;  // 33.6 degree
  double d21=7.58e-5; 
  double d31=2.35e-3; 
  double L=58000;

  TFormula * firstDis = new TFormula("firstDis","cos([0])**4 * sin(2*[1])**2 * sin(1.267*[2]*[3]/x)**2");
  firstDis->SetParameter(0,t13);
  firstDis->SetParameter(1,t12);
  firstDis->SetParameter(2,d21);
  firstDis->SetParameter(3,L);

  TF1 *first = new TF1("first","neutrino_sp*firstDis",1.5,8);

  TFormula * secondDis = new TFormula("secondDis","sin(2*[0])**2 * sin(1.267*[1]*[2]/x)**2");
  secondDis->SetParameter(0,t13);
  secondDis->SetParameter(1,d31);
  secondDis->SetParameter(2,L);

  TF1 *second = new TF1("second","neutrino_sp*secondDis",1.5,8);

  TFormula * thirdDis = new TFormula("thirdDis",  "sin(2*[0])**2 * sin([1])**2 * sin(1.267*(2*[2]-[3])*[4]/x) * sin(-1.267*[3]*[4]/x)");
  // TFormula * thirdDis = new TFormula("thirdDis",  "sin(2*[0])**2 * sin([1])**2 * sin(1.267*(4.63e-3)*[4]/x) * sin(-1.267*[3]*[4]/x)");
  thirdDis->SetParameter(0,t13);
  thirdDis->SetParameter(1,t12);
  thirdDis->SetParameter(2,d31);
  thirdDis->SetParameter(3,d21);
  thirdDis->SetParameter(4,L);

  TF1 *third = new TF1("third","neutrino_sp*thirdDis",1.5,8);


  TFormula * thirdIDis = new TFormula("thirdIDis","sin(2*[0])**2 * sin([1])**2 * sin(1.267*(2*[2]-[3])*[4]/x) * sin(-1.267*[3]*[4]/x)");
  // TFormula * thirdIDis = new TFormula("thirdIDis","sin(2*[0])**2 * sin([1])**2 * sin(1.267*(-4.77e-3)*[4]/x) * sin(-1.267*[3]*[4]/x)");
  thirdIDis->SetParameter(0,t13);
  thirdIDis->SetParameter(1,t12);
  thirdIDis->SetParameter(2,-d31);
  thirdIDis->SetParameter(3,d21);
  thirdIDis->SetParameter(4,L);

  TF1 *thirdI = new TF1("thirdI","neutrino_sp*thirdIDis",1.5,8);

  TF1* nh = new TF1("nh","neutrino_sp*(1-firstDis-secondDis-thirdDis)",1.5,8);
  nh->SetNpx(100000);

  TF1* ih = new TF1("nh","neutrino_sp*(1-firstDis-secondDis-thirdIDis)",1.5,8);
  ih->SetNpx(100000);

  first.Draw();
  second.SetNpx(100000);
  second.Draw("same");
  third.SetNpx(100000);
  third.Draw("same");

  TLegend leg(0.1,0.7,0.48,0.9);
  leg.AddEntry(first,"first");
  leg.AddEntry(second,"second");
  leg.AddEntry(third,"third");
  leg.Draw();
}

