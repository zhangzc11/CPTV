#!/usr/bin/env python
'''
    Kill all jobs in range [beginId, endId].

    Usage:
        JobKill.py beginId, endId

    Zhe Wang, Dec. 15, 2011
'''
import sys,os

class JobKill:
    def __init__(self, argv):    

        begin = int(argv[1])
        end   = int(argv[2])
        print begin, end
        for i in range( begin, end+1 ):
            os.system( "qdel " + str(i) )

if __name__ == "__main__":
    killthemall = JobKill(sys.argv)
    
