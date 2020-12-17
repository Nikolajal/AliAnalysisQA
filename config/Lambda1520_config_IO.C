#ifndef LAMBDA1520_CONFIG_IO
#define LAMBDA1520_CONFIG_IO

/*************************************************************************
  deafult directories and files
**************************************************************************/
TString basedir        = "~/Downloads/";
TString outbasedir     = "~/Downloads/outputdir";
//
TString outdirname      = "UNDEFINED/";
TString figuresdirname  = outdirname + "figures/";
TString resultsdirname  = outdirname + "results/";
TString rsnmodeldirname = outdirname + "rsnmodel/";
//
TString datalistname   = "RsnOut_f0";
TString datadirname    = basedir + "UNDEFINED/";
TString datatagname    = "UNDEFINED";
TString triggersel     = "UNDEFINED";
TString triggerQA      = "_INT7";

//
TString mcdirname      = basedir + "UNDEFINED/";
TString mctagname      = "UNDEFINED";
TString mctrigger      = "UNDEFINED";
Bool_t  ScaledEff      = kFALSE;
//
// EffMatrix related
TString effmatrixdirname = basedir + "EffMatrixTask_Run2/";
TString effmatrixrefname = "EffMatrix_LHC20e3abc_222runs_vAN-20200824"; // this must come from the general-purpose MC
TString effmatrixtagname = "EffMatrix_LHC19h6abc_2018qr_pass3runs_vAN-20200721"; // this most come from the dedicated production?
//
// files for results
TString yieldfilename     = resultsdirname + "Lambda1520_fit_DEFAULT_DEFAULT.root";
TString efffilename       = resultsdirname + "Lambda1520_eff_DEFAULT.root";
TString shapecorrfilename = resultsdirname + "Lambda1520_ptShapeCorrection_DEFAULT_BGBlastWave_constrained.root";
TString effcorrfilename   = resultsdirname + "Lambda1520_efficiencyCorrection_DEFAULT.root";
//
// results
TString resultsfilename   = resultsdirname + "Lambda1520_results_BGBlastWave_constrained.root";

const Double_t deltacommon = -0.0025;

std::map<std::string, std::string> centTrigger = {
  {"0_10"  , "_Merge"} ,
  {"0_20"  , "_INT7"} ,
  {"10_30" , "_INT7"} ,
  {"20_50" , "_INT7"} ,
  {"30_40" , "_Merge"} ,
  {"30_50" , "_Merge"} ,
  {"40_50" , "_Merge"} ,
  {"50_60" , "_INT7"} ,
  {"50_70" , "_INT7"} ,
  {"50_80" , "_INT7"} ,
  {"60_70" , "_INT7"} ,
  {"70_80" , "_INT7"} ,
  {"70_90" , "_INT7"} ,
  {"80_90" , "_INT7"} 
};

/*************************************************************************
  systematic directories and files
**************************************************************************/
TString sysdirname = resultsdirname + "Systematics/";
TString sysfiguresdirname = figuresdirname + "Systematics/";

std::map<std::string, std::pair<std::string, std::string>> sysdatamap = {
  {"DEFAULT"      , {"Lambda1520_fit_DEFAULT_DEFAULT.root"             , ""} }
};

void reconfigIO() {

  figuresdirname  = outdirname + "figures/";
  resultsdirname  = outdirname + "results/";
  rsnmodeldirname = outdirname + "rsnmodel/";

  yieldfilename     = resultsdirname + "Lambda1520_fit_DEFAULT_DEFAULT.root";
  efffilename       = resultsdirname + "Lambda1520_eff_DEFAULT.root";
  shapecorrfilename = resultsdirname + "Lambda1520_ptShapeCorrection_DEFAULT_BGBlastWave_constrained.root";
  effcorrfilename   = resultsdirname + "Lambda1520_efficiencyCorrection_DEFAULT.root";
  resultsfilename   = resultsdirname + "Lambda1520_results_BGBlastWave_constrained.root";

  sysdirname        = resultsdirname + "Systematics/";
  sysfiguresdirname = figuresdirname + "Systematics/";

}

#endif
