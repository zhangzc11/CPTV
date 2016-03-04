#!/usr/bin/env python
# 
#  Split a Full-Path-File-Name into several parts:
#      Full-Path-Name and '.' separated files names
#  
#  Zhe Wang, 2012 Dec.
#
class FileName:
    def __init__(self, FullPathFileName):

        self.FullPathFileName = FullPathFileName
        
        start = self.FullPathFileName.rfind( '/' )
        self.FullFileName = self.FullPathFileName[ start+1: ]
        
        self.fields = self.FullFileName.split( '.' )

        # Todo: need to finish all of them
        self.RunNumber  = self.fields[2]
        self.Site       = self.fields[-4]
        self.FileNumber = self.fields[-2]


if __name__ == "__main__":
    aFile = FileName( '/home/wangzhe/share/data/exp/recon.Neutrino.0017764.Physics.EH1-Merged.KUP11A-IHEP._0212.root' )
    print aFile.RunNumber, aFile.Site, aFile.FileNumber
