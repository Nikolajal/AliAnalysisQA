#include "./inc/AliAnalysisQA.h"

void RunQualityCheck()  {
    
    // Generate, if necessary, all the folders for the output
    fGenerateOutputDirectories();
    
    fCheckSelection("TOF","Kaon");
    //fCheckVertex();
}
