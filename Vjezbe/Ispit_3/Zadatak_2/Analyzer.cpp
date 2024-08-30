#include "Analyzer.h"

Analyzer::Analyzer() {
    // Otvori ROOT datoteku i učitaj histogram
    inputFile = TFile::Open("/home/public/data/QuadraticHisto.root");
    if (!inputFile || inputFile->IsZombie()) {
        cerr << "Ne mogu otvoriti datoteku!" << endl;
        exit(1);
    }
    
    inputFile->GetObject("histogram", histogram);
    if (!histogram) {
        cerr << "Ne mogu učitati histogram!" << endl;
        exit(1);
    }

    // Definiraj funkciju za fitanje
    fitFunc = new TF1("fitFunc", "[0] * ([1]*x*x + 3)", -0.1, 0.1);
    fitFunc->SetParameters(1, 0); // Početne vrijednosti za N i a
}

Analyzer::~Analyzer() {
    // Zatvori datoteku i oslobodi memoriju
    inputFile->Close();
    delete inputFile;
    delete fitFunc;
}

void Analyzer::FitHistogram() {
    // Fit histogram koristeći Maximum Likelihood metodu
    histogram->Fit("fitFunc", "L");
}

void Analyzer::DrawNegativeLogLikelihood() {
    // Nacrtaj -2lnL funkciju
    TCanvas *c1 = new TCanvas("c1", "Negative Log Likelihood", 800, 600);
    c1->cd();

    // Definiranje -2lnL funkcije
    TF1 *negLogL = new TF1("-2lnL", "[0] + 2*x*x", -0.1, 0.1);
    negLogL->SetParameter(0, fitFunc->GetMinimum());
    negLogL->Draw();
    c1->SaveAs("NegLogL.png");

    delete c1;
}

void Analyzer::DrawFitAndHistogram() {
    // Nacrtaj histogram i fitanu funkciju
    TCanvas *c2 = new TCanvas("c2", "Fit Histogram", 800, 600);
    c2->cd();
    histogram->Draw();
    fitFunc->Draw("SAME");
    c2->SaveAs("FitHistogram.png");

    delete c2;
}

