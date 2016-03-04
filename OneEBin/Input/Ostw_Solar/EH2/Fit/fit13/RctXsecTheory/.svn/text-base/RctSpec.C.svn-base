#include "RctSpec.h"
#include "Crosssection.h"
#include "Tool/Table.h"
#include <stdlib.h>

RctSpec* gU238  = new RctSpec( Reactor::U238SpecFile,  "U238"  );
RctSpec* gU235  = new RctSpec( Reactor::U235SpecFile,  "U235"  );
RctSpec* gPu239 = new RctSpec( Reactor::Pu239SpecFile, "Pu239" );
RctSpec* gPu241 = new RctSpec( Reactor::Pu241SpecFile, "Pu241" );

TH1F* gU238X  = new TH1F( "U238X ", "U238  x crosssection", Binning::NPreciseBin, Binning::BeginEnergy, Binning::EndEnergy );
TH1F* gU235X  = new TH1F( "U235X ", "U235  x crosssection", Binning::NPreciseBin, Binning::BeginEnergy, Binning::EndEnergy );
TH1F* gPu239X = new TH1F( "Pu239X", "Pu239 x crosssection", Binning::NPreciseBin, Binning::BeginEnergy, Binning::EndEnergy );
TH1F* gPu241X = new TH1F( "Pu241X", "Pu241 x crosssection", Binning::NPreciseBin, Binning::BeginEnergy, Binning::EndEnergy );

void RctSpec::SetDataFile(std::string DataFile)
{
  mDataFile = DataFile;
  
  Table data(mDataFile);
  
  /* The first 1.8 MeV. */
  for(unsigned int bin=1; bin<=180; bin++ )   {
    SetBinContent( bin, 0 );
  }
  
  /* The rest 820 bins. */
  for(unsigned int row=1; row<=820; row++ )   {
    double yield = atof( data.Columns["Yield"][row].c_str() );
    SetBinContent( 180+row, yield );
  }
}

void RctSpec::SetNameTitle(const char* name, const char* title)
{
  this->SetName(name);
  this->SetTitle(title);
}
