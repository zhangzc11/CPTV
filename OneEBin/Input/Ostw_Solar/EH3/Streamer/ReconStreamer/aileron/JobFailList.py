#!/usr/bin/env python
'''
    Queue can never be stable. Need a way to find out all failed ones.    
    Zhe Wang, Dec. 15, 2011

    Usage:
        Need to manually modify
        1. "self.DataListDir" where the data list files are stored and
        2. "self.OutputDir" where the output data files are stored.
    
'''
import sys,os
from FileName import FileName

class JobFailList:
    def __init__(self, argv):    

        self.DataListDir = "/publicfs/dyb/data/rec/P12B/P12B_good_files_3sites_prl_120221_v1/EH3/"
        self.DataListFile = os.listdir(self.DataListDir)

        self.OutputDir = "/publicfs/dyb/data/userdata/wangzhe/zlab/TWin/ReconStreamer/aileron/Output/EH3-Merged/"

        MissingDataList = []        
        for aDataListFile in self.DataListFile:
            DataFileFullPath = self.DataListDir+aDataListFile
            DataList = open( DataFileFullPath, "r" ).readlines()
            for aDataFile in DataList:
                aDataFile = aDataFile.strip()
                # Raw data file exist?
                if os.path.exists( aDataFile ):
                    filename = FileName( aDataFile )
                    StreamData = self.OutputDir+"/"+filename.RunNumber+"/"+filename.RunNumber+"."+filename.FileNumber+".Stream.root"
                    # stream.root exist?
                    if os.path.exists( StreamData ):
                        pass
                    else:
                        print "Missing... ",aDataFile
                        MissingDataList.append( aDataFile )
                else:
                    print "Error: Original",aDataFile,"doesn't exist"
                    sys.exit()

        FILE = open( "Missing.list","w" )
        for aMissingEntry in MissingDataList:
            FILE.writelines( aMissingEntry + " \n")
        FILE.close()
        
if __name__ == "__main__":
    jobList = JobFailList(sys.argv)
    print "Missing data file list created."
