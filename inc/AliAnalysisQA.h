# ifndef    ALIANALYSISQA_h
# define    ALIANALYSISQA_h

# include "AliAnalysisQAPID.h"


//>->->->->->->->->->->->->->->
//
//  Definition of Directories
//
//>->->->->->->->->->->->->->->
//
//>-> Input Data
//
TString fInputData_Directory    =   "InputData";
TString fInputData_FileName     =   "LHC10";
TString fInputData_Extension    =   ".root";
//
//>-> Outpur Directory
//
TString fOutput_Directory       =   "Result";
TString fOutput_Directory_PID   =   "PID";
TString fOutput_Directory_Track =   "Track";

//>->->->->->->->->->->->->->->
//
//  Generation of Directories
//
//>->->->->->->->->->->->->->->
//
void fGenerateOutputDirectories()   {
    
    // Generate Output PID QA directory
    gROOT->ProcessLine(Form(".! mkdir -p %s/%s",fOutput_Directory.Data(),fOutput_Directory_PID.Data()));
    
    // Generate Output Track QA directory
    gROOT->ProcessLine(Form(".! mkdir -p %s/%s",fOutput_Directory.Data(),fOutput_Directory_Track.Data()));
}

#endif
