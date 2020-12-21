# ifndef    ALIANALYSISQA_h
# define    ALIANALYSISQA_h
//
#include "../src/AliAnalysisQAPID.cxx"
#include "../src/AliAnalysisQAStyle.cxx"
#include "../src/AliAnalysisQATrack.cxx"
//
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
//
#endif
