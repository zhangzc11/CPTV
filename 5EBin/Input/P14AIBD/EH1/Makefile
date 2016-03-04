
########

ttt:
	-rm *~

clean:ttt clean_new_DataSelection_EH1

########

clean_new_DataSelection_EH1:ttt
	-rm new_DataSelection_EH1
new_DataSelection_EH1:clean_new_DataSelection_EH1
	g++ -o new_DataSelection_EH1 new_DataSelection_EH1.cc -O `root-config --libs` -I. -I/home/dayabay/sw/root/include -L/home/dayabay/sw/root/lib
