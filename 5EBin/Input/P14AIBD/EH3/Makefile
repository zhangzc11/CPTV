
########

ttt:
	-rm *~

clean:ttt clean_new_DataSelection_EH3

########

clean_new_DataSelection_EH3:ttt
	-rm new_DataSelection_EH3
new_DataSelection_EH3:clean_new_DataSelection_EH3
	g++ -o new_DataSelection_EH3 new_DataSelection_EH3.cc -O `root-config --libs` -I. -I/home/dayabay/sw/root/include -L/home/dayabay/sw/root/lib
