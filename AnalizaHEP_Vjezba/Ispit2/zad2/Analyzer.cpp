#include "Analyzer.h"
#include <TH1F.h>
#include <TCanvas.h>
#include <TF1.h>

Analyzer::Analyzer() {}

Analyzer::~Analyzer() {
    delete c;
}

void Analyzer::BinnedFit() {

    file = new TFile("/home/public/data/LinearHisto.root");
    TH1F *histogram= static_cast<TH1F*> (file->Get("histogram"));

    // Definiramo funkciju za binned fit
    TF1 *fitFunction = new TF1("fitFunction", "[0]*([1]*x + 5.0)", 0., 10.); //N(ax+5)

    histogram->Fit(fitFunction, "Q");// binned fit

    // Chi-Square
    c = new TCanvas("c", "c", 800, 600);
    TF1 *chiSquareFunction = new TF1("chiSquareFunction", "[0]*([1]*x + 5.0)",0., 10.);
    chiSquareFunction->SetParameter(0, fitFunction->GetChisquare()); //N
    chiSquareFunction->SetParameter(1, 0);//a

    chiSquareFunction->Draw();

    double parameterA = fitFunction->GetParameter(0);
    std::cout << "Vrijednost parametra a: " << parameterA << std::endl;

    double errorA = fitFunction->GetParError(0); // Greška parametra a
    // granice = parametar +/- N*devijacija ako imamo N devijacija 
    //(ovdje interval pokriva 2 std.dev.)
    double aMinus = parameterA - 2 * errorA; // Donja granica intervala
    double aPlus = parameterA + 2 * errorA; // Gornja granica intervala
    

    std::cout << "Centralni interval pouzdanosti [a-, a+]: [" << aMinus << ", " << aPlus << "]" << std::endl;

    c->cd();
    histogram->Draw();
    fitFunction->Draw("same");
    c->SaveAs("BinnedFit.png");

    delete fitFunction;
    delete chiSquareFunction;
    delete file;
}
