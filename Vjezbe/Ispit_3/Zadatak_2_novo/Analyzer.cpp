#include "Analyzer.h"

Analyzer::Analyzer() {
    // Otvorite ulazni ROOT file
    inputFile = new TFile("/home/public/data/QuadraticHisto.root", "READ");
    
    // Dohvaćanje histograma iz ROOT file-a
    if (inputFile && inputFile->IsOpen()) {
        inputFile->GetObject("histogram", histogram);
        if (!histogram) {
            cerr << "Error: Histogram not found in the file!" << endl;
            histogram = nullptr;
        }
    } else {
        cerr << "Error: Cannot open file!" << endl;
        inputFile = nullptr;
        histogram = nullptr;
    }

    // Definiranje fit funkcije
    fitFunction = new TF1("fitFunction", "[0] * (x * x + 3)", 0, 5); // Prilagodba raspona funkcije
    fitFunction->SetParameters(1, 1); // Početni parametri za a i N
}

Analyzer::~Analyzer() {
    // Provjera prije brisanja objekata
    if (inputFile) {
        inputFile->Close();
        delete inputFile;
        inputFile = nullptr;
    }
    if (histogram) {
        delete histogram;
        histogram = nullptr;
    }
    if (fitFunction) {
        delete fitFunction;
        fitFunction = nullptr;
    }
}

void Analyzer::FitHistogram() {
    if (!histogram) {
        cerr << "Error: Histogram is not loaded properly." << endl;
        return;
    }

    // Fit histograma pomoću grafičke Maximum Likelihood metode
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

    if (!histogram) return L;

    // Izračunavanje očekivanog broja događaja u svakom binu
    for (int i = 1; i <= histogram->GetNbinsX(); i++) {
        double x_i = histogram->GetBinLowEdge(i);
        double x_ip1 = histogram->GetBinLowEdge(i + 1);
        double ni = histogram->GetBinContent(i);

        // Integracija funkcije unutar granica bina
        double expected = N * (a * (x_ip1 * x_ip1 * x_ip1 - x_i * x_i * x_i) / 3 + 3 * (x_ip1 - x_i));

        if (expected > 0) {
            L += -2 * (ni * TMath::Log(expected) - expected);
        }
    }

    return L;
}

void Analyzer::PlotNegativeLogLikelihood() {
    if (!histogram) {
        cerr << "Error: Histogram is not loaded properly." << endl;
        return;
    }

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

void Analyzer::DrawFitAndHistogram() {
    if (!histogram) {
        cerr << "Error: Histogram is not loaded properly." << endl;
        return;
    }

    TCanvas *c3 = new TCanvas("c3", "Histogram and Fit", 800, 600);
    histogram->Draw("E");
    fitFunction->Draw("SAME");
    c3->SaveAs("HistogramAndFit.png");
    delete c3;
}
