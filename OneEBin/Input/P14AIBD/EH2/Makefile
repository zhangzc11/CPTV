
########

ttt:
	-rm *~

clean:ttt clean_new_DataSelection_EH2

########

clean_new_DataSelection_EH2:ttt
	-rm new_DataSelection_EH2
new_DataSelection_EH2:clean_new_DataSelection_EH2
	g++ -o new_DataSelection_EH2 new_DataSelection_EH2.cc -O `root-config --libs` -I. -I/home/dayabay/sw/root/include -L/home/dayabay/sw/root/lib
