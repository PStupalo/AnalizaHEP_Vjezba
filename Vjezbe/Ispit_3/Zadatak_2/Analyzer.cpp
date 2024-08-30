#include "Analyzer.h"

Analyzer::Analyzer() {
    // Otvorite ulazni ROOT file
    inputFile = new TFile("/home/public/data/QuadraticHisto.root", "READ");
    
    inputFile->GetObject("histogram", histogram);

    // Definiranje fit funkcije
    fitFunction = new TF1("fitFunction", "[0] * (x * x + 3)", -0.1, 0.1); // zadana funkcija f(x)=N(ax^2+3) u odredenom intervalu
    fitFunction->SetParameters(1, 1); // Početni parametri za a i N
}

Analyzer::~Analyzer() {
    delete inputFile;
    delete histogram;
    delete fitFunction;
}

void Analyzer::FitHistogram() {
    // Grafički prikaz histograma i fit funkcije
    TCanvas *c1 = new TCanvas("c1", "Histogram Fit", 800, 600);
    histogram->Draw("E");
    histogram->Fit(fitFunction, "L");
    fitFunction->Draw("SAME");

    // Spremanje slike
    c1->SaveAs("fitResult.png");
    delete c1;
}

double Analyzer::NegativeLogLikelihood(double *x, double *par) {
    // Implementacija negativnog logaritma Likelihood funkcije
    double a = par[0];
    double N = par[1];
    double L = 0;

    for (int i = 1; i <= histogram->GetNbinsX(); i++) {
        double ni = histogram->GetBinContent(i);
        double xi = histogram->GetBinCenter(i);
        double expected = N * (a * xi * xi + 3);
        L += -2 * (ni * TMath::Log(expected) - expected);
    }
    
    return L;
}

void Analyzer::PlotNegativeLogLikelihood() {
    // Definiranje raspona za parametar a
    const int nPoints = 100;
    double aMin = -0.1;
    double aMax = 0.1;
    double step = (aMax - aMin) / nPoints;
    
    // Definiranje grafika za -2lnL u ovisnosti o a
    TGraph* graph = new TGraph(nPoints);
    
    for (int i = 0; i < nPoints; ++i) {
        double a = aMin + i * step;
        double params[2] = {a, 1}; // Koristi normalizaciju N = 1 kao primjer
        double negLogL = NegativeLogLikelihood(nullptr, params);
        graph->SetPoint(i, a, negLogL);
    }
    
    // Crtanje grafa
    TCanvas* c2 = new TCanvas("c2", "-2 ln L vs a", 800, 600);
    graph->SetTitle("-2 ln L vs a; a; -2 ln L");
    graph->Draw("AL");
    
    // Spremanje slike
    c2->SaveAs("NegativeLogLikelihood.png");
    
    delete c2;
    delete graph;
}

