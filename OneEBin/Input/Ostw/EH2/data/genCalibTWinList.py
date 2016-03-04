#!/usr/bin/env python

import sys,os
if __name__ == "__main__":

    Hall   = [ 'EH1', 'EH2', 'EH3' ]
    Source = [ 'AmC_Co60', 'Ge68' ]
    Axis   = [ 'A', 'B', 'C' ]

    Ul = '_'
    Sl = '/'
        
    BaseDir = "~/userdata/zlab/TWin/data/TWin/18_P12b_all_Calib_AdScaled"

    for hallN in range(len(Hall)):
        for SrceN in range(len(Source)):
            for AxisN in range(len(Axis)):

                listfile = Hall[hallN] + Ul + Source[SrceN] + Ul + Axis[AxisN] + ".list"
                DataDir = BaseDir + Sl + Hall[hallN] + Sl + Source[SrceN] + Sl + Axis[AxisN] + Sl
                
                FILE = open(listfile,"w")
                cmdls = "ls -1 "+DataDir+"*"
                for line in os.popen( cmdls ):
                    FILE.writelines(line)
                FILE.close()
