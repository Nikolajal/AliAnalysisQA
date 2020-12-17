#include "../utils/style.C"
#include "../config.C"
//**** change trigger and MCtrigger accordingly

TString histotagname, xaxisTitle;
Float_t minx = 0., maxx = 360.;
TString trigger = "";


void DrawTrackPhi(TString datatagname , TString mctagname, Float_t maxy);
void DrawTrackPhiOuter(TString datatagname , TString mctagname, Float_t maxy);
void DrawTrackEta(TString datatagname , TString mctagname, Float_t maxy);
void DrawTrack(TString datatagname , TString mctagname, Float_t maxy);
void DrawTrackVz();
void DrawTrackVz(TString datatagname, TString mctagname1, Float_t maxy);
void DrawTrackDCAxy();
void DrawTrackDCAz();
void DrawTrackcuts(TString datatagname );
void DrawTrackDCA(TString datatagname, TString mctagname, Float_t maxy);
  
void DrawTrack_run2()
{
  //
  style();
  config();
  // trigger as per config
  trigger = triggerQA;
  
  cout<< "Data trigger = " << trigger << ", MC trigger = " << mctrigger << endl;
  //
  //
  figuresdirname += Form("%s/TRACKQA", mctagname.Data());
  gROOT->ProcessLine(Form(".! mkdir -p %s", figuresdirname.Data()) );
  //
  // Vz distribution
  DrawTrackVz();
  // Phi distribution
  DrawTrackPhi(datatagname, mctagname, 4.);
  DrawTrackPhiOuter(datatagname, mctagname, 4.);
  // Eta distribution
  DrawTrackEta(datatagname, mctagname, 100.);
  // DCA distribution
  DrawTrackDCAz();
  DrawTrackDCAxy();
  // events and track cuts
  DrawTrackcuts(datatagname);
}

void DrawTrackPhi(TString datatagname , TString mctagname, Float_t maxy)
{
  histotagname = "cutQuality.Phi_phi_charge";
  minx         = 0.0;
  maxx         = 360.;
  xaxisTitle   = "#varphi (deg)";
  DrawTrack(datatagname, mctagname, maxy);
}

void DrawTrackPhiOuter(TString datatagname , TString mctagname, Float_t maxy)
{
  histotagname = "cutQuality.PhiOuterTPC_phiOuterTPC_charge";
  minx         = 0.0;
  maxx         = 360.;
  xaxisTitle   = "#varphi (deg)";
  DrawTrack(datatagname, mctagname, maxy);
}

void DrawTrackEta(TString datatagname , TString mctagname, Float_t maxy)
{
  histotagname = "cutQuality.Eta_eta_charge";
  minx         = -1.0;
  maxx         = 1.0;
  xaxisTitle   = "#eta";
  DrawTrack(datatagname, mctagname, maxy);
}



