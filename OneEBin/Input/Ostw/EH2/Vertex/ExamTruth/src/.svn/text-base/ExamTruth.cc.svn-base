/**
 * Check IBD sample
 *
 * Jun 4, 2012 created by Zhe Wang
 */
#include "ExamTruth.h"

#include "CLHEP/Units/SystemOfUnits.h"
#include "DetDesc/Material.h"
// for SimHit
#include "Event/SimHitHeader.h"
#include "Event/SimHitCollection.h"
#include "Event/SimPmtHit.h"
#include "Event/SimHit.h"
// for history info
//#include "Event/SimParticleHistoryHeader.h"
#include "Event/SimParticleHistory.h"
#include "Event/SimUnobservableStatisticsHeader.h"
#include "Event/SimStatistic.h"
// for RecHeader
#include "Event/RecHeader.h"

using namespace std;
using namespace DayaBay;

ExamTruth::ExamTruth(const std::string& name, ISvcLocator* pSvcLocator):
  GaudiAlgorithm(name, pSvcLocator)
{
  declareProperty("RootFile", mRootFile = "test.TWin.root", "Output root file name");
  declareProperty("XYZCorr",  Corr = 0, "By default no correction");

  mRZCorr = new RZCorr;
  mXYCorr = new XYCorr;
}

ExamTruth::~ExamTruth()
{
}

StatusCode ExamTruth::initialize()
{
  mDetSimCycle = -1;
  mTree = new EventTree( "Event", mRootFile.c_str(), 0);

  m_dbOil1 = getDet<IDetectorElement>("/dd/Structure/AD/db-oil1");
  m_dbLso1 = getDet<IDetectorElement>("/dd/Structure/AD/db-lso1");


  this->GaudiAlgorithm::initialize();
  return StatusCode::SUCCESS;
}

