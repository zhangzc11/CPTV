/**
 * ReconStreamer
 *
 * Apr. 28, 2010  Created by ...
 */
#include "ReconStreamer.h"
#include "Event/CalibReadoutHeader.h"
#include "Event/CalibReadout.h"
#include "Event/CalibReadoutPmtCrate.h"
#include "Event/UserDataHeader.h"
#include "Event/RecHeader.h"
#include "Context/ServiceMode.h"

using namespace DayaBay;

ReconStreamer::ReconStreamer(const std::string& name, ISvcLocator* pSvcLocator):
  GaudiAlgorithm(name, pSvcLocator)
{
  declareProperty("TreeName", m_TreeName = "Stream", "Root tree name");
  declareProperty("FileName", m_FileName = "pending.root", "Output root file name");
  declareProperty("Verbosity", m_Verbosity = 0, "Simplified Root tree");
  declareProperty("RunNumber", m_RunNumber = -1, "RunNumber");
}

ReconStreamer::~ReconStreamer()
{
}

StatusCode ReconStreamer::initialize()
{
  StatusCode sc;
  sc = this->GaudiAlgorithm::initialize();
  if( sc.isFailure() )  return sc;

  m_StreamTree = new StreamTree( m_TreeName.c_str(), m_FileName.c_str(), m_Verbosity );

  sc = service("DetailsFromRecordSvc",m_DaqDetailsSvc);
  info()<<"DetailsFromRecordSvc "<<m_DaqDetailsSvc<<endreq;
  if( sc.isFailure() )  return sc;

  return sc;
}

StatusCode ReconStreamer::execute()
{
  m_StreamTree->Reset();

  /// 1. The Basic info
  /// =================
  CalibReadoutHeader* pCalibReadoutHdr = get<CalibReadoutHeader>( CalibReadoutHeader::defaultLocation() );
  if(!pCalibReadoutHdr) {
    error()<<"Failed to get CalibReadoutHeader"<<endreq;
    return StatusCode::FAILURE;
  }
  const CalibReadout* pCalibReadout = pCalibReadoutHdr->calibReadout();
  if(!pCalibReadout) {
    error()<<"Failed to get CalibReadout"<<endreq;
    return StatusCode::FAILURE;
  }

  int runNumber = m_RunNumber;
  /* This only works for daq format. */
  ServiceMode svcMode( pCalibReadoutHdr->context(),0 );
  if( m_DaqDetailsSvc->hasRunDetails( svcMode ) ) {
    runNumber = m_DaqDetailsSvc->runDetails( svcMode ).runNumber();
    info()<<"runNumber "<<runNumber<<endreq;
  }

  m_StreamTree->Run = runNumber;
  m_StreamTree->Site = pCalibReadout->detector().site();
  DetectorId::DetectorId_t detectorId = pCalibReadout->detector().detectorId();
  m_StreamTree->Det = pCalibReadout->detector().detectorId();
  
  m_StreamTree->TrigNum = pCalibReadout->triggerNumber();
  m_StreamTree->TrigType = pCalibReadout->triggerType();
  m_StreamTree->TrigSec = pCalibReadout->triggerTime().GetSec();
  m_StreamTree->TrigNano = pCalibReadout->triggerTime().GetNanoSec();

  const CalibReadoutPmtCrate* pPmtReadout = 0;
  if(detectorId!=DetectorId::kRPC && detectorId!=DetectorId::kUnknown){
    pPmtReadout = dynamic_cast<const CalibReadoutPmtCrate*>( pCalibReadout );
    if( !pPmtReadout ) {
      error() << "Invalid PMT Crate readout!." << endreq;
      return StatusCode::FAILURE;
    }
    m_StreamTree->NPmt = pPmtReadout->channelReadout().size();
  }
  
  /// 2. The reconstructed info
  /// =========================
  RecHeader* pRecHeader = get<RecHeader>( "/Event/Rec/AdSimple" );
  if(!pRecHeader) {
    error()<<"Failed to get RecHeader"<<endreq;
    return StatusCode::FAILURE;
  }
  const RecTrigger* pRecTrigger = &(pRecHeader->recTrigger());
  if(!pRecTrigger) {
    error()<<"Failed to get RecTrigger"<<endreq;
    return StatusCode::FAILURE;
  }

  m_StreamTree->E = pRecTrigger->energy();
  m_StreamTree->X = pRecTrigger->position().x();
  m_StreamTree->Y = pRecTrigger->position().y();
  m_StreamTree->Z = pRecTrigger->position().z();

  /// 3. Some predefined user data
  /// ============================
  UserDataHeader* pUserDataHdr = get<UserDataHeader>( "/Event/Data/CalibStats" );
  if(!pUserDataHdr) {
    error()<<"Failed to get UserDataHeader"<<endreq;
    return StatusCode::FAILURE;
  }

  m_StreamTree->TRms = pUserDataHdr->getFloat( "MiddleTimeRMS" );
  m_StreamTree->Quadrant  = pUserDataHdr->getFloat( "Quadrant" );
  m_StreamTree->QMax2Sum  = pUserDataHdr->getFloat( "MaxQ" );
  m_StreamTree->MaxQ2Inch = pUserDataHdr->getFloat( "MaxQ_2inchPMT" );

  m_StreamTree->Fill();
  return StatusCode::SUCCESS;
}

StatusCode ReconStreamer::finalize()
{
  m_StreamTree->Close();

  StatusCode sc;
  sc = this->GaudiAlgorithm::finalize();

  return sc;
}
