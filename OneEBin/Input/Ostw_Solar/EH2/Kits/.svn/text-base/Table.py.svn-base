#!/usr/bin/env python
'''
   Table class, hold column names and row list
   Append zeros if insufficient columns than field names
   Zhe Wang, July 28, 2011
'''
class Table:
    def __init__(self):
        self.reset()

    def reset(self):
        self.filename = None     # The table file
        
        self.comments = []       # All lines start with '#'        
        self.headerLine = None   # The line with  '# [name1]  [name2] ...'
        self.fieldNames = []     # Column names
        self.columns = {}        # Column name indexed value list
        self.nRows = 0           # Number of rows    

    def read(self,filename):
        self.filename = filename
        tableLines = open(self.filename).readlines()
        for line in tableLines:
            data = line.strip()
            # Catch comments / header
            if len(data)>0 and data[0]=='#':
                comment = data[1:].strip()
                if len(comment)>0 and comment[0] =='[':
                    # Found header
                    if len(self.fieldNames) > 0:
                        print "Warning Headers already defined by line \"",data,"\"",self.filename
                        print "Following lines are skipped."
                        return None
                    tokens = comment.split(']')
                    if len(tokens[-1].strip())==0: tokens = tokens[:-1]
                    for token in tokens:
                        fieldStart = token.rfind('[')
                        if fieldStart<0:
                            print "Invalid token \"",token,"\" in line \"",line,"\""
                            return None
                        fieldName = token[fieldStart+1:].strip()
                        self.fieldNames.append(fieldName)
                        self.columns[fieldName] = []
                        self.headerLine = line
                else:
                    self.comments.append(line)
                continue
            # Data line
            fields = data.split()
            if len(fields)==0: continue  # Empty line
            if len(fields) > len(self.columns):
                print "Extra number of fields in line \"",line,"\""
                return None
            for fieldIdx in range( len(fields) ):
                self.columns[ self.fieldNames[fieldIdx] ].append( fields[fieldIdx] )

            if len(fields) < len(self.columns):
                #print "Insufficient number of fields in line \"",line,"\"","0 appended"
                for fieldIdx in range( len(fields), len(self.columns) ):
                    self.columns[ self.fieldNames[fieldIdx] ].append( 0 )
                    
            self.nRows += 1

    def dump(self):
        print self.fieldNames
        for rowIdx in range(self.nRows):
            for fieldIdx in range(len(self.fieldNames)):
                print self.columns[self.fieldNames[fieldIdx]][rowIdx]

if __name__ == "__main__":
    table = Table()
    table.read("/home/dayabay/users/wangzhe/zlab/TWin/data/Sample/P12b-all/H/RunInfo.txt")

    time=0;
    fulltime  = 0;
    vetotime1 = 0;
    vetotime2 = 0;
    vetotime3 = 0;
    vetotime4 = 0;
    livetime1 = 0;
    livetime2 = 0;
    livetime3 = 0;
    livetime4 = 0;

    NMuon = 0
    NPl1 = NPl2 = NPl3 = NPl4 = 0
    NAd1 = NAd2 = NAd3 = NAd4 = 0
    NSh1 = NSh2 = NSh3 = NSh4 = 0
    NNet1 = NNet2 = NNet3 = NNet4 = 0

    NSgUp1 = NSgLw1 = NSgUp2 = NSgLw2 = NSgUp3 = NSgLw3 = NSgUp4 = NSgLw4 = 0

    for row in range( table.nRows ):
        site = int(table.columns["Site"][row])
        time = float(table.columns["FullTime"][row])
        
        if site == 4:
            fulltime  += time /24/60/60
            vetotime1 += float(table.columns["Veto1"][row]) /24/60/60
            vetotime2 += float(table.columns["Veto2"][row]) /24/60/60
            vetotime3 += float(table.columns["Veto3"][row]) /24/60/60
            vetotime4 += float(table.columns["Veto4"][row]) /24/60/60

            NMuon += int(table.columns["NMuon"][row])
            NPl1 += float(table.columns["NPl1"][row])
            NPl2 += float(table.columns["NPl2"][row])
            NPl3 += float(table.columns["NPl3"][row])
            NPl4 += float(table.columns["NPl4"][row])

            NAd1 += float(table.columns["NAd1"][row])
            NAd2 += float(table.columns["NAd2"][row])
            NAd3 += float(table.columns["NAd3"][row])
            NAd4 += float(table.columns["NAd4"][row])

            NSh1 += float(table.columns["NSh1"][row])
            NSh2 += float(table.columns["NSh2"][row])
            NSh3 += float(table.columns["NSh3"][row])
            NSh4 += float(table.columns["NSh4"][row])

            NNet1 += float(table.columns["NNet1"][row])
            NNet2 += float(table.columns["NNet2"][row])
            NNet3 += float(table.columns["NNet3"][row])
            NNet4 += float(table.columns["NNet4"][row])

            NSgUp1 += float(table.columns["NSgUp1"][row])
            NSgUp2 += float(table.columns["NSgUp2"][row])
            NSgUp3 += float(table.columns["NSgUp3"][row])
            NSgUp4 += float(table.columns["NSgUp4"][row])
            
            NSgLw1 += float(table.columns["NSgLw1"][row])
            NSgLw2 += float(table.columns["NSgLw2"][row])
            NSgLw3 += float(table.columns["NSgLw3"][row])
            NSgLw4 += float(table.columns["NSgLw4"][row])
            
        livetime1 = fulltime - vetotime1
        livetime2 = fulltime - vetotime2
        livetime3 = fulltime - vetotime3
        livetime4 = fulltime - vetotime4

    print "Site : Full time: ",site,fulltime
    print "Veto time for each AD: ",vetotime1,vetotime2,vetotime3
    print "Live time for each AD:",livetime1,livetime2,livetime3

    print "N Muon", NMuon
    print "N Pool Muon", NPl1, NPl2, NPl3
    print "N Ad Muon", NAd1, NAd2, NAd3
    print "N Sh Muon", NSh1, NSh2, NSh3
    print "N Net Muon", NNet1, NNet2, NNet3

    print "N Single Up", NSgUp1, NSgUp2, NSgUp3
    print "N Single Lw", NSgLw1, NSgLw2, NSgLw3

    #table.dump()    
    #print table.fieldNames

