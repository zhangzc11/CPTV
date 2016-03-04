/** 
 * Use vertex
 *
 * Jun 6, 2012 created by Zhe Wang
 */
#ifndef _EXAM_TRUTH_H_
#define _EXAM_TRUTH_H_
#include "GaudiAlg/GaudiAlgorithm.h"
#include "Event.h"
#include "EventTree.h"
#include "DetDesc/IGeometryInfo.h"
#include "DetDesc/DetectorElement.h"
#include "XYCorr.h"
#include "RZCorr.h"
#include <string>

class ExamTruth : public GaudiAlgorithm 
{

 public:
  
  ExamTruth(const std::string& name, ISvcLocator* pSvcLocator);
  virtual ~ExamTruth();
  
  virtual StatusCode initialize();
  virtual StatusCode execute();
  virtual StatusCode finalize();
  
 private:
  int        mDetSimCycle;
  Event      mEvent;
  EventTree* mTree;
  std::string mRootFile;

  StatusCode EndEvent();

  
  /// Others
  IDetectorElement *m_dbOil1;
  IDetectorElement *m_dbLso1;

  /// RZCorr
  int Corr;
  RZCorr * mRZCorr;
  XYCorr * mXYCorr;
};

#endif  // _EXAM_TRUTH_H_
