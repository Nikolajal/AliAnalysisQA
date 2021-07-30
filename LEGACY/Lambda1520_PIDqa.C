#include "config.C"
#include "utils/style.C"

Double_t Pt_TPC_K = 0.40; // DEFAULT = 300 MeV
Double_t Pt_TPC_P = 0.50; // DEFAULT = 500 MeV
Double_t Pt_TOF_K = 1.25; // DEFAULT = 1250 MeV
Double_t Pt_TOF_P = 2.00; // DEFAULT = 2000 MeV

void Lambda1520_PIDqa(Double_t Pt_TPC_k = Pt_TPC_K,
		      Double_t Pt_TPC_p = Pt_TPC_P,
		      Double_t Pt_TOF_k = Pt_TOF_K,
		      Double_t Pt_TOF_p = Pt_TOF_P,
		      Float_t shift = 0.0)
{
  
  config();
  
  style();

  TF1 *fgaus = (TF1 *)gROOT->GetFunction("gaus");
  
  // open data
  TString filename = datadirname;
  filename += datatagname;
  filename += ".root";
  TFile *fdt = TFile::Open(filename);
  TList *ldt = (TList *)fdt->Get(Form("RsnOut_f0"));
  
   cout << " ****** File to make QA:  " << filename.Data() << ",  trigger = " << triggerQA.Data() << endl;
 
  TH2 *htpc_ka_dt = (TH2 *)ldt->FindObject("cutQuality.TPC_nsigmaK_VsPtpc_pTPC_K");
  TH1 *htpc_ka_dt_py = htpc_ka_dt->ProjectionY("htpc_ka_dt_py",
					       htpc_ka_dt->GetXaxis()->FindBin(Pt_TPC_k - 0.005 + shift),
					       htpc_ka_dt->GetXaxis()->FindBin(Pt_TPC_k + 0.005 + shift));
  htpc_ka_dt_py->Fit(fgaus, "0q", "", -1., 1.);
  htpc_ka_dt_py->Scale(1. / fgaus->GetParameter(0));
  Double_t n5_tpc_ka_dt = htpc_ka_dt_py->Integral(htpc_ka_dt_py->FindBin(-5 + 0.001),
						   htpc_ka_dt_py->FindBin(+5 - 0.001));
  Double_t n4_tpc_ka_dt = htpc_ka_dt_py->Integral(htpc_ka_dt_py->FindBin(-4 + 0.001),
						   htpc_ka_dt_py->FindBin(+4 - 0.001));
  Double_t n3_tpc_ka_dt = htpc_ka_dt_py->Integral(htpc_ka_dt_py->FindBin(-3 + 0.001),
						   htpc_ka_dt_py->FindBin(+3 - 0.001));
  Double_t n2_tpc_ka_dt = htpc_ka_dt_py->Integral(htpc_ka_dt_py->FindBin(-2 + 0.001),
						   htpc_ka_dt_py->FindBin(+2 - 0.001));
  
  TH2 *htpc_pr_dt = (TH2 *)ldt->FindObject("cutQuality.TPC_nsigmaPro_VsPtpc_pTPC_p");
  TH1 *htpc_pr_dt_py = htpc_pr_dt->ProjectionY("htpc_pr_dt_py",
					       htpc_pr_dt->GetXaxis()->FindBin(Pt_TPC_p - 0.005 + shift),
					       htpc_pr_dt->GetXaxis()->FindBin(Pt_TPC_p + 0.005 + shift));
  htpc_pr_dt_py->Fit(fgaus, "0q", "", -1., 1.);
  htpc_pr_dt_py->Scale(1. / fgaus->GetParameter(0));
  Double_t n5_tpc_pr_dt = htpc_pr_dt_py->Integral(htpc_pr_dt_py->FindBin(-5 + 0.001),
						   htpc_pr_dt_py->FindBin(+5 - 0.001));
  Double_t n4_tpc_pr_dt = htpc_pr_dt_py->Integral(htpc_pr_dt_py->FindBin(-4 + 0.001),
						   htpc_pr_dt_py->FindBin(+4 - 0.001));
  Double_t n3_tpc_pr_dt = htpc_pr_dt_py->Integral(htpc_pr_dt_py->FindBin(-3 + 0.001),
						   htpc_pr_dt_py->FindBin(+3 - 0.001));
  Double_t n2_tpc_pr_dt = htpc_pr_dt_py->Integral(htpc_pr_dt_py->FindBin(-2 + 0.001),
						   htpc_pr_dt_py->FindBin(+2 - 0.001));
  
  TH2 *htof_ka_dt = (TH2 *)ldt->FindObject("cutQuality.TOF_nsigmaK_vsP_p_K");
  TH1 *htof_ka_dt_py = htof_ka_dt->ProjectionY("htof_ka_dt_py",
					       htof_ka_dt->GetXaxis()->FindBin(Pt_TOF_K - 0.005 + shift),
					       htof_ka_dt->GetXaxis()->FindBin(Pt_TOF_K + 0.005 + shift));
  htof_ka_dt_py->Fit(fgaus, "0q", "", -1., 1.);
  htof_ka_dt_py->Scale(1. / fgaus->GetParameter(0));
  Double_t n5_tof_ka_dt = htof_ka_dt_py->Integral(htof_ka_dt_py->FindBin(-5 + 0.001),
						   htof_ka_dt_py->FindBin(+5 - 0.001));
  Double_t n4_tof_ka_dt = htof_ka_dt_py->Integral(htof_ka_dt_py->FindBin(-4 + 0.001),
						   htof_ka_dt_py->FindBin(+4 - 0.001));
  Double_t n3_tof_ka_dt = htof_ka_dt_py->Integral(htof_ka_dt_py->FindBin(-3 + 0.001),
						   htof_ka_dt_py->FindBin(+3 - 0.001));
  Double_t n2_tof_ka_dt = htof_ka_dt_py->Integral(htof_ka_dt_py->FindBin(-2 + 0.001),
						   htof_ka_dt_py->FindBin(+2 - 0.001));
 
  TH2 *htof_pr_dt = (TH2 *)ldt->FindObject("cutQuality.TOF_nsigmaPro_vsP_p_p");
  TH1 *htof_pr_dt_py = htof_pr_dt->ProjectionY("htof_pr_dt_py",
					       htof_pr_dt->GetXaxis()->FindBin(Pt_TOF_P - 0.005 + shift),
					       htof_pr_dt->GetXaxis()->FindBin(Pt_TOF_P + 0.005 + shift));
  htof_pr_dt_py->Fit(fgaus, "0q", "", -1., 1.);
  htof_pr_dt_py->Scale(1. / fgaus->GetParameter(0));
  Double_t n5_tof_pr_dt = htof_pr_dt_py->Integral(htof_pr_dt_py->FindBin(-5 + 0.001),
						   htof_pr_dt_py->FindBin(+5 - 0.001));
  Double_t n4_tof_pr_dt = htof_pr_dt_py->Integral(htof_pr_dt_py->FindBin(-4 + 0.001),
						  htof_pr_dt_py->FindBin(+4 - 0.001));
  Double_t n3_tof_pr_dt = htof_pr_dt_py->Integral(htof_pr_dt_py->FindBin(-3 + 0.001),
						   htof_pr_dt_py->FindBin(+3 - 0.001));
  Double_t n2_tof_pr_dt = htof_pr_dt_py->Integral(htof_pr_dt_py->FindBin(-2 + 0.001),
						   htof_pr_dt_py->FindBin(+2 - 0.001));


  // open mc data
  filename = mcdirname;
  filename += mctagname;
  filename += ".root";
  TFile *fmc = TFile::Open(filename);
  TList *lmc = (TList *)fmc->Get(Form("RsnOut_f0_MC_2sTPC"));
  cout << " ****** Monte Carlo File to make QA:  " << filename.Data() << ",  trigger = " << mctrigger.Data() << endl;
  
  TH2 *htpc_ka_mc = (TH2 *)lmc->FindObject("cutQuality.TPC_nsigmaK_VsPtpc_pTPC_K");
  TH1 *htpc_ka_mc_py = htpc_ka_mc->ProjectionY("htpc_ka_mc_py",
					       htpc_ka_mc->GetXaxis()->FindBin(0.3 - 0.005),
					       htpc_ka_mc->GetXaxis()->FindBin(0.3 + 0.005));
  htpc_ka_mc_py->Fit(fgaus, "0q", "", -1., 1.);
  htpc_ka_mc_py->Scale(1. / fgaus->GetParameter(0));
  Double_t n5_tpc_ka_mc = htpc_ka_mc_py->Integral(htpc_ka_mc_py->FindBin(-5 + 0.001),
						   htpc_ka_mc_py->FindBin(+5 + 0.001));
  Double_t n4_tpc_ka_mc = htpc_ka_mc_py->Integral(htpc_ka_mc_py->FindBin(-4 + 0.001),
						   htpc_ka_mc_py->FindBin(+4 + 0.001));
  Double_t n3_tpc_ka_mc = htpc_ka_mc_py->Integral(htpc_ka_mc_py->FindBin(-3 + 0.001),
						   htpc_ka_mc_py->FindBin(+3 + 0.001));
  Double_t n2_tpc_ka_mc = htpc_ka_mc_py->Integral(htpc_ka_mc_py->FindBin(-2 + 0.001),
						   htpc_ka_mc_py->FindBin(+2 + 0.001));
   
  TH2 *htpc_pr_mc = (TH2 *)lmc->FindObject("cutQuality.TPC_nsigmaPro_VsPtpc_pTPC_p");
  TH1 *htpc_pr_mc_py = htpc_pr_mc->ProjectionY("htpc_pr_mc_py",
					       htpc_pr_mc->GetXaxis()->FindBin(0.5 - 0.005),
					       htpc_pr_mc->GetXaxis()->FindBin(0.5 + 0.005));
  htpc_pr_mc_py->Fit(fgaus, "0q", "", -1., 1.);
  htpc_pr_mc_py->Scale(1. / fgaus->GetParameter(0));
  Double_t n5_tpc_pr_mc = htpc_pr_mc_py->Integral(htpc_pr_mc_py->FindBin(-5 + 0.001),
						   htpc_pr_mc_py->FindBin(+5 + 0.001));
  Double_t n4_tpc_pr_mc = htpc_pr_mc_py->Integral(htpc_pr_mc_py->FindBin(-4 + 0.001),
						   htpc_pr_mc_py->FindBin(+4 + 0.001));
  Double_t n3_tpc_pr_mc = htpc_pr_mc_py->Integral(htpc_pr_mc_py->FindBin(-3 + 0.001),
						   htpc_pr_mc_py->FindBin(+3 + 0.001));
  Double_t n2_tpc_pr_mc = htpc_pr_mc_py->Integral(htpc_pr_mc_py->FindBin(-2 + 0.001),
						   htpc_pr_mc_py->FindBin(+2 + 0.001));
  //
  TH2 *htof_ka_mc = (TH2 *)lmc->FindObject("cutQuality.TOF_nsigmaK_vsP_p_K");
  TH1 *htof_ka_mc_py = htof_ka_mc->ProjectionY("htof_ka_mc_py",
					       htof_ka_mc->GetXaxis()->FindBin(1.25 - 0.005),
					       htof_ka_mc->GetXaxis()->FindBin(1.25 + 0.005));
  htof_ka_mc_py->Fit(fgaus, "0q", "", -1., 1.);
  htof_ka_mc_py->Scale(1. / fgaus->GetParameter(0));
  Double_t n5_tof_ka_mc = htof_ka_mc_py->Integral(htof_ka_mc_py->FindBin(-5 + 0.001),
						   htof_ka_mc_py->FindBin(+5 + 0.001));
  Double_t n4_tof_ka_mc = htof_ka_mc_py->Integral(htof_ka_mc_py->FindBin(-4 + 0.001),
						  htof_ka_mc_py->FindBin(+4 + 0.001));
  Double_t n3_tof_ka_mc = htof_ka_mc_py->Integral(htof_ka_mc_py->FindBin(-3 + 0.001),
						   htof_ka_mc_py->FindBin(+3 + 0.001));
  Double_t n2_tof_ka_mc = htof_ka_mc_py->Integral(htof_ka_mc_py->FindBin(-2 + 0.001),
						   htof_ka_mc_py->FindBin(+2 + 0.001));
 
  TH2 *htof_pr_mc = (TH2 *)lmc->FindObject("cutQuality.TOF_nsigmaPro_vsP_p_p");
  TH1 *htof_pr_mc_py = htof_pr_mc->ProjectionY("htof_pr_mc_py",
					       htof_pr_mc->GetXaxis()->FindBin(2. - 0.005),
					       htof_pr_mc->GetXaxis()->FindBin(2. + 0.005));
  htof_pr_mc_py->Fit(fgaus, "0q", "", -1., 1.);
  htof_pr_mc_py->Scale(1. / fgaus->GetParameter(0));
  Double_t n5_tof_pr_mc = htof_pr_mc_py->Integral(htof_pr_mc_py->FindBin(-5 + 0.001),
						   htof_pr_mc_py->FindBin(+5 + 0.001));
  Double_t n4_tof_pr_mc = htof_pr_mc_py->Integral(htof_pr_mc_py->FindBin(-4 + 0.001),
						   htof_pr_mc_py->FindBin(+4 + 0.001));
  Double_t n3_tof_pr_mc = htof_pr_mc_py->Integral(htof_pr_mc_py->FindBin(-3 + 0.001),
						   htof_pr_mc_py->FindBin(+3 + 0.001));
  Double_t n2_tof_pr_mc = htof_pr_mc_py->Integral(htof_pr_mc_py->FindBin(-2 + 0.001),
						   htof_pr_mc_py->FindBin(+2 + 0.001));

  TCanvas *ctpc_ka = new TCanvas("ctpc_ka", "ctpc_ka", 800, 800);
  ctpc_ka->DrawFrame(-5., 0., 5., 1.1, ";n#sigma_{K}^{TPC}");
  SetHistoStyle(htpc_ka_dt_py, 20, kRed+1);
  SetHistoStyle(htpc_ka_mc_py, 1, kAzure-1);
  htpc_ka_mc_py->SetLineWidth(3);
  htpc_ka_dt_py->Draw("same");
  htpc_ka_mc_py->Draw("same,histo");
  TLatex *l3tpc_ka_dt = new TLatex(-4.5, 0.95, Form("#frac{N_{3#sigma}}{N_{4#sigma}} = %2.1f%%",
						   100. * n3_tpc_ka_dt / n4_tpc_ka_dt));
  l3tpc_ka_dt->SetTextColor(kRed+1);
  l3tpc_ka_dt->Draw("same");
  TLatex *l2tpc_ka_dt = new TLatex(-4.5, 0.75, Form("#frac{N_{2#sigma}}{N_{4#sigma}} = %2.1f%%",
						   100. * n2_tpc_ka_dt / n4_tpc_ka_dt));
  l2tpc_ka_dt->SetTextColor(kRed+1);
  l2tpc_ka_dt->Draw("same");
  TLatex *l3tpc_ka_mc = new TLatex(4.75, 0.95, Form("#frac{N_{3#sigma}}{N_{4#sigma}} = %2.1f%%",
						  100. * n3_tpc_ka_mc / n4_tpc_ka_mc));
  l3tpc_ka_mc->SetTextColor(kAzure-3);
  l3tpc_ka_mc->SetTextAlign(31);
  l3tpc_ka_mc->Draw("same");
  TLatex *l2tpc_ka_mc = new TLatex(4.75, 0.75, Form("#frac{N_{2#sigma}}{N_{4#sigma}} = %2.1f%%",
						  100. * n2_tpc_ka_mc / n4_tpc_ka_mc));
  l2tpc_ka_mc->SetTextColor(kAzure-3);
  l2tpc_ka_mc->SetTextAlign(31);
  l2tpc_ka_mc->Draw("same");
  // save as .pdf
  gROOT->ProcessLine(Form(".! mkdir -p %s/%s/PIDQA/", figuresdirname.Data(), mctagname.Data()));
  ctpc_ka->SaveAs(Form("%s/%s/PIDQA/cPIDqa_tpc_ka%s.png", figuresdirname.Data(), mctagname.Data(), triggerQA.Data() ));
  
  TCanvas *ctpc_pr = new TCanvas("ctpc_pr", "ctpc_pr", 800, 800);
  ctpc_pr->DrawFrame(-5., 0., 5., 1.1, ";n#sigma_{p}^{TPC}");
  SetHistoStyle(htpc_pr_dt_py, 20, kRed+1);
  SetHistoStyle(htpc_pr_mc_py, 1, kAzure-1);
  htpc_pr_mc_py->SetLineWidth(3);
  htpc_pr_dt_py->Draw("same");
  htpc_pr_mc_py->Draw("same,histo");
  TLatex *l3tpc_pr_dt = new TLatex(-4.5, 0.95, Form("#frac{N_{3#sigma}}{N_{4#sigma}} = %2.1f%%",
						   100. * n3_tpc_pr_dt / n4_tpc_pr_dt));
  l3tpc_pr_dt->SetTextColor(kRed+1);
  l3tpc_pr_dt->Draw("same");
  TLatex *l2tpc_pr_dt = new TLatex(-4.5, 0.75, Form("#frac{N_{2#sigma}}{N_{4#sigma}} = %2.1f%%",
						   100. * n2_tpc_pr_dt / n4_tpc_pr_dt));
  l2tpc_pr_dt->SetTextColor(kRed+1);
  l2tpc_pr_dt->Draw("same");
  TLatex *l3tpc_pr_mc = new TLatex(4.75, 0.95, Form("#frac{N_{3#sigma}}{N_{4#sigma}} = %2.1f%%",
						  100. * n3_tpc_pr_mc / n4_tpc_pr_mc));
  l3tpc_pr_mc->SetTextColor(kAzure-3);
  l3tpc_pr_mc->SetTextAlign(31);
  l3tpc_pr_mc->Draw("same");
  TLatex *l2tpc_pr_mc = new TLatex(4.75, 0.75, Form("#frac{N_{2#sigma}}{N_{4#sigma}} = %2.1f%%",
						  100. * n2_tpc_pr_mc / n4_tpc_pr_mc));
  l2tpc_pr_mc->SetTextColor(kAzure-3);
  l2tpc_pr_mc->SetTextAlign(31);
  l2tpc_pr_mc->Draw("same");
  // save as .pdf
  gROOT->ProcessLine(Form(".! mkdir -p %s/%s/PIDQA/", figuresdirname.Data(), mctagname.Data()));
  ctpc_pr->SaveAs(Form("%s/%s/PIDQA/cPIDqa_tpc_pr%s.png", figuresdirname.Data(), mctagname.Data(), triggerQA.Data() ));

  
  TCanvas *ctof_ka = new TCanvas("ctof_ka", "ctof_ka", 800, 800);
  ctof_ka->DrawFrame(-5., 0., 5., 1.1, ";n#sigma_{K}^{TOF}");
  SetHistoStyle(htof_ka_dt_py, 20, kRed+1);
  SetHistoStyle(htof_ka_mc_py, 1, kAzure-1);
  htof_ka_mc_py->SetLineWidth(3);
  htof_ka_dt_py->Draw("same");
  htof_ka_mc_py->Draw("same,histo");
  TLatex *l3tof_ka_dt = new TLatex(-4.5, 0.95, Form("#frac{N_{3#sigma}}{N_{5#sigma}} = %2.1f%%",
						   100. * n3_tof_ka_dt / n5_tof_ka_dt));
  l3tof_ka_dt->SetTextColor(kRed+1);
  l3tof_ka_dt->Draw("same");
  TLatex *l2tof_ka_dt = new TLatex(-4.5, 0.75, Form("#frac{N_{2#sigma}}{N_{5#sigma}} = %2.1f%%",
						   100. * n2_tof_ka_dt / n5_tof_ka_dt));
  l2tof_ka_dt->SetTextColor(kRed+1);
  //  l2tof_ka_dt->Draw("same");
  TLatex *l3tof_ka_mc = new TLatex(4.75, 0.95, Form("#frac{N_{3#sigma}}{N_{5#sigma}} = %2.1f%%",
						  100. * n3_tof_ka_mc / n5_tof_ka_mc));
  l3tof_ka_mc->SetTextColor(kAzure-3);
  l3tof_ka_mc->SetTextAlign(31);
  l3tof_ka_mc->Draw("same");
  TLatex *l2tof_ka_mc = new TLatex(4.75, 0.75, Form("#frac{N_{2#sigma}}{N_{5#sigma}} = %2.1f%%",
						  100. * n2_tof_ka_mc / n5_tof_ka_mc));
  l2tof_ka_mc->SetTextColor(kAzure-3);
  l2tof_ka_mc->SetTextAlign(31);
  //  l2tof_ka_mc->Draw("same");
  // save as .pdf
  gROOT->ProcessLine(Form(".! mkdir -p %s/%s/PIDQA/", figuresdirname.Data(), mctagname.Data()));
  ctof_ka->SaveAs(Form("%s/%s/PIDQA/cPIDqa_tof_ka%s.png", figuresdirname.Data(), mctagname.Data(),  triggerQA.Data() ));
  
  TCanvas *ctof_pr = new TCanvas("ctof_pr", "ctof_pr", 800, 800);
  ctof_pr->DrawFrame(-5., 0., 5., 1.1, ";n#sigma_{p}^{TOF}");
  SetHistoStyle(htof_pr_dt_py, 20, kRed+1);
  SetHistoStyle(htof_pr_mc_py, 1, kAzure-1);
  htof_pr_mc_py->SetLineWidth(3);
  htof_pr_dt_py->Draw("same");
  htof_pr_mc_py->Draw("same,histo");
  TLatex *l3tof_pr_dt = new TLatex(-4.5, 0.95, Form("#frac{N_{3#sigma}}{N_{5#sigma}} = %2.1f%%",
						   100. * n3_tof_pr_dt / n5_tof_pr_dt));
  l3tof_pr_dt->SetTextColor(kRed+1);
  l3tof_pr_dt->Draw("same");
  TLatex *l2tof_pr_dt = new TLatex(-4.5, 0.75, Form("#frac{N_{2#sigma}}{N_{5#sigma}} = %2.1f%%",
						   100. * n2_tof_pr_dt / n5_tof_pr_dt));
  l2tof_pr_dt->SetTextColor(kRed+1);
  //  l2tof_pr_dt->Draw("same");
  TLatex *l3tof_pr_mc = new TLatex(4.75, 0.95, Form("#frac{N_{3#sigma}}{N_{5#sigma}} = %2.1f%%",
						  100. * n3_tof_pr_mc / n5_tof_pr_mc));
  l3tof_pr_mc->SetTextColor(kAzure-3);
  l3tof_pr_mc->SetTextAlign(31);
  l3tof_pr_mc->Draw("same");
  TLatex *l2tof_pr_mc = new TLatex(4.75, 0.75, Form("#frac{N_{2#sigma}}{N_{5#sigma}} = %2.1f%%",
						  100. * n2_tof_pr_mc / n5_tof_pr_mc));
  l2tof_pr_mc->SetTextColor(kAzure-3);
  l2tof_pr_mc->SetTextAlign(31);
  //  l2tof_pr_mc->Draw("same");
  // save as .pdf
  gROOT->ProcessLine(Form(".! mkdir -p %s/%s/PIDQA/", figuresdirname.Data(), mctagname.Data()));
  ctof_pr->SaveAs(Form("%s/%s/PIDQA/cPIDqa_tof_pr%s.png", figuresdirname.Data(), mctagname.Data(), triggerQA.Data() ));
  
 }
