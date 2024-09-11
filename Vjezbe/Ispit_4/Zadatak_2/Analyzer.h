
#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <TH1F.h>
#include <TRandom.h>
#include <TFile.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

using namespace std;

class Analyzer {
public:
    Analyzer(const char* filename); // Konstruktor koji učitava datoteku
    ~Analyzer(); // Destruktor za oslobađanje memorije

    void LoadHistogram(); // Učitavanje histograma iz datoteke
    void SimulateExperiments(); // Generiranje pseudoeksperimenata za hipoteze
    void DrawCombinedResults(); // Crtanje rezultata i usporedba hipoteza
    double CalculateObservedSuccess(); // Izračunavanje uočene vjerojatnosti uspjeha

private:
    TFile* inputFile; // Ulazna datoteka
    TH1F* histObserved; // Histogram uočenih podataka
    TH1F* hist_H0; // Histogram za hipotezu H0
    TH1F* hist_H1; // Histogram za hipotezu H1
    TRandom randGen; // Generator slučajnih brojeva
    int N; // Broj pokušaja (N=20)
    double prob_H0; // Vjerojatnost uspjeha za H0
    double prob_H1; // Vjerojatnost uspjeha za H1
    int totalExperiments; // Broj pseudoeksperimenata
    int totalMeasurements; // Broj mjerenja po eksperimentu
};

#endif
