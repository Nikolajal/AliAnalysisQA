#ifndef LAMBDA1520_CONFIG
#define LAMBDA1520_CONFIG

#include "config/Lambda1520_config_IO.C"
//#include "config/Lambda1520_config_systematics.C"

//#include "config/Lambda1520_config_cpm222_2015.C" // for 2015 (0-90%)
//#include "config/Lambda1520_config_cpm112.C" // like 2010 (0-90%)

// HACK Neelima
#include "config/Lambda1520_config_cpm222_2018.C" // for 2015 (0-90%)



void config()
{
  
  
  // input data
  datadirname     = basedir;
  datatagname     = "AnalysisResults_1783_20200921-1842-DATA"; //
  //"AnalysisResults.DATA.2015_1021"; // pass2 data: pass1 runs
  //"AnalysisResults.DATA.2015_1012"; // pass1 data: pass1 runs
  //"AnalysisResults.DATA.2015_866";  // pass1 data: pass1 runs
  triggersel      = "_INT7";
  
  // input mc
  mcdirname       = basedir;
  mctagname       = "AnalysisResultsMC";
  mctrigger       = "_INT7";
  
  // output data
  outdirname      = outbasedir + "/December2020/";
  
  // Turn ON scale efficiency flag
  ScaledEff       = kTRUE;
  
  // reconfigure IO
  reconfigIO();

  // systematic file
  //sys_2015();
  
  // QA trigger
  triggerQA      = "_INT7";

  return;
  /*
  Bool_t _centBinSkip[] = {1, 1, 1, 1, 1, 0};
  Bool_t _ptBinSkip[]     = {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1};
  
  for (Int_t i = 0; i < ncentBins; ++i){
    centBinSkip[i] = _centBinSkip[i];
    for (Int_t j = 0; j < nptBins; ++j)
      ptBinSkip[i][j] = _ptBinSkip[j];  
  }
  
  */
}

#endif