void DrawTrack(TString datatagname , TString mctagname, Float_t maxy)
{
  
  //Data File
  TString filename = datadirname;
  filename        += datatagname;
  filename        += ".root";
 
  TFile *findata   = TFile::Open(filename);
  TList *lindata   = (TList*)findata->Get(Form("RsnOut_Lambda1520_PbPb%s", trigger.Data()));
  TH1F *hevent     = (TH1F*)lindata->FindObject(Form("Lambda1520_PbPb%s_eventVtx", trigger.Data()));

  //Monte-Carlo File
  TString filenamemc = mcdirname;
  filenamemc        += mctagname;
  filenamemc        += ".root";
 
  TFile *finMC       = TFile::Open(filenamemc);
  TList *linMC       = (TList*)finMC->Get(Form("RsnOut_Lambda1520_PbPb%s", mctrigger.Data()));
  
  //Phi distribution
  TString plus = "+", minus = "-";
  
  
  TH2F *htrack_phi       = (TH2F*)lindata->FindObject(histotagname.Data());
  TH1 *htrack_phi_p      = htrack_phi->ProjectionX("htrack_phi_p", 2, 3);
  TH1 *htrack_phi_n      = htrack_phi->ProjectionX("htrack_phi_n", 1, 2);
  TH2F *htrack_phiMC     = (TH2F*)linMC->FindObject(histotagname.Data());
  TH1* htrack_phi_p_MC   = (TH2F*)htrack_phiMC->ProjectionX("htrack_phi_p_MC", 2, 3);
  TH1* htrack_phi_n_MC   = (TH2F*)htrack_phiMC->ProjectionX("htrack_phi_n_MC", 1, 2);
  Double_t ndatapositive = htrack_phi_p->GetEntries();
  Double_t ndatanegative = htrack_phi_n->GetEntries();
  Double_t nmcpositive   = htrack_phi_p_MC->GetEntries();
  Double_t nmcnegative   = htrack_phi_n_MC->GetEntries();
  Double_t nevents       = hevent->GetEntries();
  htrack_phi_p->Scale(1/nevents);
  htrack_phi_n->Scale(1/nevents);

  htrack_phi_p_MC->Scale(ndatapositive/nmcpositive/nevents);
  htrack_phi_n_MC->Scale(ndatanegative/nmcnegative/nevents);
  
  htrack_phi_p->SetMarkerColor(kRed+1);
  htrack_phi_p->SetMarkerStyle(20);
  htrack_phi_n->SetMarkerColor(kAzure-3);
  htrack_phi_n->SetMarkerStyle(20);

  htrack_phi_p_MC->SetLineColor(kBlack);
  htrack_phi_p_MC->SetLineWidth(2);
  htrack_phi_p_MC->SetMarkerStyle(20);
  htrack_phi_p_MC->SetMarkerColor(kRed+1);
  htrack_phi_p_MC->SetFillStyle(3001);
  htrack_phi_p_MC->SetFillColor(kRed+1);

  htrack_phi_n_MC->SetLineColor(kBlack);
  htrack_phi_n_MC->SetLineWidth(2);
  htrack_phi_n_MC->SetMarkerStyle(20);
  htrack_phi_n_MC->SetMarkerColor(kAzure-3);
  htrack_phi_n_MC->SetFillStyle(3001);
  htrack_phi_n_MC->SetFillColor(kAzure-3);

  //LEGEND
  TLegend *leg_positive = new TLegend(0.65, 0.84, 0.9, 0.94);
  leg_positive->SetBorderSize(0);
  leg_positive->SetTextSize(0.04);
  leg_positive->AddEntry(htrack_phi_p, "data", "lp");
  leg_positive->AddEntry(htrack_phi_p_MC, "Monte Carlo", "f");
  
  TLegend *leg_negative = new TLegend(0.65, 0.84, 0.9, 0.94);
  leg_negative->SetBorderSize(0);
  leg_negative->SetTextSize(0.04);
  leg_negative->AddEntry(htrack_phi_n, "data", "lp");
  leg_negative->AddEntry(htrack_phi_n_MC, "Monte Carlo" ,"f");

  // TEXT
  TLatex *lat_positive = new TLatex(0.18, 0.88, "positively charged tracks");
  lat_positive->SetTextSize(0.04);
  lat_positive->SetNDC();
  TLatex *lat_negative = new TLatex(0.18, 0.88, "negatively charged tracks");
  lat_negative->SetTextSize(0.04);
  lat_negative->SetNDC();
  
  TCanvas *cCanvasp  = new TCanvas(Form("c_%s_%s_%s", datatagname.Data(), plus.Data(), histotagname.Data()), Form("c_%s_%s_%s", datatagname.Data(), plus.Data(), histotagname.Data()), 800, 800);
  cCanvasp->SetLogy();
  TH1 *hframep       = cCanvasp->DrawFrame(minx, 1.e-3*maxy, maxx, maxy);
  printf(" IM HERE: %s\n", xaxisTitle.Data()); 
  hframep->SetTitle(Form(";%s;normalised track counts", xaxisTitle.Data()));
  htrack_phi_p_MC->Draw("histo, same");
  htrack_phi_p->Draw("same");
  leg_positive->Draw();
  lat_positive->Draw();
  
  TCanvas *cCanvasn  = new TCanvas(Form("c_%s_%s_%s", datatagname.Data(), minus.Data(), histotagname.Data()), Form("c_%s_%s_%s", datatagname.Data(), minus.Data(), histotagname.Data()), 800, 800);
  cCanvasn->SetLogy();
  TH1 *hframen       = cCanvasn->DrawFrame(minx, 1.e-3*maxy, maxx, maxy);
  hframen->SetTitle(Form(";%s;normalised track counts", xaxisTitle.Data()));
  htrack_phi_n_MC->Draw("histo, same");
  htrack_phi_n->Draw("same");
  leg_negative->Draw();
  lat_negative->Draw();
  
  cCanvasp->SaveAs(Form("%s/trackphi_data_mc_%s_%s%s.png", figuresdirname.Data(), plus.Data(), histotagname.Data(), trigger.Data()));
  cCanvasn->SaveAs(Form("%s/trackphi_data_mc_%s_%s%s.png", figuresdirname.Data(), minus.Data(), histotagname.Data(), trigger.Data()));

}

