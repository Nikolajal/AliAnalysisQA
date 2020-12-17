#include "../utils/style.C"
#include "../config.C"

TString Trigger         = "";
Float_t MinPt           = 0.1;
Float_t MaxP            = 5.;
TString detname[3]      = {"TPC", "TOF", "TPC-dEdx"};
TString partname[2]     = {"kaon", "proton"};
Double_t Xmin[3]        = {-10., -10., 0.,};
Double_t Xmax[3]        = {10., 10., 500.};
TString histoname[3][2] = { "cutQuality.TPC_nsigmaK_VsPtpc_pTPC_K", "cutQuality.TPC_nsigmaPro_VsPtpc_pTPC_p",
			    "cutQuality.TOF_nsigmaK_vsP_p_K", "cutQuality.TOF_nsigmaPro_vsP_p_p",
			    "cutKaon.dEdx_VsPtpc_pTPC_sTPC", "cutProton.dEdx_VsPtpc_pTPC_sTPC" };


void DrawPID(TString datatagname, TString extratag);
void DrawPID_detector_particle(TString datatagname, Int_t det, Int_t part, TString extratag);
void DrawTPCKaonSelectionTPConly(Double_t MaxPk = 0.6); // 2010 Test03 -- TPC Kaon
void DrawTPCKaonSelectionTPCTOF(); //-- TPC + mendetry TOF kaon
void DrawTPCProtonSelectionTPConly(Double_t MaxPr = 1.10); // 2010 Test03 -- TPC proton
void DrawTPCProtonSelectionTPCTOF(); //-- TPC + mendetry TOF proton
void DrawTOFKaonSelectionTPCTOF();//-- TOF kaon
void DrawTOFProtonSelectionTPCTOF(); //-- TOF proton


void DrawPID_run2()
{
  config();
  //
  Trigger = triggerQA;
  //
  figuresdirname += Form("%s/PIDQA", mctagname.Data());
  gROOT->ProcessLine(Form(".! mkdir -p %s", figuresdirname.Data()) );
  DrawPID(datatagname, Trigger); 
}


void DrawPID(TString datatagname, TString extratag)
{
  for (Int_t i = 0; i < 3; i++)
    for (Int_t j = 0; j < 2; j++)
      DrawPID_detector_particle(datatagname, i, j, extratag);
}


void DrawPID_detector_particle(TString datatagname, Int_t det, Int_t part, TString extratag)
{
  style();

  //Data File
  TString filename = datadirname;
  filename += datatagname;
  filename += ".root";
  TFile *findata = TFile::Open(filename);
  if(det == 0 && part == 00)
    cout << " ****** File to make QA:  " << filename.Data() << ",  trigger = " << Trigger.Data() << endl << endl;
  TList *lindata = (TList*)findata->Get(Form("RsnOut_Lambda1520_PbPb%s", Trigger.Data()));
  //
  //
  TH2 *hin = (TH2 *)lindata->FindObject(histoname[det][part].Data());
  
  if (det == 0 || det == 2) {
    MinPt = 0.1;
    MaxP = 3.0;
  }
  if (det == 1) {
    MinPt = 0.3;
    MaxP = 6.0;
  }

  TCanvas *cCanvas = new TCanvas(Form("c_%s%s_%s", detname[det].Data(), partname[part].Data(), extratag.Data()), Form("c_%s%s_%s", detname[det].Data(), partname[part].Data(), extratag.Data()), 800, 800);
  cCanvas->SetLogx();
  cCanvas->SetLogz();
  if (det != 2) {
    cCanvas->SetGridx();
    cCanvas->SetGridy();
  }
  
  TH1 *hframe = cCanvas->DrawFrame(MinPt, Xmin[det], MaxP, Xmax[det]);
  hframe->GetXaxis()->SetMoreLogLabels();
  hframe->GetXaxis()->SetNoExponent(); 
  
  hin->Draw("col,same");
  cCanvas->RedrawAxis("g");
  
  TLatex *latex = new TLatex(0.90, 0.9, Form("%s PID response, %s hypothesis", detname[det].Data(), partname[part].Data()));
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->SetTextAlign(33);
  latex->Draw("same");
  
  cout << "det" << det << "part" << part << endl; 
  switch (det) {
  case 0:
    switch (part) {
    case 0:
      hframe->SetTitle(";#it{p}_{TPC} (GeV/#it{c});TPC n#sigma_{K}");
      DrawTPCKaonSelectionTPConly(0.60); // run2 Test03
      DrawTPCKaonSelectionTPCTOF();
      break; 
    case 1:
      hframe->SetTitle(";#it{p}_{TPC} (GeV/#it{c});TPC n#sigma_{p}");
      DrawTPCProtonSelectionTPConly(1.1);  // run2 Test03
      DrawTPCProtonSelectionTPCTOF();
      break;
    }
    break;
  case 1:
    switch (part) {
    case 0:
      hframe->SetTitle(";#it{p} (GeV/#it{c});TOF n#sigma_{K}");
      DrawTOFKaonSelectionTPCTOF();
      break;
    case 1:
      hframe->SetTitle(";#it{p} (GeV/#it{c});TOF n#sigma_{p}");
      DrawTOFProtonSelectionTPCTOF();
      break;
    }
    break;
  case 2:
    hframe->SetTitle(";#it{p}_{TPC} (GeV/#it{c});TPC dE/dx (a.u.)");
    break;
  } 


  cCanvas->SaveAs(Form("%s/DrawPID_%s%s%s.png", figuresdirname.Data(), detname[det].Data(), partname[part].Data(), extratag.Data()));
}

