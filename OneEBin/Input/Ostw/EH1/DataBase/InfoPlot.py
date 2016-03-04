#!/usr/bin/env python
'''
   Zhe Wang, Jan. 5, 2011
'''
from ROOT import gROOT, gStyle, gDirectory, TCanvas, TFile, TTree, TPad, TLatex, TH2F, TH1F, TGraph
from Table import Table
from array import array

if __name__ == "__main__":
    
    table = Table()
    table.read("NewTable.txt")
    #table.dump()

    run       = array( 'f' )
    time      = array( 'f' )
    livetime  = array( 'f' )
    nMuon     = array( 'f' )
    n8MeV1    = array( 'f' )
    n8MeV2    = array( 'f' )
    n22MeV1   = array( 'f' )
    n22MeV2   = array( 'f' )

    rateMu       = array( 'f' )
    effCorr      = array( 'f' )
    rateRaw8_1   = array( 'f' )
    rateRaw8_2   = array( 'f' )
    rateRaw22_1  = array( 'f' )
    rateRaw22_2  = array( 'f' )
    rate8_1      = array( 'f' )
    rate8_2      = array( 'f' )
    rate22_1     = array( 'f' )
    rate22_2     = array( 'f' )

    for i in range(0,table.nRows):
        run       .append( float(table.columns["Run"][i]       ))
        time      .append( float(table.columns["Time"][i]      ))
        livetime  .append( float(table.columns["LiveTime"][i]  ))
        nMuon     .append( float(table.columns["NMuon"][i]     ))
        n8MeV1    .append( float(table.columns["N8MeV1"][i]    ))
        n8MeV2    .append( float(table.columns["N8MeV2"][i]    ))
        n22MeV1   .append( float(table.columns["N22MeV1"][i]   ))
        n22MeV2   .append( float(table.columns["N22MeV2"][i]   ))

        rateMu    .append( nMuon[i]/livetime[i] )
        effCorr   .append( 1.0-rateMu[i] * 800e-6 )
        
        rateRaw8_1   .append( n8MeV1[i]/livetime[i]*24*60*60  )
        rateRaw8_2   .append( n8MeV2[i]/livetime[i]*24*60*60  )
        rateRaw22_1  .append( n22MeV1[i]/livetime[i]*24*60*60 )
        rateRaw22_2  .append( n22MeV2[i]/livetime[i]*24*60*60 )

        # It seems I should not have this correction
        rate8_1      .append( n8MeV1[i]/livetime[i]*24*60*60  / effCorr[i] )
        rate8_2      .append( n8MeV2[i]/livetime[i]*24*60*60  / effCorr[i] )
        rate22_1     .append( n22MeV1[i]/livetime[i]*24*60*60 / effCorr[i] )
        rate22_2     .append( n22MeV2[i]/livetime[i]*24*60*60 / effCorr[i] )

    c1 = TCanvas("c1")
    gMuRate = TGraph( table.nRows, time, rateMu )
    gMuRate.Draw('AP')

    c2 = TCanvas("c2")
    gRateRaw8_1 = TGraph( table.nRows, time, rateRaw8_1 )
    gRateRaw8_1.Draw('AP')

    c3 = TCanvas("c3")
    gRateRaw8_2 = TGraph( table.nRows, time, rateRaw8_2 )
    gRateRaw8_2.Draw('AP')

    c4 = TCanvas("c4")
    gRateRaw22_1 = TGraph( table.nRows, time, rateRaw22_1 )
    gRateRaw22_1.Draw('AP')

    #c5 = TCanvas("c5")
    gRateRaw22_2 = TGraph( table.nRows, time, rateRaw22_2 )
    gRateRaw22_2.Draw('Psame')

    c6 = TCanvas("c6")
    gRate8_1 = TGraph( table.nRows, time, rate8_1 )
    gRate8_1.Draw('AP')

    c7 = TCanvas("c7")
    gRate8_2 = TGraph( table.nRows, time, rate8_2 )
    gRate8_2.Draw('AP')

    c8 = TCanvas("c8")
    gRate22_1 = TGraph( table.nRows, time, rate22_1 )
    gRate22_1.Draw('AP')

    #c9 = TCanvas("c9")
    gRate22_2 = TGraph( table.nRows, time, rate22_2 )
    gRate22_2.Draw('Psame')
    
    raw_input("Press ENTER to exit")
