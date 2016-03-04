#!/usr/bin/env python
'''
    Usage:
        CalibVertex.py CalibListFile BkgListFile Site
    
'''

import sys,os
if __name__ == "__main__":

    CalibListFile = sys.argv[1]
    BkgListFile = sys.argv[2]
    Site = sys.argv[3]
    
    #CalibListFile = "Short_EH1_Ge68_A.list"
    #BkgListFile   = "/home/bes/wangzhe/userdata/zlab/TWin/data/TWinList/16_P12b_AdScaled/EH1.list"

    os.system( "rm Output-*.root")

    CalibList = open( CalibListFile, "r" ).readlines()
    BkgList   = open( BkgListFile, "r" ).readlines()

    ExePath = "~/userdata/zlab/TWin/Vertex/CalibVertex/"

    if Site == "EH1":
        ADs = 2
    if Site == "EH2":
        ADs = 1
    if Site == "EH3":
        ADs = 3
       
    First1350 = True
    First0 = True 
    Firstn1350 = True
    for line in CalibList:
        CalibFile = line.strip()
        RunNumber = CalibFile[-17:-10]
        IntRunNumber = int(RunNumber)

        TargetBkgFile = ""
        for bkg in BkgList:
            BkgFile = bkg.strip()
            BkgRunNum = BkgFile[-17:-10]
            IntBkgRunNum = int(BkgRunNum)
            if IntBkgRunNum>IntRunNumber:
                TargetBkgFile = BkgFile
                break

        if TargetBkgFile != "":

            # Loop over each AD
            for ad in range(1,ADs+1):

                output = RunNumber+"-"+str(ad)+".root"
                print "CaVx/CaVx "+CalibFile+" "+TargetBkgFile+" "+str(ad)+" "+output
                os.system( ExePath+"CaVx/CaVx "+CalibFile+" "+TargetBkgFile+" "+str(ad)+" "+output )
                
                zlist = os.popen( ExePath+"GetMean/GetMean "+output )
                zline = zlist.readlines()
                zstr = zline[0]
                z = float( zstr )
                print "z= ",z
                
                MergeFile = "Output-"+str(ad)+"-"
                print "alpha",abs(z-0),abs(z-1200),abs(z+1200)
                if abs(z-0) < 300:
                    MergeFile += "0.root"
                if abs(z-1200) < 300:
                    MergeFile += "1350.root"
                if abs(z+1200) < 300:
                    MergeFile += "n1350.root"
                print MergeFile
                
                if not os.path.exists( MergeFile ):
                    os.system( "cp "+output+" "+MergeFile)
                else:
                    os.system(" hadd new.root "+output+" "+MergeFile)
                    os.system(" mv new.root "+MergeFile)
                    
