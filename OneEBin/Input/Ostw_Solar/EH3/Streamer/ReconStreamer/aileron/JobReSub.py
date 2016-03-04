#!/usr/bin/env python
'''
    Queue can never be stable. Need a way to automatically to resub them
    Zhe Wang, Dec. 15, 2011
'''
import sys,os
from FileName import FileName

class JobReSub:
    def __init__(self, argv):    

        self.MainDir = "/publicfs/dyb/data/userdata/wangzhe/zlab/TWin/ReconStreamer/aileron/Script/"
        self.WorkingDirs = [ self.MainDir+"Recon-0014858-14861-14866-14869-14872-14876-14928-14931-14934-14937.list/",
                             self.MainDir+"Recon-0014941-14996-15001-15007-15012-15018-15021-15029-15033-15036.list/",
                             self.MainDir+"Recon-0015101-15105-15134-15140-15146-15389-15536-15593-15694-15775.list/",
                             self.MainDir+"Recon-0016084-16094-16347-16432-17094-17158-17231-17270-17274-17332.list/",
                             self.MainDir+"Recon-0017341-17535-17601-17656-17751-17764-17865-17884-17895.list/",
                             self.MainDir+"Recon-0012400-12579-12653-12730-12793-12857-13002-13061-13230-13303.list/",
                             self.MainDir+"Recon-0013363-13422-13499-13564-13719-13778-13837-13859-13879-13954.list/",
                             self.MainDir+"Recon-0014012-14020-14077-14124-14127-14136-14139-14152-14192-14193.list/",
                             self.MainDir+"Recon-0014256-14349-14369-14371-14375-14408-14735-14788-14852-14855.list/" ]

        JobList = []
        for scriptDir in self.WorkingDirs:
            for script in os.listdir( scriptDir ):
                if script[-4:] == ".csh":
                    jobdone = scriptDir + script[:-4] + ".done"
                    # test each csh script
                    if not os.path.exists( jobdone ):
                        aJob = scriptDir+script
                        JobList.append( aJob )

        for command in JobList:
            print "qsub -q dyb64q ",command,"&"
            #os.system( "qsub -q dyb64q "+command+"&" )


if __name__ == "__main__":
    jobReSub = JobReSub(sys.argv)
    
