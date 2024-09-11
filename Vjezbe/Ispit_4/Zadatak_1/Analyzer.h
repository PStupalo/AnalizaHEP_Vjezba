#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include <TH1F.h>
#include <TRandom.h>
#include <TFile.h>
#include <TF1.h>
#include <TCanvas.h>

class Analyzer {
public:
    Analyzer();
    ~Analyzer();

    void GeneratePseudoExperiments();
    void ChiSquareDistribution();
    void CalculateChiSquare();
    
private:
    TH1F* chi2_min_hist;
    TRandom* rand;
    TH1F* data_histogram;
    double chi2_min_obs;  // Dodano: čuva promatranu vrijednost chi-square minima
};

#endif
