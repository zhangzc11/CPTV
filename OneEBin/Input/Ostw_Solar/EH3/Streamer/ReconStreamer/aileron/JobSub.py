#!/usr/bin/env python
'''
  Provide a command line to submit a bunch of file-by-file jobs
  Zhe Wang Oct. 3, 2010

  Example:
    1.  The default case
        JobSub.py ReconFile.list

    2. 20 files per job
        JobSub.py -f 20 ReconFile.list

    3. 20 jobs, number of files per job will be calculated depending on the total number of files
        JobSub.py -j 20 ReconFile.list

    ReconFile.list is a list of input files. By default, only one job and it will process all files.
    When both -f and -j exist , -f wins. Negative numbers are treated as invalid numbers.
'''
import sys,os
from FileName import FileName

class JobSub:
    def __init__(self, argv):    

        self.ParseArgs(argv)
        self.NOF = int(self.opts.number_of_files)
        self.NOJ = int(self.opts.number_of_jobs)
        self.ReconDataListFile = self.args[-1]
        
        self.Regulate()
        self.MainLoop()

        return

    # Arg parser
    def ParseArgs(self, argv):
        from optparse import OptionParser
        parser = OptionParser(usage=self.__doc__)

        parser.add_option("-f","--number-of-files",
                          help="Number of files for each job",
                          default=-1)
        parser.add_option("-j","--number-of-jobs",
                          help="Number of jobs",
                          default=-1)

        (options,args) = parser.parse_args(args=argv)
        self.opts = options
        self.args = args
        
        return

    # Regulate input parameters
    def Regulate(self):
        
        if not os.path.exists( self.ReconDataListFile ):
            sys.exit()

        self.List = open( self.ReconDataListFile, "r" ).readlines()
        self.Length = len(self.List)

        if self.NOF > self.Length:
            self.NOF = self.Length
        if self.NOJ > self.Length:
            self.NOJ = self.Length

        # NOF will win if both NOF and NOJ both exist.
        if self.NOF > 0:
            if self.Length % self.NOF > 0:
                self.NOJ = int(self.Length/self.NOF) + 1
            else:
                self.NOJ = int(self.Length/self.NOF)
        else:
            # Only NOJ is specified.
            if self.NOJ > 0:
                if self.Length % self.NOJ > 0:
                    self.NOF = int(self.Length/self.NOJ) + 1
                else:
                    self.NOF = int(self.Length/self.NOJ)
            # Nothing is specified.
            else:
                self.NOJ = 1
                self.NOF = self.Length

        print self.ReconDataListFile, "contains", self.Length, "data file(s), they will be processed with", self.NOJ, "job(s) with", self.NOF, "files per job."
        
    # The main loop
    def MainLoop(self):

        # Figure out the list file name and use it to store the scripts
        start = self.ReconDataListFile.rfind( '/' )
        ListFileName = self.ReconDataListFile[ start+1: ]
        
        currDir = os.getcwd()
        self.WorkingDir = currDir + "/Script/"+ListFileName+"/"        
        self.Output = "../../Output/"
        self.Log = "../../Log/"
        
        if not os.path.exists( self.WorkingDir ):
            os.makedirs( self.WorkingDir )
                        
        job_counter = 0
        file_counter = 0
        for line in self.List:
            aFile = line.strip()
            
            file_counter += 1
            if file_counter == 1:
                # Begin of job
                job_counter += 1
                cshfile = self.WorkingDir + "job" + str(job_counter).zfill(3) + ".csh"
                FILE = open(cshfile,"w")
                FILE.writelines("#!/bin/tcsh \n")
                FILE.writelines("cd "+self.WorkingDir+" \n")
                FILE.writelines("source ~wangzhe/pub_nuwa.csh \n")
                FILE.writelines("source ~wangzhe/userdata/zlab/TWin/ReconStreamer/cmt/setup.csh \n")
                                                
            if os.path.exists( aFile ):
                filename = FileName( aFile )
                # Directory name and creation
                os.chdir(self.WorkingDir)
                # output dir
                outputDir = self.Output + filename.Site + "/" + filename.RunNumber + "/"
                if not os.path.exists(outputDir):
                    os.makedirs(outputDir)
                # log file dir
                logDir    = self.Log    + filename.Site + "/" + filename.RunNumber + "/"
                if not os.path.exists(logDir):
                    os.makedirs(logDir)
                os.chdir(currDir)
                
                # filename etc
                outputfile = outputDir + filename.RunNumber+"."+filename.FileNumber+".Stream.root"
                logfile    = logDir    + filename.RunNumber+"."+filename.FileNumber+".log"
                FILE.writelines( "nuwa.py -A none --random off -n -1 -m 'ReconStreamer.run -r " + filename.RunNumber + 
                                 " -o " + outputfile + "' " + aFile + ">" + logfile + " \n")
            else:
                print "Error: ",aFile, "doesn't exist."

            if file_counter == self.NOF:
                # End of job
                FILE.writelines("echo 1 > job" + str(job_counter).zfill(3) + ".done \n")
                FILE.close()
                os.system("chmod 744 "+cshfile)
                self.submit( cshfile )
                # reset file_counter
                file_counter = 0

        # Not exactly NOF files in the last job
        if file_counter !=0 and file_counter < self.NOF:
            FILE.writelines("echo 1 > job" + str(job_counter).zfill(3) + ".done \n")
            FILE.close()
            os.system("chmod 744 "+cshfile)
            self.submit( cshfile )

    def submit(self,command):
        print "qsub -q dyb64q "+command
        os.system( "qsub -q dyb64q "+command+"&" )

if __name__ == "__main__":
    jobs = JobSub(sys.argv)
    