void DrawTPCPionSelectionTPConly(Double_t MaxPi = MaxP)
{
  
  Double_t x[12] = {MinPt, 0.20, 0.20, 0.30, 0.30, MaxPi,
		    MaxPi, 0.30, 0.30, 0.20, 0.20, MinPt};

  Double_t y[12] = { 3.00, 3.00, 3.00, 3.00, 3.00, 3.00,
		     -3.00, -3.0, -3.0, -3.0, -3.0, -3.0};
 
  TPolyLine *pl = new TPolyLine(12, x, y);
  pl->SetLineWidth(5);
  pl->SetLineStyle(1);
  pl->Draw();
   
}


void DrawTPCKaonSelectionTPConly(Double_t MaxPk = 0.60) // 2018  -- TPC Kaon
{

  Double_t x[12] = {MinPt, 0.20, 0.20, 0.40, 0.40, MaxPk,
		    MaxPk, 0.40, 0.40,  0.20, 0.20, MinPt};

  Double_t y[12] = { 4.00, 4.00, 3.00, 3.00, 2.00, 2.00,
		     -2.00, -2.00, -3.00, -3.00, -4.00, -4.00};

  TPolyLine *pl = new TPolyLine(12, x, y);

  pl->SetLineWidth(5);
  pl->SetLineStyle(1);
  pl->Draw();
   
  }


void DrawTPCProtonSelectionTPConly(Double_t MaxPr = 1.10) // 2018  -- TPC proton
{

  Double_t x[12] = {MinPt, 0.25, 0.25, 0.70, 0.70, MaxPr,
		    MaxPr, 0.70, 0.70, 0.25, 0.25, MinPt};

  Double_t y[12] = { 4.00, 4.00, 3.00, 3.00, 2.00, 2.00,
		     -2.00, -2.00, -3.00, -3.00, -4.00, -4.00};

  TPolyLine *pl = new TPolyLine(12, x, y);


  pl->SetLineWidth(5);
  pl->SetLineStyle(1);
  pl->Draw();
   
  }


void DrawTPCPionSelectionTPCTOF() 
{

  Double_t x[4] = {MaxP,  0.4,  0.4, MaxP};
  Double_t y[4] = {-5.0, -5.0,  5.0, 5.0};
  TPolyLine *pl = new TPolyLine(4, x, y);
  pl->SetLineWidth(5);
  pl->SetLineStyle(7);
  pl->Draw();
  
}

void DrawTPCKaonSelectionTPCTOF() //-- TPC + mendetry TOF kaon
{

  Double_t x[4] = {MaxP,  0.45,  0.45, MaxP};
  Double_t y[4] = {-5.0, -5.0,  5.0, 5.0};
  TPolyLine *pl = new TPolyLine(4, x, y);
  pl->SetLineWidth(5);
  pl->SetLineStyle(7);
  pl->Draw();
  
}

void DrawTPCProtonSelectionTPCTOF() //-- TPC + mendetry TOF proton
{

  Double_t x[4] = {MaxP,  0.8,  0.8, MaxP};
  Double_t y[4] = {-5.0, -5.0,  5.0, 5.0};
  TPolyLine *pl = new TPolyLine(4, x, y);
  pl->SetLineWidth(5);
  pl->SetLineStyle(7);
  pl->Draw();
  
}

void DrawTOFKaonSelectionTPCTOF() //-- TOF kaon
{

  Double_t x[4] = {MaxP,  0.45,  0.45, MaxP};
  Double_t y[4] = {-3.0, -3.0,  3.0, 3.0};
  TPolyLine *pl = new TPolyLine(4, x, y);
  pl->SetLineWidth(5);
  pl->SetLineStyle(1);
  pl->Draw();
  
}

void DrawTOFProtonSelectionTPCTOF() //-- TOF proton
{

  Double_t x[4] = {MaxP,  0.8,  0.8, MaxP};
  Double_t y[4] = {-3.0, -3.0,  3.0, 3.0};
  TPolyLine *pl = new TPolyLine(4, x, y);
  pl->SetLineWidth(5);
  pl->SetLineStyle(1);
  pl->Draw();
  
}
