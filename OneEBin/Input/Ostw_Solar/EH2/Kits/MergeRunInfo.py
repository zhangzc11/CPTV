#!/usr/bin/env python
'''
    Merge three sites RunInfo tables
    Zhe Wang, Dec. 15, 2011

    Usage:
    MergeRunInfo.py EH1.txt EH2.txt EH3.txt
    
'''
import sys,os
from Table import Table

class MergeTables:
    def __init__(self, argv):    

        FILE = open("RunInfoAll.txt","w")

        for siteIdx in range(1,4):
            # 1,2,3  -> 1,2,4
            site = siteIdx
            if siteIdx==3:
                site = 4
            
            print siteIdx,argv[siteIdx]
            table = Table()
            table.read( argv[siteIdx] )

            if siteIdx==1:
                FILE.writelines( table.headerLine )

            for row in range(0, table.nRows):
                # print table.columns["Site"][row]
                if int( table.columns["Site"][row] ) == site:
                    for col in range(0, len(table.fieldNames)):
                        FILE.writelines( table.columns[ table.fieldNames[col] ][row] )
                        FILE.writelines("\t")
                    FILE.writelines("\n")
                                                 
        FILE.close()

if __name__ == "__main__":
    mt = MergeTables(sys.argv)
    
