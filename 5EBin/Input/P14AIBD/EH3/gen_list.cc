void gen_list()
{
  int from = 20000;
  int to   = 50000;
  int line = 0;

  TString File = "";

  cout<<endl;
  cout<<endl;

  ofstream ListWrite("cmd_list.csh", ios::out|ios::app);

  for(int idx=from; idx<to; idx++)
    {
      File = TString::Format("/back1/dayabay_back1/data/TWin/20_P14A/Gd/EH3/%07d.TWin.root", idx);

      ifstream ReadFile(File);
      if(!ReadFile) continue;

      line++;
      cout<<TString::Format(" ---> processing %03d,  Run%05d", line, idx)<<endl;

      ///
      ofstream WriteFile(TString::Format("./run_%07dj.csh",idx),ios::out|ios::app);
      WriteFile<<"#"<<endl;
      WriteFile<<"source /home/wangzhe/mroot.csh"<<endl;
      WriteFile<<TString::Format("./new_DataSelection_EH3 %d", idx)<<endl;
      WriteFile<<endl;
      WriteFile.close();

      ListWrite<<TString::Format("qsub run_%07dj.csh",idx)<<endl;
    }

  ListWrite.close();

  cout<<endl;
  cout<<endl;


}
