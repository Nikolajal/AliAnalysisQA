# ifndef    ALIANALYSISQAVARIABLES_h
# define    ALIANALYSISQAVARIABLES_h
//>->->->->->->->->->->->->->->
//
//  Definition of Directories
//
//>->->->->->->->->->->->->->->
//
//>-> Input Data Directory
//
TString fInputData_Directory    =   "~/cernbox/PhiCount/DataSet";
TString fInputData_FileName     =   "LHC10b.root";
TString fInputData_TList        =   "fQCOutputList";
//
//>-> Input Data Trees and Histograms
//
TString fInputData_Det_Part     =   "fHist%s%s3";
TString fInputData_Vertex__     =   "fHist%s%s3";
//
//>-> Output Data Directory
//
TString fOutput_Directory       =   "Result";
TString fOutput_Directory_PID   =   "PIDQA";
TString fOutput_Directory_Track =   "TRKQA";
//
//>-> Output Data Trees and Histograms
//
#endif
