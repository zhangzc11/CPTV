/**
 * SubEvt
 *
 * Nov. 22, 2011 Created by Zhe Wang
 */

#ifndef _SUB_EVT_H_
#define _SUB_EVT_H_

struct AdSubEvt
{
  bool   Valid;
  int    Event;
  int    Det;

  int    TrigType;
  int    TrigSec;
  int    TrigNano;

  int    NPmt;

  double E;
  double X;
  double Y;
  double Z;

  double TRms;
  double Quadrant;
  double QMax2Sum;
};

struct PoolSubEvt
{
  bool   Valid;
  int    Event;
  int    Det;

  int    TrigType;
  int    TrigSec;
  int    TrigNano;

  int    NPmt;
};

struct RpcSubEvt
{
  bool   Valid;
  int    Event;
  int    Det;

  int    TrigType;
  int    TrigSec;
  int    TrigNano;
  double X;
  double Y;
};

struct SubEvt
{
  int    Run;
  int    Site;
  //  01110001 are for AD1, IWS, OWS and RPC
  int    Detectors;

  double MuonProb;
  
  AdSubEvt Ads[4];
  PoolSubEvt Iws;
  PoolSubEvt Ows;
  RpcSubEvt Rpc;
};

#endif  // _SUB_EVT_H_
