#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TStyle.h>
#include <iostream>

using namespace std;

class Analyzer {
public:
    Analyzer();
    virtual ~Analyzer();
    void BinnedFit();
private:
    TFile *file;
    TCanvas *c;
    TH1F *histogram;
};

#endif
