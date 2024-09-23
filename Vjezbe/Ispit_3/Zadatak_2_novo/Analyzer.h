#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TLegend.h>
#include <TF1.h>
#include <TGraph.h>
#include <iostream>

using namespace std;

class Analyzer {
public:
    Analyzer();  // Konstruktor
    virtual ~Analyzer();  // Destruktor

    void FitHistogram();  // Metoda za fitanje histograma
    double NegativeLogLikelihood(double *x, double *par);  // Funkcija za izračunavanje -2lnL
    void PlotNegativeLogLikelihood();  // Metoda za crtanje -2lnL u ovisnosti o parametru a
    void DrawFitAndHistogram();  // Metoda za crtanje histograma i fit funkcije

private:
    TFile* inputFile;  // Ulazni ROOT file
    TH1F* histogram;  // Histogram iz ROOT file-a
    TF1* fitFunction;  // Fit funkcija za histogram
};

#endif
