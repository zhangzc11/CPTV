#!/usr/bin/env python

from GaudiPython import *
from DybPython.DybPythonAlg import DybPythonAlg

from ROOT import TTree
from array import array

from DybDbi import GDcsAdTemp as motemp

import os
import math
# Add some crap to get file paths here perhaps

#Taken from TestDbiDataSvc.py
str2ts = lambda _:gbl.TimeStamp(*map(int,_.split("-")))

class TestTargetProtonsSvc(DybPythonAlg):

	def __init__(self,name):
		DybPythonAlg.__init__(self,name) 
		self.startTime = startTime
		self.endTime = endTime
		print "Setting up the protons test algorithm: ",self.name()
		return

	def initialize(self):
		status = DybPythonAlg.initialize(self)
		print "Initializing TestTargetProtonsSvc",self.name()
		if status.isFailure(): 
			print "Didn't get DybPythonAlg ",self.name()
			return status

		targetProtonsSvc = self.svc("ITargetProtonsSvc","TargetProtonsSvc")

		self.startTimeStamp = str2ts( self.startTime )
		self.endTimeStamp = str2ts( self.endTime )
		context = gbl.Context()
		context.SetSimFlag(gbl.SimFlag.kData)
		context.SetSite(gbl.Site.kDayaBay)
		context.SetDetId(gbl.DetectorId.kAD1)
		context.SetTimeStamp(self.startTimeStamp)
		svcMode = gbl.ServiceMode(context,0)
		protons = [ ]


		adMasses = targetProtonsSvc.getAdMasses()

		FILE = open(adMassFile,"w")
		FILE.writelines( "# [StartUTC] [StopUTC] [Site] [Ad] [GdProton] [GdProtonRE] [GdProtonAE] [LsProton] [LsProtonRE] [LsProtonAE] \n" )

		# Get day-by-day LS and GdLS proton numbers for each AD
		dt = self.startTimeStamp
		print self.startTimeStamp, self.endTimeStamp, dt
		step = 86400
		# The overloaded TimeStamp operator "<" or "<=" don't work.
		while (dt.GetSec() <= self.endTimeStamp.GetSec()):
			print "dt= ",dt
			context.SetTimeStamp( dt )

			Halls = [ gbl.Site.kDayaBay, gbl.Site.kLingAo, gbl.Site.kFar ] 
			for hall in Halls:
				# Hall 1	
				context.SetSite( hall )

				Ads = []
				if hall == gbl.Site.kDayaBay: 
					Ads = [ gbl.DetectorId.kAD1, gbl.DetectorId.kAD2 ]
				if hall == gbl.Site.kLingAo:
					Ads = [ gbl.DetectorId.kAD1 ]
				if hall == gbl.Site.kFar:
					Ads = [ gbl.DetectorId.kAD1, gbl.DetectorId.kAD2, gbl.DetectorId.kAD3 ]
				
				for ad in Ads:
					# AD 1
					print "ad= ",ad
					context.SetDetId( ad )
					svcMode = gbl.ServiceMode(context,0)
					time = dt.GetSec()
					GdProton   = targetProtonsSvc.getProtonNumber(svcMode).protonNumber
					GdProtonRE = targetProtonsSvc.getProtonNumber(svcMode).protonNumberErr_rel
					if GdProtonRE<0: GdProtonRE=0
					GdProtonAE = targetProtonsSvc.getProtonNumber(svcMode).protonNumberErr_abs
					if GdProtonAE<0: GdProtonAE=0
					
					ofMasses   = targetProtonsSvc.getOFMasses(svcMode)
					LsMass     = adMasses.m_lsMass[ad]-ofMasses.m_lsOFMass[ad]
					LsMassE    = ofMasses.m_lsOFMassErr[ad]
					HMassFraction = 0.1191
					HMassFractionRE = 0.0053
					LsProton   = LsMass*0.1191/(1.00794/6.0221415e26)
					LsProtonRE = 0
					LsProtonAE = LsProton * math.sqrt ( HMassFractionRE*HMassFractionRE + (LsMassE/LsMass)*(LsMassE/LsMass) )

					print "RE= ",HMassFractionRE, LsMassE/LsMass
					
					FILE.writelines( str(dt.GetSec())+" "+str(dt.GetSec()+step)+" "+str(hall)+" "+str(ad)+" "+
							 str(GdProton)+" "+str(GdProtonRE)+" "+str(GdProtonAE)+" "+
							 str(LsProton)+" "+str(LsProtonRE)+" "+str(LsProtonAE)+" "+
							 "\n" )

			dt.Add( step )

		FILE.close()
		return SUCCESS

	def execute(self):
		print "Executing", self.name()
		return SUCCESS

	def finalize(self):
		print "Finalizing",self.name()
		status = DybPythonAlg.finalize(self)
		return status

	pass


adMassFile="NProton.20110920-20120220.txt"
protonsSvcName = "TargetProtonsSvc"
startTime = "2011-09-20-0-0-0"
#endTime = "2011-09-22-0-0-0"
endTime = "2012-02-20-0-0-0"

def configure(argv=[]):
	global protonsSvcName
	global startTime
	global endTime

	import sys,getopt
	opts,args = getopt.getopt(argv,"",["adMassTable-name=", "startTime=","endTime="])
	for opt,arg in opts:
		if opt == "--adMassTable-name":
			adMassFile = arg
		if opt == "--startTime":
			startTime = arg
		if opt == "--endTime":
			endTime = arg

	return

def run(app):
	global protonsSvcName
	global startTime
	global endTime
	app.ExtSvc += [protonsSvcName]
	alg = TestTargetProtonsSvc("TestTargetProtonsSvc")
	alg.startTime = startTime
	alg.endTime = endTime
	app.addAlgorithm(alg)

	return

