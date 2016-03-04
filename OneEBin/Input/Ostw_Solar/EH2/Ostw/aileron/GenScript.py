#!/usr/bin/env python
'''
   Submit Ostw jobs for all the list files in the specified directory.
   Need to manually edit "site" and "StreamListDir".

   Feb. 2012
   Zhe Wang
'''

import sys,os
if __name__ == "__main__":

    farm = "Tsinghua"
    site = "EH2"
    data = "H"
    if farm == "Tsinghua" :
        CurDir = os.getcwd()
        AppDir = CurDir+"/../src/"
        #StreamListDir = "/back1/dayabay_back1/data/StreamList/20_P14A/"+site+"/"
        #basedir = "/work/wangzhe_work/zhangzc/Livetime/Period6AD/EH2/Ostw/aileron/"
        StreamListDir = "/back1/dayabay_back1/data/StreamList/20_P14A/"+site+"/"
        basedir = "/work/wangzhe_work/zhangzc/Ostw_Solar/EH2/Ostw/aileron/"
    else:
        AppDir = "/publicfs/dyb/data/userdata/wangzhe/zlab/TWin/Ostw/"
        StreamListDir = "/publicfs/dyb/data/userdata/wangzhe/zlab/TWin/data/StreamList/03_P12b_ext/"+site+"/"
        basedir = "/publicfs/dyb/data/userdata/wangzhe/zlab/TWin/Ostw/aileron/"
        
    ListOfList = os.listdir( StreamListDir )
    for run in ListOfList:
        ext = run[-5:]
        if ext == ".list":

            base = run[:-5]
            runN = run[:-12]

	    scriptDir = basedir+"Script/"+site+"/"
            outputDir = basedir+"Output/"+site+"/"
            logDir    = basedir+"Log/"+site+"/"
            
            cshfile = scriptDir+"run"+runN+"Z2.csh"
            print cshfile
            FILE = open(cshfile,"w")
            FILE.writelines("#!/bin/tcsh \n")
            FILE.writelines("source ~/mroot.csh \n")
            FILE.writelines("cd "+AppDir+" \n")
            FILE.writelines("Ostw "+StreamListDir+base+".list" + "  " +
                            outputDir+runN+".TWin.root " + outputDir+"RunInfo.txt "+data+ " > " +
                            logDir+runN+".log\n")
            FILE.close()
            os.system("chmod 744 "+cshfile)

            if farm == "Tsinghua" :
                os.system( "bsub -n 2 -R \"span[hosts=1]\" -o "+logDir+"output.%J -e "+logDir+"error.%J "+cshfile )
            else:
                os.system( "qsub -q dyb64q "+cshfile )
