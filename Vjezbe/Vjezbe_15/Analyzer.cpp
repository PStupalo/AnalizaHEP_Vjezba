#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::ReconstructHiggs()
{
   c= new TCanvas("c","c",700,700);

   RecoMass = new TH1F("RecoMass","RecoMass",200,0.,700.);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      p1.SetXYZM(particle1_px,particle1_py,particle1_pz,0);
      p2.SetXYZM(particle2_px,particle2_py,particle2_pz,0);

      RecoMass->Fill((p1+p2).M());
   }

   RecoMass->SetTitle("Reconstructed invariant mass");
   RecoMass->SetStats(0);
   RecoMass->GetXaxis()->SetTitle("m_{#gamma#gamma}");
   RecoMass->GetYaxis()->SetTitle("Events / 3.5 GeV");
   RecoMass->SetMarkerStyle(20);
   RecoMass->SetMarkerColor(kBlack);
   RecoMass->SetMarkerSize(0.6);
   RecoMass->Draw("EP");

   theoreticalPDF->FixParameter(1,100.);
   RecoMass->Fit(theoreticalPDF);

   leg = new TLegend(0.5,0.7,0.9,0.9);

   leg->AddEntry(RecoMass, "Data", "EP");
   leg->AddEntry(theoreticalPDF, "SM prediction", "l");

   leg->SetTextSize(0.03);
   leg->Draw();

   c->SaveAs("ReconstructedMass.pdf");
}

void Analyzer::GenerateTestStatisticPDF(int nsteps)
{
  c= new TCanvas("c","c",700,700);

  TestStatistic_PDF = new TH1F("TestStatistic_PDF","TestStatistic_PDF",300,0,30);

  theoreticalPDF = new TF1("theoreticalPDF","[0]/TMath::Exp(x/[1])",0,700);
  theoreticalPDF->SetParameter(0,1000.);
  theoreticalPDF->SetParameter(1,100.);

  float chi2;
  float m_H = 0.;

  for(int i = 0; i < nsteps; i++)
  {
    TString name = "toy_histo_" + std::to_string(i);
    toy_histo = new TH1F(name,"toy_histo",200,0.,700.);

    for(int j = 0; j < 100000; j++) toy_histo->Fill(r3->Exp(100));

    theoreticalPDF->FixParameter(1,100.); //fix the parameter to theoretical value

    for(int i = 10; i < 690; i+=5) // do the fit doing 5 GeV steps in 10-690 GeV region
    {
      m_H = i/1.0;

      toy_histo->Fit(theoreticalPDF,"Q","",m_H-10,m_H+10); // perform the fit in the 20 GeV window
      chi2 = theoreticalPDF->GetChisquare();
      TestStatistic_PDF->Fill(chi2);
    }
  }

  TestStatistic_PDF->SetStats(0);
  gPad->SetBottomMargin(0.2);
  TestStatistic_PDF->SetTitle("Test statistic PDF");
  TestStatistic_PDF->GetXaxis()->SetTitle("#chi^{2}(N,#zeta_{SM})");
  TestStatistic_PDF->GetXaxis()->SetTitleOffset(1.5);
  TestStatistic_PDF->Scale(1./TestStatistic_PDF->Integral());
  TestStatistic_PDF->Draw("HIST");

  c->SaveAs("TestStatisticPDF.pdf");

  delete c, toy_histo;
  delete gROOT->FindObject("toy_histo");
}

void Analyzer::ObservedPValueScan()
{
  c= new TCanvas("c","c",700,700);

  expected_scan = new TGraph();
  observed_scan = new TGraph();

  // Theoretical parameters
  float a_SM=-1.;
  float b_SM=-190.;
  float c_SM=0.02;
  float sigma_SM=0.0236;

  float m_H = 0.;
  float t_exp_obs = 0.;

  float chi2_o;
  float chi2;

  theoreticalPDF = new TF1("theoreticalPDF","[0]/TMath::Exp(x/[1])",0,700);
  theoreticalPDF->SetParameter(0,1000.);
  theoreticalPDF->SetParameter(1,100.);

  for(int i = 10; i < 690; i+=5)
  {
    m_H = i/1.0;

    TString name = "toy_histo2_" + std::to_string(i);
    toy_histo = new TH1F(name,"toy_histo2",200,0.,700.);

    for(int j = 0; j < 100000; j++)
    {
      if(r3->Rndm() > a_SM*TMath::Power((m_H + b_SM),2) + c_SM ) toy_histo->Fill(r3->Exp(100)); // Generate SM process for probability given by theory
      else toy_histo->Fill(r3->Gaus(m_H,sigma_SM*m_H)); // otherwise generate Higgs boson according to theoretical PDF
    }

    theoreticalPDF->FixParameter(1,100.);
    toy_histo->Fit(theoreticalPDF,"Q","",m_H-10.,m_H+10.);
    chi2 = theoreticalPDF->GetChisquare();

    expected_p_value = TestStatistic_PDF->Integral(TestStatistic_PDF->FindBin(chi2),TestStatistic_PDF->GetNbinsX())/TestStatistic_PDF->Integral();

    expected_scan->SetPoint(i/5-2,m_H,expected_p_value);

    theoreticalPDF->FixParameter(1,100.);
    RecoMass->Fit(theoreticalPDF,"Q","",m_H-10.,m_H+10.);
    chi2_o = theoreticalPDF->GetChisquare();

    observed_p_value = TestStatistic_PDF->Integral(TestStatistic_PDF->FindBin(chi2_o),TestStatistic_PDF->GetNbinsX())/TestStatistic_PDF->Integral();

    observed_scan->SetPoint(i/5-2,m_H,observed_p_value);

  }

  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLeftMargin(0.1);

  expected_scan->SetLineColor(kBlack);
  expected_scan->SetLineStyle(kDashed);
  expected_scan->SetLineWidth(2);
  expected_scan->SetMarkerColor(kBlack);
  expected_scan->SetMarkerStyle(20);
  expected_scan->SetMarkerSize(0.6);

  observed_scan->SetLineColor(kRed);
  observed_scan->SetLineWidth(2);
  observed_scan->SetMarkerColor(kRed);
  observed_scan->SetMarkerStyle(20);
  observed_scan->SetMarkerSize(0.6);

  mg = new TMultiGraph();
  mg->Add(expected_scan);
  mg->Add(observed_scan);
  mg->SetTitle("Observed p-value scan");
  mg->SetMinimum(0.00001);
  mg->Draw("ALP");
  mg->GetXaxis()->SetRangeUser(0,700);
  mg->GetXaxis()->SetTitle("m_{H}");
  mg->GetYaxis()->SetTitle("p-value");
  mg->GetYaxis()->SetTitleOffset(0.7);


  c->SaveAs("ObservedPValueScan.pdf");

  delete c, toy_histo, mg;
  delete gROOT->FindObject("toy_histo");
}