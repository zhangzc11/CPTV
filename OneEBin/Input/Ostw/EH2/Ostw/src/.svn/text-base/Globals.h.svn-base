#ifndef _GLOBALS_H_
#define _GLOBALS_H_ 1

#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include "TChain.h"
#include "StreamReader.h"
#include "Common/Cuts.h"
#include "SubEvt.h"
#include "TimeStamp.h"
#include "math.h"
#include "Event.h"
#include "EventTree.h"
#include "RunInfo.h"

/* SubEvt queue */
typedef std::multimap<TimeStamp, SubEvt*>            SubEvtQueue;
typedef std::multimap<TimeStamp, SubEvt*>::iterator  SubEvtQueueIterator;

/* Running status */
namespace RunStatus {
  enum RunStatus_t  { waiting, inEvent };
}

#endif // _GLOBALS_H_
