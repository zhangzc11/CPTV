#!/usr/bin/env python
'''
  Generate a list of all the data in the StreamDataDir area.
  Assume all the data are sorted in run number.
  Generated list file is stored in current directory.

  Jan. 2012
  Zhe Wang
'''
import sys,os
if __name__ == "__main__":
    
    StreamDataDir = "~/userdata/zlab/TWin/data/Stream/07_P12b_ext_AdScaled/EH1-Merged/"
    cmdls = "ls -1 "+StreamDataDir
    RunList = os.popen( cmdls );

    for runNumber in RunList:
        run = runNumber.strip()
        print "Creating stream.list for run ",str(run).zfill(7)
        listfile = str(run).zfill(7)+".Stream.list"

        FILE = open(listfile,"w")
        cmdls = "ls -1 "+StreamDataDir+str(run).zfill(7)+"/*"
        print cmdls
        for line in os.popen( cmdls ):
            FILE.writelines(line)
        FILE.close()
