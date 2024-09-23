#include "Analyzer.h"

Analyzer::Analyzer()
{
  r3 = new TRandom3();
}

Analyzer::~Analyzer()
{
  delete r3;
}

void Analyzer::GenerateTestStatisticPDF(int nsteps)
{
  c= new TCanvas("c","c",700,700);

  TestStatistic_PDF = new TH1F("TestStatistic_PDF","TestStatistic_PDF",400,0,40);


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

  delete c;
}

void Analyzer::ExpectedPValueScan()
{
  c= new TCanvas("c","c",700,700);

  expected_scan = new TGraph();

  // Theoretical parameters
  float a_SM=-1.;
  float b_SM=-190.;
  float c_SM=0.5;
  float sigma_SM=0.0236;

  float m_H = 0.;

  float chi2;

  for(int i = 10; i < 690; i+=5)
  {
    TString name = "toy_histo2_" + std::to_string(i);
    toy_histo = new TH1F(name,"toy_histo",200,0.,700.);

    theoreticalPDF = new TF1("theoreticalPDF","[0]/TMath::Exp(x/[1])",0,700);
    theoreticalPDF->SetParameter(0,1000.);
    theoreticalPDF->SetParameter(1,100.);

    m_H = i/1.0;

    for(int j = 0; j < 10000; j++)
    {
      if(r3->Rndm() > a_SM*TMath::Power((m_H + b_SM),2) + c_SM ) toy_histo->Fill(r3->Exp(100)); // Generate SM process for probability given by theory
      else toy_histo->Fill(r3->Gaus(m_H,sigma_SM*m_H)); // otherwise generate Higgs boson according to theoretical PDF
    }

    theoreticalPDF->FixParameter(1,100.);
    toy_histo->Fit(theoreticalPDF,"Q","",m_H-10.,m_H+10.);
    chi2 = theoreticalPDF->GetChisquare();

    expected_p_value = TestStatistic_PDF->Integral(TestStatistic_PDF->FindBin(chi2),TestStatistic_PDF->GetNbinsX())/TestStatistic_PDF->Integral();

    expected_scan->SetPoint(i/5-2,m_H,expected_p_value);

    // cout << i/5-2 << " : " << m_H << " : " << expected_p_value << endl;
    //
    // toy_histo->Draw();
    // c->SaveAs("test.pdf");
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

  expected_scan->SetTitle("Expected p-value scan");

  expected_scan->GetXaxis()->SetRangeUser(0,700);
  expected_scan->SetMinimum(0.00001);
  expected_scan->GetXaxis()->SetTitle("m_{H}");
  expected_scan->GetYaxis()->SetTitle("p-value");
  expected_scan->GetYaxis()->SetTitleOffset(0.7);

  expected_scan->Draw();

  c->SaveAs("ExpectedPValueScan.pdf");

  delete c;
}