/** 
 * ReconStreamer
 *
 * Dec. 5, 2011  Created by Zhe Wang
 */

#ifndef _RECONSTREAMER_H_
#define _RECONSTREAMER_H_

#include "GaudiAlg/GaudiAlgorithm.h"
#include "DataSvc/IDaqDetailsSvc.h"
#include "StreamTree.h"
#include <string>

using namespace std;

class ReconStreamer : public GaudiAlgorithm 
{

 public:
  
  ReconStreamer(const std::string& name, ISvcLocator* pSvcLocator);
  virtual ~ReconStreamer();
  
  virtual StatusCode initialize();
  virtual StatusCode execute();
  virtual StatusCode finalize();
  
 private:
  StreamTree* m_StreamTree;

  string m_TreeName;
  string m_FileName;
  int    m_Verbosity;

  int    m_RunNumber;
  IDaqDetailsSvc* m_DaqDetailsSvc;
};

#endif  // _RECONSTREAMER_H_
