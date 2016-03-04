#!/usr/bin/env python
'''
  Change file and directory permissions recursively and together.

  Sep. 2012
  Zhe Wang
'''
import sys,os
if __name__ == "__main__":

    currDir = os.getcwd()
    for root, subFolders, files in os.walk(currDir):

        for folder in subFolders:
            fullfolder = os.path.join(root, folder)
            os.chmod( fullfolder, 0755 )

        for file in files:
            fullfile = os.path.join(root, file)
            appendix = file[-3:]
            if appendix == ".py":
                os.chmod( fullfile, 0755 )
            else:
                os.chmod( fullfile, 0644 )
