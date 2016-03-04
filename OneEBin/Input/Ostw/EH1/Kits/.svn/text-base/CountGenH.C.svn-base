/*
  This is useful to count how many genheaders in one MC job.
  Usage: 
    root CountGenH.C
*/

{
  TChain GenHeader("/Event/Gen/GenHeader");
  GenHeader.Add("recon_LS_modif_Absop_p3_r09.root");
  GenHeader.Add("recon_LS_modif_Absop_p3_r10.root");

  cout<< GenHeader.GetEntries()<<endl;
}
