#!/usr/bin/env python
'''
    Add all log file together.
    Zhe Wang
'''
import sys,os
if __name__ == "__main__":

    CurrentDir = "./"
    cmdls = "ls -1 "+CurrentDir+"*.log"
    RunList = os.popen( cmdls )
    
    for runlog in RunList:
        log = runlog.strip()
        print log
        cmdcat = "cat "+log+" >> Tree.txt"
        print cmdcat
        os.popen( cmdcat )
