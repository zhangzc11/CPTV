#!/usr/bin/env python
'''
    Usage:
        
    
'''

import sys,os
if __name__ == "__main__":

    CalibListDir = "/publicfs/dyb/data/userdata/wangzhe/zlab/TWin/data/TWinList/18_P12b_all_Calib_AdScaled"
    BkgListDir = "/publicfs/dyb/data/userdata/wangzhe/zlab/TWin/data/TWinList/18_P12b_all_Calib_AdScaled/BkgList"

    CmdDir = "/publicfs/dyb/data/userdata/wangzhe/zlab/TWin/Vertex/CalibVertex"

    cmdls = "ls -1 "+CalibListDir+"/*.list"
    currDir = os.getcwd()
    
    for line in os.popen( cmdls ):
        ListFile = line.strip()
        LastSl = ListFile.rfind( '/' )
        ListFileName = ListFile[ LastSl+1:-5 ]
        Site = ListFileName[ 0:3 ]

        #print ListFileName, Site
        os.chdir(currDir)
        if not os.path.exists( ListFileName ):
            os.makedirs( ListFileName )
        os.chdir(ListFileName)

        BkgFile = BkgListDir+"/"+Site+".list"

        print ListFile
        print BkgFile
        
        cmd = CmdDir+"/CalibVertex.py "+ListFile+" "+BkgFile+" "+Site +" &"
        print cmd
        os.system( " echo 1> OK " )
        os.system( cmd )
        
        

