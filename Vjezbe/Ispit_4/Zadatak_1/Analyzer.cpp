#include "Analyzer.h"
#include <iostream>
#include <TLine.h> // Dodavanje potrebne biblioteke za TLine

Analyzer::Analyzer() {
    // Inicijalizacija histograma i generatora slučajnih brojeva
    chi2_min_hist = new TH1F("chi2_min_hist", "Chi^2 Minimum Distribution", 100, 0, 70); // Proširivanje raspona osi X do 70
    rand = new TRandom();
    
    // Učitavanje histograma iz datoteke
    TFile* inputFile = new TFile("/home/public/data/GoodnessOfFit.root", "READ");
    inputFile->GetObject("histogram", data_histogram);
    inputFile->Close();
}

Analyzer::~Analyzer() {
    delete chi2_min_hist;
    delete rand;
}

void Analyzer::GeneratePseudoExperiments() {
    // Generiranje 1000 pseudoeksperimenata za hipotezu H0
    for (int i = 0; i < 1000; ++i) {
        TH1F* pseudo_hist = new TH1F("pseudo_hist", "Pseudo Experiment", 100, 0, 12.5);
        for (int j = 0; j < 10000; ++j) {  // 10^4 mjerenja
            double x = rand->Exp(1.25); // Generiranje podataka prema H0 (1/12.5)*exp(-0.8x)
            pseudo_hist->Fill(x);
        }
        pseudo_hist->Scale(1.0 / pseudo_hist->Integral()); // Normalizacija histograma

        // Fit funkcija na pseudo-histogram
        TF1* fit_function = new TF1("fit_function", "[0]*exp(-0.8*x)", 0, 12.5);
        fit_function->SetParameter(0, 1.0 / 12.5);
        pseudo_hist->Fit(fit_function, "Q"); // Fitiranje i uzimanje Chi-square vrijednosti

        chi2_min_hist->Fill(fit_function->GetChisquare());
        delete pseudo_hist;
    }
}

void Analyzer::ChiSquareDistribution() {
    // Ova funkcija crta distribuciju pseudoeksperimenata i dodaje liniju za promatranu vrijednost
    TCanvas* canvas = new TCanvas("canvas", "Chi^2 Minimum Distribution", 800, 600);
    chi2_min_hist->GetXaxis()->SetRangeUser(0, 70);  // Prilagodba raspona osi X od 0 do 70
    chi2_min_hist->GetYaxis()->SetRangeUser(0, 40);   // Prilagodba raspona osi Y od 0 do 25
    chi2_min_hist->GetXaxis()->SetTitle("#chi^{2}_{min} vrijednost"); // Postavljanje naziva x-osi
    chi2_min_hist->GetYaxis()->SetTitle("Broj pseudo-eksperimenata"); // Postavljanje naziva y-osi
    chi2_min_hist->Draw();
    
    // Dodavanje linije za promatranu vrijednost na histogram distribucije
    TLine* line = new TLine(chi2_min_obs, 0, chi2_min_obs, 40); // Linija od 0 do 25
    line->SetLineColor(kRed);
    line->SetLineWidth(2); // Postavi debljinu linije za bolju vidljivost
    line->Draw("same");

    canvas->SaveAs("ChiSquareWithObserved.pdf"); // Spremanje grafike sa svim podacima
}

void Analyzer::CalculateChiSquare() {
    // Učitavanje histograma iz datoteke
    TFile* inputFile = new TFile("/home/public/data/GoodnessOfFit.root", "READ");
    inputFile->GetObject("histogram", data_histogram);
    
    // Fit funkcija na stvarni histogram
    TF1* fit_function = new TF1("fit_function", "[0]*exp(-0.8*x)", 0, 12.5);
    fit_function->SetParameter(0, 1.0 / 12.5);
    data_histogram->Fit(fit_function, "Q"); 

    chi2_min_obs = fit_function->GetChisquare(); // Pohrana promatrane vrijednosti u privatni član
    std::cout << "Chi-Square min za stvarni histogram: " << chi2_min_obs << std::endl;

    // Dodavanje linije na histogram
    ChiSquareDistribution(); // Poziv funkcije za crtanje distribucije i dodavanje linije
    inputFile->Close();
}