StatusCode ExamTruth::execute()
{
  /// The reconstructed info
  /// ----------------------
  /* AdSimple has been tried. The grid structure is too obvious. */
  RecHeader* pRecHeader = get<RecHeader>( "/Event/Rec/AdScaled" );
  if(!pRecHeader) {
    error()<<"Failed to get RecHeader"<<endreq;
    return StatusCode::FAILURE;
  }

  /// Get RecTrigger
  const RecTrigger* pRecTrigger = &(pRecHeader->recTrigger());
  if(!pRecTrigger) {
    error()<<"Failed to get RecTrigger"<<endreq;
    return StatusCode::FAILURE;
  }

  /// Trigger time
  TimeStamp TrigTime ( pRecTrigger->triggerTime().GetSec(), pRecTrigger->triggerTime().GetNanoSec() );
  double E = pRecTrigger->energy();
  double recX = pRecTrigger->position().x();
  double recY = pRecTrigger->position().y();
  double recZ = pRecTrigger->position().z();

  double X,Y,Z,R2;

  double recR2 = pow(recX,2)+pow(recY,2);

  if( Corr ) {
    //mXYCorr->Correct( recX, recY, X, Y );
    X = recX;
    Y = recY;
    mRZCorr->Correct( recZ, recR2, Z, R2 );
  } else {
    X = recX;
    Y = recY;
    Z = recZ;
    R2 = recR2;
  }

  /// Find its MC truth info
  /// ----------------------
  const vector<const IHeader*> IList = pRecHeader->findHeaders( SimHeader::classID() );
  if( IList.size() == 0 )  {
    warning()<<"Failed to get its corresponding SimHeaders. Skipped."<<endreq;
    return StatusCode::SUCCESS;
  }
  if( IList.size() >= 2 )  {
    warning()<<"Get more than 1 SimHeaders. Skipped to avoid ambiguity."<<endreq;
    return StatusCode::SUCCESS;
  }
  /// Get the only one SimHeader
  const SimHeader* pSimHeader = dynamic_cast<const SimHeader*>( *(IList.begin()) );
  int ThisSimCycle = pSimHeader->execNumber();
  info()<<ThisSimCycle<<endreq;

  //Get UnObservable Statistics info
  const DayaBay::SimUnobservableStatisticsHeader* pUnobs =
    pSimHeader->unobservableStatistics();
  const DayaBay::SimUnobservableStatisticsHeader::stat_map&
    statmap = pUnobs->stats();
  DayaBay::SimUnobservableStatisticsHeader::stat_map::const_iterator
    st, stdone = statmap.end();

  /// Find tCap
  /// ---------
  double tCap;  /* in ns */
  double xCap, yCap, zCap, capTarget;
  
  /// Positron info
  int pdgId_Trk1;
  double x_Trk1, y_Trk1, z_Trk1, e_Trk1;

  if( !pUnobs ) {
    warning()<<"Failed to get SimParticleHistory. Skipped."<<endreq;
    return StatusCode::SUCCESS;

  } else {
    
    /// About neutron capture
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="tCap")   tCap = st->second.sum();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="xCap")   xCap = st->second.sum();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="yCap")   yCap = st->second.sum();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="zCap")   zCap = st->second.sum();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="capTarget")   capTarget = st->second.sum();
    }

    /// About positron initial info
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="pdgId_Trk1")   pdgId_Trk1 = (int)st->second.sum();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="e_Trk1")   e_Trk1 = st->second.sum();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="x_Trk1")   x_Trk1 = st->second.sum();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="y_Trk1")   y_Trk1 = st->second.sum();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="z_Trk1")   z_Trk1 = st->second.sum();
    }

  }

  /// Just confirm track 1 is positron
  if( pdgId_Trk1 != -11 )  {
    warning()<<"Track 1 is not positron. Can't get positron truth. Skipped."<<endreq;
    return StatusCode::SUCCESS;
  }

  /// Truth vertex transformation to local cooridinates.
  Gaudi::XYZPoint GblGen( x_Trk1, y_Trk1, z_Trk1 );
  Gaudi::XYZPoint LclGen = m_dbOil1->geometry()->toLocal( GblGen );

  Gaudi::XYZPoint GblCap( xCap, yCap, zCap );
  Gaudi::XYZPoint LclCap = m_dbOil1->geometry()->toLocal( GblCap );

  /// CapT and GenT
  TimeStamp GenT = pSimHeader->timeStamp();          /* Abs generation time */
  TimeStamp CapT = GenT;  CapT.Add(tCap/1e9);        /* Abs capture time    */

  static int lastSim=-1;
  if( tCap < 1e3 )  {
    int Sim = pSimHeader->execNumber();
    if( Sim != lastSim ) {
      warning()<<" One candidate with CapT<1e3 ns "<<endreq;
      lastSim = Sim;
    }
    warning()<<"CapT and GenT are too closed. Skipped."<<endreq;
    return StatusCode::SUCCESS;
  }

  /// The first interaction vertex of the 2.2 MeV gamma
  const DayaBay::SimParticleHistory* pHist = pSimHeader->particleHistory();

  if( !pHist ) {
    warning()<<"Can't get the history info"<<endreq;
    return StatusCode::SUCCESS;
  }

  // Search for the 2.2 MeV SimTrack
  const std::list<DayaBay::SimTrack*>& trk=pHist->tracks();
  std::list<DayaBay::SimTrack*>::const_iterator tkci, tkEnd=trk.end();

  SimTrack* GammaTrack = 0;
  for(tkci = trk.begin(); tkci != tkEnd; tkci++ ) {
    // Find primary gamma track
    // There is only one gamma track in H-capture. So this code doesn't work
    // well for Gd-capture.
    if( (*tkci)->particle() == 22 ) {
      GammaTrack = *tkci ;
      break;
    }
  }
  
  if( !GammaTrack )  {
    warning()<<"Failed to get the 2.2 MeV gamma track"<<endreq;
    return StatusCode::SUCCESS;
  }

  /// Looking for the first interaction point
  const vector<SimVertex*>& GamVtx = GammaTrack->vertices();
  const SimVertex* FirstComptonVtx = 0;
  Gaudi::XYZPoint  AveGammaVtx(0,0,0);
  double ETotal, EAtLastVtx, ELoss;
  for( unsigned int ci=0; ci<GamVtx.size(); ++ci )  {
    /*
    // Print out to validate the gamma processes
    if( ci==0 )  {
      info()<<"Begin of a gamma track with e="<<GamVtx[ci]->totalEnergy()<<endreq;
    }
    info()<<GamVtx[ci]->process().type()<<"\t"<<GamVtx[ci]->process().name()<<"\t"<<GamVtx[ci]->totalEnergy()<<endreq;
    */
    
    if( ci==0 )  {
      EAtLastVtx = GamVtx[ci]->totalEnergy();
    }
    
    if( ci>0  )  {

      Gaudi::XYZPoint ThisVtx = GamVtx[ci]->position();
      /* Only consider the vertexes in LS */
      if( m_dbLso1->geometry()->isInside( ThisVtx ) )  {
	ELoss = EAtLastVtx - GamVtx[ci]->totalEnergy();
	AveGammaVtx.SetX( AveGammaVtx.x() + ThisVtx.x()*ELoss );
	AveGammaVtx.SetY( AveGammaVtx.Y() + ThisVtx.y()*ELoss );
	AveGammaVtx.SetZ( AveGammaVtx.Z() + ThisVtx.z()*ELoss );
	
	ETotal += ELoss;
      }

      EAtLastVtx = GamVtx[ci]->totalEnergy();
    }
   
    if( GamVtx[ci]->process().name() == "LowEnCompton" ||
	GamVtx[ci]->process().name() == "LowEnConversion" ||
	GamVtx[ci]->process().name() == "LowEnPhotoElec" ) {
      if( !FirstComptonVtx )  FirstComptonVtx = GamVtx[ci];
     }    
  }
  
  AveGammaVtx = AveGammaVtx/ETotal;

  if( !FirstComptonVtx )  {
    warning()<<"Failed to get the 2.2 MeV Gamma's first Compton or Conversion vertex"<<endreq;
    return StatusCode::SUCCESS;
  }

  Gaudi::XYZPoint GblDepC;
  if( AveGammaVtx.Mag2() > 0 )  {
    GblDepC = AveGammaVtx;
  } else {
    /* Rarely gamma vertexes themselves are not in LS, but their products' vertexes might be in LS.
       So cannot find an average gamma vertex. They all have very small detected energy.
       Use first compton scattering vertex instead. */
    GblDepC = FirstComptonVtx->position();
  }
  Gaudi::XYZPoint LclDepC = m_dbOil1->geometry()->toLocal( GblDepC );

  /// Finish an event and restart
  /// ---------------------------
  if( ThisSimCycle != mDetSimCycle )  {
    if( mDetSimCycle != -1 )  {
      EndEvent();
    }
    mDetSimCycle = ThisSimCycle;
    mEvent.Reset();
  }

  /// Positron branch
  /// ---------------
  if( abs((TrigTime-GenT).GetSeconds()) < 0.1e-6 ) {

    /* Is this a bug to set it to 1 here? */
    /* Always set positron to the first?  */
    mEvent.Fold = 1;

    // AddElectron
    mEvent.TrigSec[0]  = TrigTime.GetSec();
    mEvent.TrigNano[0] = TrigTime.GetNanoSec();
    mEvent.E[0]        = E;
    mEvent.X[0]        = X;
    mEvent.Y[0]        = Y;
    mEvent.Z[0]        = Z;
    mEvent.D2First[0]  = 0;

    // Truth
    mEvent.TrigSecT[0]  = GenT.GetSec();
    mEvent.TrigNanoT[0] = GenT.GetNanoSec();
    mEvent.ET[0]        = e_Trk1 + 0.511; /* Kinetic Energy + 0.511 */
    mEvent.XT[0]        = - LclGen.x();   /* Trac 1215 */
    mEvent.YT[0]        = - LclGen.y();
    mEvent.ZT[0]        = LclGen.z();
    mEvent.D2FirstT[0]  = 0;

  }

  /// Neutron branch
  /// --------------
  mEvent.CapTarget = capTarget;
  if( abs((TrigTime-CapT).GetSeconds()) < 0.1e-6 ) {

    mEvent.Fold += 1;
    int Fold = mEvent.Fold-1;  /* for array idx */

    // AddNeutron
    double X1,Y1,Z1;
    X1  = mEvent.X[ 0 ];
    Y1  = mEvent.Y[ 0 ];
    Z1  = mEvent.Z[ 0 ];

    mEvent.TrigSec[Fold]  = TrigTime.GetSec();
    mEvent.TrigNano[Fold] = TrigTime.GetNanoSec();
    mEvent.E[Fold]        = E;
    mEvent.X[Fold]        = X;
    mEvent.Y[Fold]        = Y;
    mEvent.Z[Fold]        = Z;
    mEvent.D2First[Fold]  = sqrt( (X-X1)*(X-X1) + (Y-Y1)*(Y-Y1) + (Z-Z1)*(Z-Z1) );

    // Truth
    X1  = mEvent.XT[ 0 ];
    Y1  = mEvent.YT[ 0 ];
    Z1  = mEvent.ZT[ 0 ];

    mEvent.TrigSecT[Fold]  = CapT.GetSec();
    mEvent.TrigNanoT[Fold] = CapT.GetNanoSec();

    mEvent.ET[Fold] = capTarget;
    if( capTarget == 1 )   mEvent.ET[Fold] = 2.2246;
    if( capTarget == 6 )   mEvent.ET[Fold] = 5.5;
    if( capTarget == 64 )  mEvent.ET[Fold] = 8.1;

    mEvent.XT[Fold]        = - LclCap.x();
    mEvent.YT[Fold]        = - LclCap.y();
    mEvent.ZT[Fold]        = LclCap.z();
    mEvent.D2FirstT[Fold]  = sqrt( ( mEvent.XT[Fold]-X1)*(mEvent.XT[Fold]-X1) 
				   + (mEvent.YT[Fold]-Y1)*(mEvent.YT[Fold]-Y1) 
				   + (mEvent.ZT[Fold]-Z1)*(mEvent.ZT[Fold]-Z1) );

    mEvent.XDepC[Fold]      = - LclDepC.x();
    mEvent.YDepC[Fold]      = - LclDepC.y();
    mEvent.ZDepC[Fold]      = LclDepC.z();
    
    mEvent.T2PrevSubEvt[Fold] = (mEvent.TrigSecT[Fold]-mEvent.TrigSecT[Fold-1])+
      (mEvent.TrigNanoT[Fold]-mEvent.TrigNanoT[Fold-1])*1e-9;
  }

  return StatusCode::SUCCESS;
}

