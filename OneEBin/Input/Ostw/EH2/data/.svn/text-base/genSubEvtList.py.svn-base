#!/usr/bin/env python

import sys,os
if __name__ == "__main__":
    RunList = [ 15001, 15007, 15012, 15018, 15021, 15029, 15033, 15036, 15101, 15105, 
                15134, 15140, 15146, 15389, 15536, 15593, 15694, 15775, 16084, 16094, 
                16347, 16432, 17094, 17158, 17231, 17270, 17274, 17332, 17341, 17535, 
                17601, 17656, 17751, 17764, 17865, 17884, 17895 ]
    
    SubEvtDataDir = "/home/wangzhe/share/data/exp/SubEvt/"

    for run in RunList:
        print "Creating SubEvt.list for run ",str(run).zfill(7)
        listfile = str(run).zfill(7)+".SubEvt.list"

        FILE = open(listfile,"w")
        cmdls = "ls -1tr "+SubEvtDataDir+str(run).zfill(7)+"*"
        for line in os.popen( cmdls ):
            FILE.writelines(line)
        FILE.close()
