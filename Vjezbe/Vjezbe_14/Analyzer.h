
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TGraph.h>
#include <TRandom3.h>
#include <TLegend.h>

#include <iostream>
#include <cmath>

using namespace std;

class Analyzer {
public :
   Analyzer();
   ~Analyzer();
   void GenerateTestStatisticPDF(int);
   void ExpectedPValueScan();

   TCanvas *c;
   TH1F *TestStatistic_PDF, *toy_histo;
   TF1 *theoreticalPDF;

   TRandom3 *r3;

   float expected_p_value;

   TGraph *expected_scan;

};