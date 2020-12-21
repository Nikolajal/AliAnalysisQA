#include "../inc/AliAnalysisQAPID.h"
//
//>->->->->->->->->->->->->->->
//
//  PID Checks on Selections
//
//>->->->->->->->->->->->->->->
//
void    fCheckSelection ( TString fDetector, TString fParticle )  {
    
    // Making the Detectors Directory
    gROOT->ProcessLine(Form(".! mkdir -p %s/%s/%s",fOutput_Directory.Data(),fOutput_Directory_PID.Data(),fDetector.Data()));
    
    // Open Data File and load List
    TFile  *fInputFile      =   TFile::Open(Form("%s/%s",fInputData_Directory.Data(),fInputData_FileName.Data()));
    TList  *fInputList      =   (TList*)fInputFile->Get(Form("%s",fInputData_TList.Data()));
    
    // Recover the Sigma Histogram
    TH2    *hSigmaDetPart   =   (TH2*)fInputList->FindObject(Form(fInputData_Det_Part.Data(),fDetector.Data(),"PID"));
    
    // Set Attributes
 
    // Drawing histogram output
    gROOT->SetBatch(kTRUE);
    TCanvas    *cSigmaDetPart   = new TCanvas();
    gPad                         ->SetLogz(kTRUE);
    gStyle                      ->SetOptStat(0);
    hSigmaDetPart               ->Draw("COLZ");
    cSigmaDetPart               ->SaveAs(Form("./%s/%s/%s/PID.pdf",fOutput_Directory.Data(),fOutput_Directory_PID.Data(),fDetector.Data()));
    
    gROOT->SetBatch(kFALSE);
}
//
void    fCheckAllDetectors ( TString fParticle )  {
    
    for ( auto fDetectorName:fDetectors )  {
        fCheckSelection(fDetectorName,fParticle);
    }
}
//
void    fCheckAllParticles ( TString fDetector )  {
    
    for ( auto fParticleName:fParticles )  {
        fCheckSelection(fDetector,fParticleName);
    }
}
//
void    fCheckAllSelections ( )  {
    
    for ( auto fDetectorName:fDetectors)  {
        
        for ( auto fParticleName:fParticles )  {
            
            fCheckSelection(fDetectorName,fParticleName);
        }
    }
}
