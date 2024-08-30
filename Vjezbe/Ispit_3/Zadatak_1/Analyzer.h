#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <iostream>
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <THStack.h>
#include <TGraph.h>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <TApplication.h>
#include <string>
#include <TF1.h>
#include <TLine.h>
#include <TGraphErrors.h>
#include <TRandom3.h>

using namespace std;

class Analyzer {
public:
    TTree *fChain;     //! Pointer na analizirano stablo
    Int_t fCurrent;    //! Broj trenutnog stabla u lancu

    // Deklaracija varijabli za pohranu podataka
    Double_t x;

    // Popis grana
    TBranch *b_x; //!

    Analyzer(TTree *tree = 0);
    virtual ~Analyzer();
    virtual void RunAnalysis();
    virtual void TestHypotheses();
    virtual void Init(TTree *tree);
    virtual Bool_t Notify();
    virtual void Show(Long64_t entry = -1);
    virtual Int_t Cut(Long64_t entry);
    virtual Int_t GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);

private:
    double GenerateValue(double parameter);
    double CalculateMedian(vector<double>& data);
    
    TRandom3* randomGenerator;
};

#endif

