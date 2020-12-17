# ifndef    ALIANALYSISQA_h
# define    ALIANALYSISQA_h

#include "../src/AliAnalysisQAPID.cxx"
#include "../src/AliAnalysisQAStyle.cxx"

//>->->->->->->->->->->->->->->
//
//  Definition of Directories
//
//>->->->->->->->->->->->->->->
//
//>-> Input Data
//
TString fInputData_Directory    =   "~/cernbox/PhiCount/DataSet";
TString fInputData_FileName     =   "LHC10b.root";
TString fInputData_TList        =   "fQCOutputList";
TString fInputData_Detector     =   "fHist%s%s3";
//
//>-> Outpur Directory
//
TString fOutput_Directory       =   "Result";
TString fOutput_Directory_PID   =   "PIDQA";
TString fOutput_Directory_Track =   "TRKQA";

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
//>->->->->->->->->->->->->->->
//
//  PID Checks on Selections
//
//>->->->->->->->->->->->->->->
//
void    fCheckSelection ( TString fDetector )  {
    
    // Making the Detectors Directory
    gROOT->ProcessLine(Form(".! mkdir -p %s/%s/%s",fOutput_Directory.Data(),fOutput_Directory_PID.Data(),fDetector.Data()));
    
    // Open Data File and load List
    TFile  *fInputFile  =   TFile::Open(Form("%s/%s",fInputData_Directory.Data(),fInputData_FileName.Data()));
    TList  *fInputList  =   (TList*)fInputFile->Get(Form("%s",fInputData_TList.Data()));
    
    // Recover the Sigma Histogram
    TH2    *hSigma      =   (TH2*)fInputList->FindObject(Form(fInputData_Detector.Data(),fDetector.Data(),"PID"));
    
}
//
void    fCheckAllDetectors ( )  {
    
    for ( auto fDetectorName:fDetectors)  {
        fCheckSelection(fDetectorName);
    }
}

#endif