void DrawTrackVz()
{
  histotagname = "Lambda1520_PbPb_eventVtx";
  minx         = -20.;
  maxx         = 20;
  xaxisTitle   = "Vz (cm)";
  DrawTrackVz(datatagname, mctagname, 3.e-2);
}

void DrawTrackVz(TString datatagname, TString mctagname1, Float_t maxy)
{
  
  //Data File
  TString filename1 = datadirname;
  filename1        += datatagname;
  filename1        += ".root";
  TFile *findata    = TFile::Open(filename1);
  cout << " *** Vz: data file *** "<< filename1 << " *****" << endl << endl;
  TList *lindata    = (TList*)findata->Get(Form("RsnOut_Lambda1520_PbPb%s", trigger.Data()));
  TH1F *hevent      = (TH1F*)lindata->FindObject(Form("Lambda1520_PbPb%s_eventVtx", trigger.Data()));
  Double_t nevents  = hevent->GetEntries();
  
  //Monte-Carlo File 1
  TString filenamemc1 = mcdirname;
  filenamemc1        += mctagname;
  filenamemc1        += ".root";
  cout << " *** Vz: MC file *** "<< filenamemc1 << " *****" << endl << endl;
  TFile *finMC        = TFile::Open(filenamemc1);
  TList *linMC        = (TList*)finMC->Get(Form("RsnOut_Lambda1520_PbPb%s", mctrigger.Data()));

  TH1F *hhisto        = (TH1F*)lindata->FindObject(Form("Lambda1520_PbPb%s_eventVtx", trigger.Data()));
  TH1F *hhistoMC      = (TH1F*)linMC->FindObject(Form("Lambda1520_PbPb%s_eventVtx", mctrigger.Data()));
  Double_t ndata      = hhisto->GetEntries();
  Double_t nmc        = hhistoMC->GetEntries();
  
  hhisto->Scale(1/nevents);
  hhistoMC->Scale(ndata/nmc/nevents); 

  hhisto->SetMarkerColor(kBlue);
  hhisto->SetMarkerStyle(20);
  hhisto->SetLineColor(kBlack);
  hhisto->SetLineWidth(2);
  hhisto->SetMarkerStyle(20);
  hhisto->SetMarkerColor(kCyan+1);
  hhisto->SetFillStyle(3001);
  hhisto->SetFillColor(kCyan+1);
  
  hhistoMC->SetLineColor(kBlack);
  hhistoMC->SetLineWidth(2);
  hhistoMC->SetMarkerStyle(20);
  hhistoMC->SetMarkerColor(kCyan+1);
  hhistoMC->SetFillStyle(3001);
  hhistoMC->SetFillColor(kCyan+1);
  
  //LEGEND
  TLegend *leg = new TLegend(0.2,0.8,0.35,0.9);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(hhisto, "data", "lp");
  leg->AddEntry(hhistoMC, "Monte Carlo", "f");

  TCanvas *cCanvas  = new TCanvas(Form("c_%s_%s", datatagname.Data(), histotagname.Data()), Form("c_%s_%s", datatagname.Data(), histotagname.Data()), 800, 800);
  cCanvas->SetLogy();
  TH1 *hframen      = cCanvas->DrawFrame(minx, .2e-2*maxy, maxx, maxy);
  hframen->SetTitle(Form(";%s;accepted events", xaxisTitle.Data()));
  hhistoMC->Draw("histo, same");
  hhisto->Draw("same");
  leg->Draw("same");
  TLatex *latex = new TLatex(0.90, 0.90, "ALICE, Pb-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->SetTextAlign(33);
  latex->Draw("same");
  TLatex *latex1 = new TLatex(0.90, 0.85, "run2 data");
  latex1->SetNDC();
  latex1->SetTextSize(0.04);
  latex1->SetTextAlign(33);
  latex1->Draw("same");
  
  
  cCanvas->SaveAs(Form("%s/Vz_Distribution_%s%s.png", figuresdirname.Data(), histotagname.Data(), trigger.Data()));

}


void DrawTrackDCAz()
{
  histotagname = "cutQuality.DCAzVsP_p_DCAz";
  minx         = -3.;
  maxx         = 3;
  xaxisTitle   = "DCAz (cm)";
  DrawTrackDCA(datatagname, mctagname, 1000.);
}


void DrawTrackDCAxy()
{
  histotagname = "cutQuality.DCAxyVsPt_pt_DCAxy";
  minx         = -0.5;
  maxx         = 0.5;
  xaxisTitle   = "DCAxy (cm)";
  DrawTrackDCA(datatagname, mctagname, 1000.);
}


void DrawTrackDCA(TString datatagname, TString mctagname, Float_t maxy)
{
  //Data File
  TString filename2 = datadirname;
  filename2        += datatagname;
  filename2        += ".root";
  
  TFile *findata    = TFile::Open(filename2);
  TList *lindata    = (TList*)findata->Get(Form("RsnOut_Lambda1520_PbPb%s", trigger.Data()));
  TH1F *hevent      = (TH1F*)lindata->FindObject(Form("Lambda1520_PbPb%s_eventVtx", trigger.Data()));

  //Monte-Carlo File 1
  TString filenamemc2 = mcdirname;
  filenamemc2        += mctagname;
  filenamemc2        += ".root";
 
  TFile *finMC        = TFile::Open(filenamemc2);
  TList *linMC        = (TList*)finMC->Get(Form("RsnOut_Lambda1520_PbPb%s", mctrigger.Data()));

  TH2F *hhisto2d   = (TH2F*)lindata->FindObject(histotagname.Data());
  TH2F *hhistoMC2d = (TH2F*)linMC->FindObject(histotagname.Data());
  TH1F *hhisto     = (TH1F*)hhisto2d->ProjectionY("hhisto");
  TH1F *hhistoMC   = (TH1F*)hhistoMC2d->ProjectionY("hhistoMC");
  Double_t ndata   = hhisto->GetEntries();
  Double_t nmc     = hhistoMC->GetEntries();
  Double_t nevents = hevent->GetEntries();
  hhisto->Scale(1/nevents);
  hhistoMC->Scale(ndata/nmc/nevents); 

  hhisto->SetMarkerColor(kBlue);
  hhisto->SetMarkerStyle(20);

  hhistoMC->SetLineColor(kBlack);
  hhistoMC->SetLineWidth(2);
  hhistoMC->SetMarkerStyle(20);
  hhistoMC->SetMarkerColor(kCyan+1);
  hhistoMC->SetFillStyle(3001);
  hhistoMC->SetFillColor(kCyan+1);

  //LEGEND
  TLegend *leg = new TLegend(0.65,0.84,0.9,0.94);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(hhisto, "data", "lp");
  leg->AddEntry(hhistoMC, "Monte Carlo", "f");


  TCanvas *cCanvas  = new TCanvas(Form("c_%s_%s", datatagname.Data(), histotagname.Data()), Form("c_%s_%s", datatagname.Data(), histotagname.Data()), 800, 800);
  cCanvas->SetLogy();
  TH1 *hframen      = cCanvas->DrawFrame(minx, 1.e-10*maxy, maxx, maxy);
  hframen->SetTitle(Form(";%s;accepted tracks", xaxisTitle.Data()));
  hhistoMC->DrawClone("histo, same");
  hhisto->DrawClone("same");
  leg->Draw();
  
  cCanvas->SaveAs(Form("%s/DCA_Normalised_Distribution_%s%s.png", figuresdirname.Data(), histotagname.Data(), trigger.Data()));

}


void DrawTrackcuts(TString datatagname )
{
 //Data File
  TString filename3 = datadirname;
  filename3        += datatagname;
  filename3        += ".root";
  TFile *findata    = TFile::Open(filename3);
  TList *lindata    = (TList*)findata->Get(Form("RsnOut_Lambda1520_PbPb%s", trigger.Data()));
  
  //DCAxy vs. pt distribution
  histotagname    = "cutQuality.DCAxyVsPt_pt_DCAxy";
  TCanvas *cDCAxy = new TCanvas("cDCAxy", "cDCAxy", 800, 800);
  cDCAxy->DrawFrame(0.0, -0.4, 10, 0.4, ";#it{p}_{T} (GeV/#it{c});DCAxy (cm)");
  cDCAxy->cd();
  TH2F *htrack_DCAxy = (TH2F*)lindata->FindObject(histotagname.Data()); 
  cDCAxy->SetLogz();
  htrack_DCAxy->Draw("same,colz");
  cDCAxy->SaveAs(Form("%s/DCAxy_track%s.png",  figuresdirname.Data(), trigger.Data()));


  //DCAz vs. p distribution
  histotagname   = "cutQuality.DCAzVsP_p_DCAz";
  TCanvas *cDCAz = new TCanvas("cDCAz", "cDCAz", 800, 800);
  cDCAz->DrawFrame(0.0, -3, 10, 3, ";#it{p} (GeV/#it{c});DCAz (cm)");
  cDCAz->cd();
  TH2F *htrack_DCAz = (TH2F*)lindata->FindObject(histotagname.Data());
  cDCAz->SetLogz();
  htrack_DCAz->Draw("same,colz");
  cDCAz->SaveAs(Form("%s/DCAz_track%s.png",  figuresdirname.Data(), trigger.Data()));


   //TPC dEdx -track
  histotagname   = "cutQuality.dEdx_VsPtpc_pTPC_sTPC";
  TCanvas *cdedx = new TCanvas("cdedx", "cdedx", 800, 800);
  cdedx->DrawFrame(0.15, 0., 10, 500, ";#it{p}_{T} (GeV/#it{c});TPC d#it{E}/d#it{x} (a.u.)");
  cdedx->cd();
  TH2F *htrack_TPCdEdx = (TH2F*)lindata->FindObject(histotagname.Data());
  htrack_TPCdEdx->Draw("same,colz");
  htrack_TPCdEdx->GetXaxis()->SetMoreLogLabels();
  htrack_TPCdEdx->GetXaxis()->SetNoExponent();
  cdedx->SetLogz();
  cdedx->SetLogx();
  cdedx->RedrawAxis("g");
  cdedx->SaveAs(Form("%s/dEdx_allTrack%s.png",  figuresdirname.Data(), trigger.Data()));

  /*
  //TPC dEdx -kaons
  histotagname = "cutKaon.dEdx_VsPtpc_pTPC_sTPC";
  TCanvas *cdedxkaon = new TCanvas("cdedxKaon", "cdedxKaon_%s", 800, 800);
  cdedxkaon->DrawFrame(0.15, 0., 10, 500, ";#it{p}_{T} (GeV/#it{c});TPC dE/dx_{ Kaon} (eV/cm)");
  cdedxkaon->cd();
  TH2F *hkaon_TPCdEdx = (TH2F*)lindata->FindObject(histotagname.Data());
  hkaon_TPCdEdx->GetXaxis()->SetMoreLogLabels();
  hkaon_TPCdEdx->GetXaxis()->SetNoExponent();
  cdedxkaon->SetLogz();
  cdedxkaon->RedrawAxis("g");
  hkaon_TPCdEdx->Draw("same,colz");
  cdedxkaon->SaveAs(Form("%s/dEdxKaon_data.png",  figuresdirname.Data()));


  //TPC dEdx - protons
  histotagname = "cutProton.dEdx_VsPtpc_pTPC_sTPC";
  TCanvas *cdedxproton = new TCanvas("cdedxProton_%s", "cdedxProton", 800, 800);
  cdedxproton->DrawFrame(0.15, 0., 10, 500, ";#it{p}_{T} (GeV/#it{c});TPC dE/dx_{ Proton} (eV/cm)");
  cdedxproton->cd();
  TH2F *hproton_TPCdEdx = (TH2F*)lindata->FindObject(histotagname.Data());
  hproton_TPCdEdx->GetXaxis()->SetMoreLogLabels();
  hproton_TPCdEdx->GetXaxis()->SetNoExponent();
  cdedxproton->SetLogz();
  cdedxproton->RedrawAxis("g");
  hproton_TPCdEdx->Draw("same,colz");
  cdedxproton->SaveAs(Form("%s/dEdxProton_data.png",  figuresdirname.Data()));
  */

}
