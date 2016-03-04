#!/usr/bin/env python                                                           
#
#  -- Usage:
#     In this directory
#       >  nuwa.py -A none --random off -n 10 -m "run -o output.Stream.root" /home/wangzhe/share/data/exp/recon.Neutrino.0017764.Physics.EH1-Merged.KUP11A-IHEP._0212.root 
#     In other directories use ReconStreamer.run
#       >  nuwa.py -A none --random off -n 10 -m "ReconStreamer.run -o output.Stream.root" /home/wangzhe/share/data/exp/recon.Neutrino.0017764.Physics.EH1-Merged.KUP11A-IHEP._0212.root -o output.Stream.root
#     

def configure(argv=[]):
    import sys, getopt
    opts,args = getopt.getopt(argv,"r:o:")

    runNum = -1
    for opt,arg in opts:
        if opt == "-r":
            runNum = arg
        if opt == "-o":
            output = arg

    from Gaudi.Configuration import ApplicationMgr
    theApp = ApplicationMgr()
    
    # Add myself into the queue                                                 
    from ReconStreamer.ReconStreamerConf import ReconStreamer
    MyAlg=ReconStreamer()
    MyAlg.RunNumber = runNum
    MyAlg.FileName = output
    theApp.TopAlg.append(MyAlg)
    
