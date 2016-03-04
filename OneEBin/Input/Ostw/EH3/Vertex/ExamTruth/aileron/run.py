#!/usr/bin/env python                                                           

def configure(argv=[]):
    import sys, getopt
    opts,args = getopt.getopt(argv,"r:o:")
    
    output = ""
    for opt,arg in opts:
        if opt == "-o":
            output = arg
                                                    

    from Gaudi.Configuration import ApplicationMgr
    theApp = ApplicationMgr()

    # Add myself into the queue                                                 
    from ExamTruth.ExamTruthConf import ExamTruth
    chkIBD=ExamTruth()
    chkIBD.RootFile = output
    theApp.TopAlg.append(chkIBD)
