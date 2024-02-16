#include "Analyzer.h"

#include <TH1F.h>
#include <TRandom3.h>
#include <TCanvas.h>


Analyzer::Analyzer() {}

void Analyzer :: CentralLimitTheorem()
{
    const int N = 50;
    const int numEvents = 1000000;
    rand= new TRandom3();

    TCanvas *c1 = new TCanvas("histo","histo",1000,1000);

    TH1F *histogram = new TH1F("histogram", "Distribucija sume S", 500, 500, 2000);
    histogram->SetStats(0);

    double x;
    for (int i = 0; i < numEvents; i++) { //petlja po broju dogadaja
        double sum = 0.;
        for (int tau = 1; tau <= N; tau++) { //petlja po tau (tau je od 1 do N)
            x= rand->Exp(tau); // Nasumična varijabla eksponencijalne distribucije exp(-x)
            sum += x;
        }
        histogram->Fill(sum);
    }

    double meanFromHistogram = histogram->GetMean(1);
    double meanExpected = N * 1.0 / 2; // Srednja vrijednost distribucije S predviđena Central Limit Theorem

    std::cout << "Srednja vrijednost distribucije sume S sa histograma: " << meanFromHistogram << std::endl;
    std::cout << "Srednja vrijednost distribucije S predviđena Central Limit Theorem: " << meanExpected << std::endl;

   histogram->SetLineColor(kRed-2);

    gPad -> SetLeftMargin (0.20);

   histogram->SetTitle("Distribucija sume S");
   histogram->GetXaxis()->SetTitle("exp(x/tau)");
   histogram->GetYaxis()->SetTitle("Distribucija sume S");

 
   histogram->Draw("HIST");

   c1->SaveAs("distribucija.pdf");
    delete histogram;


}