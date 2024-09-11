// Analyzer.cpp
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

Analyzer::Analyzer(const char* filename) : N(20), prob_H0(0.62), prob_H1(0.66), totalExperiments(1000), totalMeasurements(100) {
    inputFile = new TFile(filename, "READ");
    if (!inputFile || inputFile->IsZombie()) {
        cout << "Greška pri otvaranju datoteke!" << endl;
        return;
    }
    LoadHistogram();
}

Analyzer::~Analyzer() {
    delete histObserved;
    delete hist_H0;
    delete hist_H1;
    inputFile->Close();
    delete inputFile;
}

void Analyzer::LoadHistogram() {
    
    inputFile->GetObject("histogram", histObserved);
    if (!histObserved) {
        cout << "Histogram nije pronađen!" << endl;
        return;
    }

    // Norm histo
    histObserved->Scale(1.0 / histObserved->Integral());

    // Inicijalizacija histograma za H0 i H1
    hist_H0 = new TH1F("hist_H0", "Distribucija vjerojatnosti za H0", 100, 0, 1);
    hist_H1 = new TH1F("hist_H1", "Distribucija vjerojatnosti za H1", 100, 0, 1);

    SimulateExperiments();
}

void Analyzer::SimulateExperiments() {
    // petlja po pseudoeksperimentma
    for (int i = 0; i < totalExperiments; ++i) {
        double probability_H0 = 0;
        double probability_H1 = 0;

        // petlja po mjerenjima
        for (int j = 0; j < totalMeasurements; ++j) {
            int numSuccess_H0 = randGen.Binomial(N, prob_H0); //  broj uspjeha za H0
            int numSuccess_H1 = randGen.Binomial(N, prob_H1); //  broj uspjeha za H1

            probability_H0 += static_cast<double>(numSuccess_H0) / N;
            probability_H1 += static_cast<double>(numSuccess_H1) / N;
        }

        // Izračun prosječne vjerojatnosti uspjeha
        probability_H0 /= totalMeasurements;
        probability_H1 /= totalMeasurements;

        // Popuni histograme
        hist_H0->Fill(probability_H0);
        hist_H1->Fill(probability_H1);
    }

    // Normaliziraj histograme
    hist_H0->Scale(1.0 / hist_H0->Integral());
    hist_H1->Scale(1.0 / hist_H1->Integral());

    DrawCombinedResults();
}

void Analyzer::DrawCombinedResults() {
    // Crtanje kombiniranih rezultata za H0 i H1
    TCanvas* canvas = new TCanvas("canvas", "Usporedba Hipoteza", 800, 600);

    gStyle->SetOptStat(0);

    hist_H0->SetLineColor(kGreen + 2);
    hist_H1->SetLineColor(kRed);

    // Postavi raspon x-osi od 0.5 do 0.8
    //da se "lijepse vidi"
    //hist_H0->GetXaxis()->SetRangeUser(0.5, 0.8);
    //hist_H1->GetXaxis()->SetRangeUser(0.5, 0.8);

    hist_H0->Draw("HIST");
    hist_H1->Draw("HIST SAME");

    // Dodavanje legende na platno
    TLegend* legend = new TLegend(0.7, 0.8, 0.9, 0.9);
    legend->AddEntry(hist_H0, "Hipoteza H0 (p = 0.62)", "l");
    legend->AddEntry(hist_H1, "Hipoteza H1 (p = 0.66)", "l");
    legend->Draw();

    // Dodavanje vertikalne linije za promatranu vrijednost
    double observedSuccess = CalculateObservedSuccess();
    TLine* line = new TLine(observedSuccess, 0, observedSuccess, hist_H1->GetMaximum());
    line->SetLineColor(kBlue);
    line->SetLineWidth(2);
    line->Draw("same");

    TString observedText;
    observedText.Form("Promatrana uspjesnost = %.3f", observedSuccess);
    legend->AddEntry(line, observedText, "l"); // Dodaj opis s vrijednošću za liniju

    canvas->SaveAs("HypothesisComparison.png");
    //canvas->SaveAs("HypothesisComparison_drugi_xrange.png");
    delete canvas;
}

double Analyzer::CalculateObservedSuccess() {
    // Izračunaj vjerojatnost uspjeha iz uočenih podataka
    double p = 0;
    for (int i = 1; i <= N; ++i) {
        p += histObserved->GetBinContent(i) * static_cast<double>(i - 1) / N;
    }
    cout << "Uočena vjerojatnost uspjeha p: " << p << endl;
    return p;
}
