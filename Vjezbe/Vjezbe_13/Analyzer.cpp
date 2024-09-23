#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void Analyzer::CompareHypothesis(TString country, double mu, double sigma)
{
   TCanvas *c3 = new TCanvas(country,country,700,700);

   testStatistic_H0 = new TH1F("testStatistic_H0"+country,"H_0 Test Statistic PDF",150,160.,175.);
   testStatistic_H1 = new TH1F("testStatistic_H1"+country,"H_1 Test Statistic PDF",150,160.,175.);

   double sum_height_H0;
   double sum_height_H1;

   for (int i=0; i < 1000000 ; i++)
   {
     sum_height_H0 = 0.;
     sum_height_H1 = 0.;

     for (int j=0; j < 100; j++)
     {
         sum_height_H0 += r3->Gaus(168.0,7.0);
         sum_height_H1 += r3->Gaus(mu,sigma);
     }

     testStatistic_H0->Fill(sum_height_H0/100.);
     testStatistic_H1->Fill(sum_height_H1/100.);

   }

   testStatistic_H0->SetFillColor(kRed-2);
   testStatistic_H0->SetLineColor(kRed-2);

   testStatistic_H0->SetTitle("Hypoyhesis testing");
   testStatistic_H0->GetXaxis()->SetTitle("#bar{h} [cm]");

   testStatistic_H0->Scale(1./testStatistic_H0->Integral());
   testStatistic_H0->Draw("HIST");

   testStatistic_H1->SetFillColor(kBlue-4);
   testStatistic_H1->SetLineColor(kBlue-4);

   testStatistic_H1->SetTitle("Hypoyhesis testing");
   testStatistic_H1->GetXaxis()->SetTitle("#bar{h} [cm]");

   testStatistic_H1->Scale(1./testStatistic_H1->Integral());
   testStatistic_H1->Draw("HIST SAME");

   TLine *line = new TLine(t_obs, 0. , t_obs, 0.04);
   line->SetLineWidth(3);
   line->Draw();

   TLegend *leg = new TLegend(0.7,0.6,0.9,0.9);
   leg->AddEntry(testStatistic_H0, "Spain", "f");
   leg->AddEntry(testStatistic_H1, country, "f");
   leg->Draw();

   c3->SaveAs("TestStatistic_SpainVs"+ country + ".pdf");

   double p_H0 = 0.;
   double p_H1 = 0.;

   if( mu < 168.0)
   {
     p_H0 = testStatistic_H0->Integral(0, testStatistic_H0->FindBin(t_obs));
     p_H1 = testStatistic_H1->Integral(testStatistic_H1->FindBin(t_obs), 150);
   }

   else
   {
     p_H0 = testStatistic_H0->Integral(testStatistic_H0->FindBin(t_obs), 150);
     p_H1 = testStatistic_H1->Integral(0, testStatistic_H1->FindBin(t_obs));
   }

   cout << "We can exclude alternative hypothesis of " << country << " at " << (1-p_H1/p_H0)*100 << "\% CL." << endl;

}



void Analyzer::PValueCalculation()
{
   TCanvas *c2 = new TCanvas("c2","c2",700,700);

   t_obs = 0.;
   double p_value = 0.;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      t_obs+=height;
   }

   t_obs = t_obs/100.;

   testStatistic_PDF->SetFillColor(kRed-2);
   testStatistic_PDF->SetLineColor(kRed-2);

   testStatistic_PDF->SetTitle("Test Statistic PDF distribution");
   testStatistic_PDF->GetXaxis()->SetTitle("#bar{h} [cm]");

   testStatistic_PDF->Scale(1./testStatistic_PDF->Integral());
   testStatistic_PDF->Draw("HIST");

   TLine *line = new TLine(t_obs, 0. , t_obs, 0.04);
   line->SetLineWidth(3);
   line->Draw();

   c2->SaveAs("TestStatistic_PDF.pdf");

   p_value = testStatistic_PDF->Integral(testStatistic_PDF->FindBin(t_obs),100);
   cout << "p-value for the null hypothesis is: " << p_value << endl;
   cout << "Significance for the null hypothesis is " << Analyzer::Significance(p_value) << endl;

}

void Analyzer::Generate_TestStatistic_H0()
{
  TCanvas *c = new TCanvas("c","c",700,700);

  gStyle->SetOptStat(0);

  testStatistic_PDF = new TH1F("testStatistic_PDF","Test Statistic PDF",100,160.,170.);

  double sum_height;

  for (int i=0; i < 1000000 ; i++)
  {
    sum_height = 0.;

    for (int j=0; j < 100; j++)
    {
        sum_height += r3->Gaus(164.7,7.1);
    }

    testStatistic_PDF->Fill(sum_height/100.);

  }

  c->cd();
  testStatistic_PDF->SetFillColor(kRed-2);
  testStatistic_PDF->SetLineColor(kRed-2);

  testStatistic_PDF->SetTitle("Test Statistic PDF distribution");
  testStatistic_PDF->GetXaxis()->SetTitle("#bar{h} [cm]");

  testStatistic_PDF->Scale(1./testStatistic_PDF->Integral());
  // testStatistic_PDF->Draw("HIST");
  // c->SaveAs("TestStatistic_PDF.pdf");
}

double Analyzer::Significance( double p_value )
{
  return TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value);
}