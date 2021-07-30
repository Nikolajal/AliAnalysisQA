#include "./inc/AliAnalysisQA.h"

void RunQualityCheck()  {
    
    // Generate, if necessary, all the folders for the output
    fGenerateOutputDirectories();
    if ( !fSetInputHistograms() ) { cout << "ahiahi" << endl; return;}
    
    fCheckFllTrack();
    fCheckFllTrack("Kaons");
    fCheckSelection();
    fCheckSelection("Kaons","TOF");
    fCheckPIDSigma();
    fCheckPIDSigma("Kaons","TOF");
    fCheckVertexPosition();
}
