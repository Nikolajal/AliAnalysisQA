#include "config.C"
#include "utils/style.C"

Double_t trUpcent0 = 5100.;
Double_t trUpcent1 = 3500.;
Double_t trUpcent2 = 2200.;
Double_t trUpcent3 = 1500.;
Double_t trUpcent4 = 1000.;
Double_t trUpcent5 = 600.;


void Lambda1520_centralityQA()
{
  
  config();
  style();
  gROOT->ProcessLine(Form(".! mkdir -p %s/%s/CENTQA", figuresdirname.Data(), mctagname.Data()));
  
  // open data
  TString filename = datadirname;
  filename        += datatagname;
  filename        += ".root";
  TFile *fdt       = TFile::Open(filename);
  TList *ldt       = (TList *)fdt->Get(Form("RsnOut_Lambda1520_PbPb%s", triggerQA.Data()));
  TH1 *hCent_dt    = (TH2 *)ldt->FindObject(Form("Lambda1520_PbPb%s_eventCentrality", triggerQA.Data()));
  hCent_dt->Scale(1. / hCent_dt->GetEntries());
  
  TH2 *hTrkCent_dt          = (TH2 *)ldt->FindObject(Form("Lambda1520_PbPb%s_trackletsCentrality", triggerQA.Data()));
  TProfile *hTrkCent_dt_pfx = hTrkCent_dt->ProfileX("hTrkCent_dt_pfx");

  // create canvas for tracklets
   TCanvas *cTrk   = new TCanvas("cTrk", "cTrk", 800, 800);
   cTrk->SetLogz();
   cTrk->SetLogy();
   cTrk->cd();
   hTrkCent_dt->SetTitle("Tracklets; centrality(%); entries");
   hTrkCent_dt->Draw("colz");
   
   cTrk->SaveAs(Form("%s/%s/CENTQA/cTrkletdata%s.png", figuresdirname.Data(), mctagname.Data(), triggerQA.Data()));
   
  
  // open mc data
  filename         = mcdirname;
  filename        += mctagname;
  filename        += ".root";
  TFile *fmc       = TFile::Open(filename);
  TList *lmc       = (TList *)fmc->Get(Form("RsnOut_Lambda1520_PbPb%s", mctrigger.Data()));
  TH1 *hCent_mc    = (TH2 *)lmc->FindObject(Form("Lambda1520_PbPb%s_eventCentrality", mctrigger.Data()));
  hCent_mc->Scale(1. / hCent_mc->GetEntries());
  
  TH2 *hTrkCent_mc          = (TH2 *)lmc->FindObject(Form("Lambda1520_PbPb%s_trackletsCentrality", mctrigger.Data()));
  TProfile *hTrkCent_mc_pfx = hTrkCent_mc->ProfileX("hTrkCent_mc_pfx");

  TCanvas *cTrkMC   = new TCanvas("cTrkMC", "cTrkMC", 800, 800);
   cTrkMC->SetLogz();
   cTrkMC->SetLogy();
   cTrkMC->cd();
   hTrkCent_mc->SetTitle("Tracklets; centrality(%); entries");
   hTrkCent_mc->Draw("colz");
   
   cTrkMC->SaveAs(Form("%s/%s/CENTQA/cTrkletMC%s.png", figuresdirname.Data(), mctagname.Data(), triggerQA.Data()));
   
  
  TCanvas *cCent   = new TCanvas("cCent", "cCent", 800, 800);
  TH1 *hf          = cCent->DrawFrame(0., 0., 90., 0.025, ";centrality percentile;normalised counts");
  hf->GetYaxis()->SetNdivisions(504);
  SetHistoStyle(hCent_dt, 20, kRed+1);
  SetHistoStyle(hCent_mc, 25, kAzure-3);  
  hCent_dt->Draw("same");
  hCent_mc->Draw("same");
  TLegend *legend = new TLegend(0.2, 0.75, 0.45, 0.9);
  legend->SetBorderSize(0);  
  legend->AddEntry(hCent_dt, "data", "pl");
  legend->AddEntry(hCent_mc, "MC", "pl");
  legend->Draw("same");
  // save as .pdf
 
  cCent->SaveAs(Form("%s/%s/CENTQA/cCentralityQA%s.png", figuresdirname.Data(), mctagname.Data(), triggerQA.Data()));
  
  TCanvas *cTrkCent = new TCanvas("cTrkCent", "cTrkCent", 800, 800);
  cTrkCent->SetLogy();
  cTrkCent->DrawFrame(0., 10., 90, 3000., ";centrality percentile;#LTN_{tracklets}#GT");
  SetHistoStyle(hTrkCent_dt_pfx, 20, kRed+1);
  SetHistoStyle(hTrkCent_mc_pfx, 25, kAzure-3);  
  hTrkCent_dt_pfx->Draw("same");
  hTrkCent_mc_pfx->Draw("same");
  
  legend = new TLegend(0.65, 0.75, 0.9, 0.9);
  legend->SetBorderSize(0);  
  legend->AddEntry(hTrkCent_dt_pfx, "data", "pl");
  legend->AddEntry(hTrkCent_mc_pfx, "MC", "pl");
  legend->Draw("same");
  
  // save as .pdf
  cTrkCent->SaveAs(Form("%s/%s/CENTQA/cCentralityQA_tracklets%s.png", figuresdirname.Data(), mctagname.Data(), triggerQA.Data()));
  
  TCanvas *cTrkCentRatio = new TCanvas("cTrkCentRatio", "cTrkCentRatio", 800, 800);
  cTrkCentRatio->DrawFrame(0., 0.9, 90, 1.5, ";centrality percentile;MC / data #LTN_{tracklets}#GT ratio");
  TH1 *hTrkCent_mc_pfx_r = (TH1 *)hTrkCent_mc_pfx->Clone("hTrkCent_mc_pfx_r");
  hTrkCent_mc_pfx_r->Divide(hTrkCent_dt_pfx);
  hTrkCent_mc_pfx_r->SetLineWidth(3);
  hTrkCent_mc_pfx_r->Draw("same,histo");
  
  // save as .pdf
  cTrkCentRatio->SaveAs(Form("%s/%s/CENTQA/cCentralityQA_tracklets_ratio%s.png", figuresdirname.Data(), mctagname.Data(), triggerQA.Data()));
  
  /* loop over centrality bins */
  Float_t trkMax[3] = {3500., 1500., 500.};
  Float_t yMin[3]   = {1.e-7, 1.e-7, 1.e-7};
  Float_t yMax[3]   = {1.e-1};

  // create root file to store tracklets per centrality
  gROOT->ProcessLine(Form(".! mkdir -p %s", resultsdirname.Data()));
  TString foutname = resultsdirname;
  foutname += "Lambda1520_tracklets";
  foutname += triggerQA;
  foutname += ".root";
  TFile *fout = TFile::Open(foutname.Data(), "RECREATE");
  
  cout << "Tracklets are saved in File = "<< foutname.Data() << endl;
  
  // centrality checks
  for (Int_t icent = 0; icent < ncentBins; icent++) {

    // trigger per centrality
     /** get the data **/
   
    if (triggersel.EqualTo("Auto")) {
      if (centTrigger.count(centname[icent].Data()) == 0) {
	std::cout << " ***** WARNING: Auto trigger selection requested for undefined centrality: " << centname[icent] << std::endl;
      } else {
	std::cout << " ***** INFO: Auto trigger selection requested" << std::endl;
	triggerQA = centTrigger[centname[icent].Data()];
      }
    }
 
    std::cout << " ***** Centrality = " << centname[icent] << " , "
	      << " triggersel = " << triggersel.Data() << " , "
	      << " triggerQA = " << triggerQA.Data() << std::endl;
    
    
    // get related histos
    ldt         = (TList *)fdt->Get(Form("RsnOut_Lambda1520_PbPb%s", triggerQA.Data()));
    hCent_dt    = (TH2 *)ldt->FindObject(Form("Lambda1520_PbPb%s_eventCentrality", triggerQA.Data()));

    
    TList *lmc       = (TList *)fmc->Get(Form("RsnOut_Lambda1520_PbPb%s", mctrigger.Data()));
    TH1 *hCent_mc00  = (TH2 *)lmc->FindObject(Form("Lambda1520_PbPb%s_eventCentrality", mctrigger.Data()));

    // count number of events in centrality range
    Int_t nEvents_dt = hCent_dt->Integral(hCent_dt->FindBin(centBin[icent]) + 0.001,
					  hCent_dt->FindBin(centBin[icent + 1]) - 0.001);
    
    Int_t nEvents_mc = hCent_mc00->Integral(hCent_mc00->FindBin(centBin[icent]) + 0.001,
					    hCent_mc00->FindBin(centBin[icent + 1]) - 0.001);
    
    cout << endl<< "**** Data: nEvents **** in"<< centname[icent].Data() <<" ***** = "<< nEvents_dt << endl;
    cout << endl<< "****   MC: nEvents **** in"<< centname[icent].Data() <<" ***** = "<< nEvents_mc << endl << endl;
    
    hCent_dt->Scale(1. / hCent_dt->GetEntries());
  
    hTrkCent_dt     = (TH2 *)ldt->FindObject(Form("Lambda1520_PbPb%s_trackletsCentrality", triggerQA.Data()));
    hTrkCent_dt_pfx = hTrkCent_dt->ProfileX(Form("hTrkCent_dt_pfx_%d", icent));

 
    // prepare canvases   
    TCanvas *c = new TCanvas(Form("cCent_noadj_%d", icent), Form("cCent_noadj_%d", icent), 800, 800);
    c->SetLogy();
    if(icent == 0) c->DrawFrame(0., 1.e-7, trUpcent0, 1., ";N_{tracklets};normalised counts");
    if(icent == 1) c->DrawFrame(0., 1.e-7, trUpcent1, 1., ";N_{tracklets};normalised counts");
    if(icent == 2) c->DrawFrame(0., 1.e-7, trUpcent2, 1., ";N_{tracklets};normalised counts");
    if(icent == 3) c->DrawFrame(0., 1.e-7, trUpcent3, 1., ";N_{tracklets};normalised counts");
    if(icent == 4) c->DrawFrame(0., 1.e-7, trUpcent4, 1., ";N_{tracklets};normalised counts");
    if(icent == 5) c->DrawFrame(0., 1.e-7, trUpcent5, 1., ";N_{tracklets};normalised counts");

    //****************************************************************************************//
    // *************************** No Multiplicity adjustment ********************************//
    
    // multiplicity projection
    TH1 *hTrkCent_dt_py = hTrkCent_dt->ProjectionY(Form("hTrkCent_dt_py%d", icent), hTrkCent_dt->GetXaxis()->FindBin(centBin[icent] + 0.001), hTrkCent_dt->GetXaxis()->FindBin(centBin[icent + 1] - 0.001));

    hTrkCent_dt_py->Scale(1. / hTrkCent_dt_py->GetEntries());
      // event outliers counting
    
    Int_t nbins = hTrkCent_dt_py->GetNbinsX();
    
    Double_t  TotEvnt, TotEvnt_lo, TotEvnt_hg;
    
    TotEvnt = hTrkCent_dt_py->Integral(1, nbins);
    
    if (icent == 0){
      TotEvnt_lo = hTrkCent_dt_py->Integral(1, hTrkCent_dt_py->FindBin(1500)); // 0-10%
      TotEvnt_hg = hTrkCent_dt_py->Integral(hTrkCent_dt_py->FindBin(4100), hTrkCent_dt_py->FindBin(5000)); //0-10%
    }
    if (icent == 1) {
      TotEvnt_lo = hTrkCent_dt_py->Integral(1, hTrkCent_dt_py->FindBin(700)); //10-30%
      TotEvnt_hg = hTrkCent_dt_py->Integral(hTrkCent_dt_py->FindBin(2600), hTrkCent_dt_py->FindBin(5000)); //10-30%
    }

    if (icent == 2) {
      TotEvnt_lo = hTrkCent_dt_py->Integral(1, hTrkCent_dt_py->FindBin(400));  //30-40%
      TotEvnt_hg = hTrkCent_dt_py->Integral(hTrkCent_dt_py->FindBin(1200), hTrkCent_dt_py->FindBin(5000)); //30-40%
    }
    
    if (icent == 3) {
      TotEvnt_lo = hTrkCent_dt_py->Integral(1, hTrkCent_dt_py->FindBin(200)); //40-50%
      TotEvnt_hg = hTrkCent_dt_py->Integral(hTrkCent_dt_py->FindBin(800), hTrkCent_dt_py->FindBin(5000)); //40-50%
    }
    
    if (icent == 4) {
      TotEvnt_lo = hTrkCent_dt_py->Integral(1, hTrkCent_dt_py->FindBin(10)); //50-70%
      TotEvnt_hg = hTrkCent_dt_py->Integral(hTrkCent_dt_py->FindBin(500), hTrkCent_dt_py->FindBin(5000)); //50-70%
    }
    
    if (icent == 5) {
      TotEvnt_lo = hTrkCent_dt_py->Integral(1, hTrkCent_dt_py->FindBin(1)); //70-90%
      TotEvnt_hg = hTrkCent_dt_py->Integral(hTrkCent_dt_py->FindBin(180), hTrkCent_dt_py->FindBin(5000)); //70-90%
    }
    
    cout << "fraction of outliers = " << 100 * ((TotEvnt_lo + TotEvnt_hg) / TotEvnt) << endl << endl;
    
    
    TH1 *hTrkCent_mc_py = hTrkCent_mc->ProjectionY(Form("hTrkCent_mc_py%d", icent), hTrkCent_mc->GetXaxis()->FindBin(centBin[icent] + 0.001), hTrkCent_mc->GetXaxis()->FindBin(centBin[icent + 1]  - 0.001));
    hTrkCent_mc_py->Scale(1. / hTrkCent_mc_py->GetEntries());
    
    SetHistoStyle(hTrkCent_dt_py, 20, kRed+1);
    SetHistoStyle(hTrkCent_mc_py, 25, kAzure-3);
        
    hTrkCent_dt_py->Draw("same");
    hTrkCent_mc_py->Draw("same");
    
    TLatex *l_average_dt = new TLatex(0.9, 0.9, Form("#LTN_{trk}#GT^{data} = %.1f", hTrkCent_dt_py->GetMean()));
    l_average_dt->SetTextColor(kRed+1);
    l_average_dt->SetNDC(kTRUE);
    l_average_dt->SetTextAlign(33);
    l_average_dt->Draw("same");
    
    TLatex *l_average_mc = new TLatex(0.9, 0.8, Form("#LTN_{trk}#GT^{MC} = %.1f", hTrkCent_mc_py->GetMean()));
    l_average_mc->SetTextColor(kAzure-3);
    l_average_mc->SetNDC(kTRUE);
    l_average_mc->SetTextAlign(33);
    l_average_mc->Draw("same");
    
    // save as .pdf
    c->SaveAs(Form("%s/%s/CENTQA/cCentralityQA_tracklets_cent_%s%s_noadj.png", figuresdirname.Data(), mctagname.Data(), centname[icent].Data(), triggerQA.Data()));


    //****************************************************************************************//
    
    // ************** multiplicity  adjusted monte Carlo tracklets****************************//
    
    TCanvas *c1 = new TCanvas(Form("cCent_adj_%d", icent), Form("cCent_adj_%d", icent), 800, 800);
    c1->SetLogy();
    if(icent == 0) c1->DrawFrame(0., 1.e-7, trUpcent0, 1., ";N_{tracklets};normalised counts");
    if(icent == 1) c1->DrawFrame(0., 1.e-7, trUpcent1, 1., ";N_{tracklets};normalised counts");
    if(icent == 2) c1->DrawFrame(0., 1.e-7, trUpcent2, 1., ";N_{tracklets};normalised counts");
    if(icent == 3) c1->DrawFrame(0., 1.e-7, trUpcent3, 1., ";N_{tracklets};normalised counts");
    if(icent == 4) c1->DrawFrame(0., 1.e-7, trUpcent4, 1., ";N_{tracklets};normalised counts");
    if(icent == 5) c1->DrawFrame(0., 1.e-7, trUpcent5, 1., ";N_{tracklets};normalised counts");
    
    TH1 *hTrkCent_mc_py_adj = hTrkCent_mc->ProjectionY(Form("hTrkCent_mc_py%d", icent), hTrkCent_mc->GetXaxis()->FindBin(centBin[icent] + centAdjMC_lo[icent] + 0.001), hTrkCent_mc->GetXaxis()->FindBin(centBin[icent + 1] + centAdjMC_hi[icent] - 0.001));
    hTrkCent_mc_py->Scale(1. / hTrkCent_mc_py->GetEntries());
    
    SetHistoStyle(hTrkCent_dt_py, 20, kRed+1);
    SetHistoStyle(hTrkCent_mc_py_adj, 25, kAzure-3);
   
    
    hTrkCent_dt_py->Draw("same");
    hTrkCent_mc_py_adj->Draw("same");
   
    l_average_dt = new TLatex(0.9, 0.9, Form("#LTN_{trk}#GT^{data} = %.1f", hTrkCent_dt_py->GetMean()));
    l_average_dt->SetTextColor(kRed+1);
    l_average_dt->SetNDC(kTRUE);
    l_average_dt->SetTextAlign(33);
    l_average_dt->Draw("same");
   
    l_average_mc = new TLatex(0.9, 0.8, Form("#LTN_{trk}#GT^{MC} = %.1f", hTrkCent_mc_py_adj->GetMean()));
    l_average_mc->SetTextColor(kAzure-3);
    l_average_mc->SetNDC(kTRUE);
    l_average_mc->SetTextAlign(33);
    l_average_mc->Draw("same");
    
    // save as .pdf
    c1->SaveAs(Form("%s/%s/CENTQA/cCentralityQA_tracklets_cent_%s%s_adj.png", figuresdirname.Data(), mctagname.Data(), centname[icent].Data(), triggerQA.Data()));


    // write to file
    fout->cd();
    hTrkCent_dt_py->Write();
    
  }
  
  fout->Close();
  
}