StatusCode ExamTruth::finalize()
{
  mTree->Close();
  return this->GaudiAlgorithm::finalize();
}

StatusCode ExamTruth::EndEvent()
{
  mTree->Reset();

  mTree->Run        = 0;
  mTree->Det        = 0;

  mTree->T2PrevMu   = 0;
  mTree->T2PrevPlMu = 0;
  mTree->T2PrevAdMu = 0;
  mTree->T2PrevShMu = 0;
  mTree->T2PrevNetMu = 0;

  mTree->Fold       = mEvent.Fold;
  if( mEvent.Fold > Max ) {
    warning()<<"Number of fold is above the limit. Skipped."<<endreq;
    return StatusCode::SUCCESS;
  }

  for( int FoldIdx = 0; FoldIdx < mEvent.Fold; FoldIdx++ )   {
    mTree->TrigSec[FoldIdx]      = mEvent.TrigSec[FoldIdx];
    mTree->TrigNano[FoldIdx]     = mEvent.TrigNano[FoldIdx];
    mTree->E[FoldIdx]            = mEvent.E[FoldIdx];
    mTree->X[FoldIdx]            = mEvent.X[FoldIdx];
    mTree->Y[FoldIdx]            = mEvent.Y[FoldIdx];
    mTree->Z[FoldIdx]            = mEvent.Z[FoldIdx];
    mTree->D2First[FoldIdx]      = mEvent.D2First[FoldIdx];
    mTree->T2PrevSubEvt[FoldIdx] = mEvent.T2PrevSubEvt[FoldIdx];

    mTree->TrigSecT[FoldIdx]      = mEvent.TrigSecT[FoldIdx];
    mTree->TrigNanoT[FoldIdx]     = mEvent.TrigNanoT[FoldIdx];
    mTree->ET[FoldIdx]            = mEvent.ET[FoldIdx];
    mTree->XT[FoldIdx]            = mEvent.XT[FoldIdx];
    mTree->YT[FoldIdx]            = mEvent.YT[FoldIdx];
    mTree->ZT[FoldIdx]            = mEvent.ZT[FoldIdx];
    mTree->D2FirstT[FoldIdx]      = mEvent.D2FirstT[FoldIdx];
    mTree->T2PrevSubEvtT[FoldIdx] = mEvent.T2PrevSubEvtT[FoldIdx];

    mTree->XDepC[FoldIdx]          = mEvent.XDepC[FoldIdx];
    mTree->YDepC[FoldIdx]          = mEvent.YDepC[FoldIdx];
    mTree->ZDepC[FoldIdx]          = mEvent.ZDepC[FoldIdx];
    mTree->CapTarget      	   = mEvent.CapTarget;
  }
  
  // For beizhen
  if( mEvent.Fold==1 ) {
    mTree->Fold       = 2;
    mTree->E[1]       = 0;
  } 

  mTree->Fill();

  return StatusCode::SUCCESS;
}  
