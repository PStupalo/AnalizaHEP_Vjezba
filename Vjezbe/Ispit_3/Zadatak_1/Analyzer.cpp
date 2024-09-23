#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

Analyzer::Analyzer(TTree *tree) : fChain(0) {
    if (tree == 0) {
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/HypothesisTestMedian.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("/home/public/data/HypothesisTestMedian.root");
        }
        f->GetObject("tree", tree);
    }
    randomGenerator = new TRandom3();
    Init(tree);
}

Analyzer::~Analyzer() {
    if (!fChain) return;
    delete fChain->GetCurrentFile();
    delete randomGenerator;
}

void Analyzer::RunAnalysis() {
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
    }
}

void Analyzer::TestHypotheses() {
    const int numExperiments = 10000;
    const int numMeasurements = 1000;

    TH1F* h_H0 = new TH1F("h_H0", "Median Distribution for H0", 100, 0, 1);
    TH1F* h_H1 = new TH1F("h_H1", "Median Distribution for H1", 100, 0, 1);

    for (int experiment = 0; experiment < numExperiments; experiment++) {
        vector<double> dataH0(numMeasurements), dataH1(numMeasurements);

        for (int i = 0; i < numMeasurements; i++) {
            dataH0[i] = GenerateValue(0.9);
            dataH1[i] = GenerateValue(1.1);
        }

        h_H0->Fill(CalculateMedian(dataH0));
        h_H1->Fill(CalculateMedian(dataH1));
    }

    // Normalizacija histograma
    h_H0->Scale(1.0 / h_H0->Integral());
    h_H1->Scale(1.0 / h_H1->Integral());

    // Postavljanje stila platna
    TCanvas* canvas = new TCanvas("canvas", "Hypothesis Testing Results", 800, 600);
    canvas->SetGrid();
    gStyle->SetOptStat(0); // Sakrij statističke informacije

    // Podešavanje stila za histograme
    h_H0->SetLineColor(kRed);
    h_H0->SetLineWidth(2);
    h_H1->SetLineColor(kBlue);
    h_H1->SetLineWidth(2);

    // Crtanje histograma
    h_H0->Draw("HIST");
    h_H1->Draw("HIST SAME");

    // Dodavanje legendi
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_H0, "H0: alpha = 0.9", "l");
    legend->AddEntry(h_H1, "H1: alpha = 1.1", "l");
    legend->Draw();

    // Dodavanje vertikalnih linija za medijane
    double median_H0 = h_H0->GetBinCenter(h_H0->GetMaximumBin());
    double median_H1 = h_H1->GetBinCenter(h_H1->GetMaximumBin());

    TLine* line_H0 = new TLine(median_H0, 0, median_H0, h_H0->GetMaximum());
    line_H0->SetLineColor(kRed);
    line_H0->SetLineStyle(2);
    line_H0->SetLineWidth(2);
    line_H0->Draw();

    TLine* line_H1 = new TLine(median_H1, 0, median_H1, h_H1->GetMaximum());
    line_H1->SetLineColor(kBlue);
    line_H1->SetLineStyle(2);
    line_H1->SetLineWidth(2);
    line_H1->Draw();

    canvas->SaveAs("HypothesisResults_with_Lines.png");
}

void Analyzer::Init(TTree *tree) {
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("x", &x, &b_x);
    Notify();
}

Bool_t Analyzer::Notify() {
    return kTRUE;
}

Int_t Analyzer::GetEntry(Long64_t entry) {
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t Analyzer::LoadTree(Long64_t entry) {
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

void Analyzer::Show(Long64_t entry) {
    if (!fChain) return;
    fChain->Show(entry);
}

Int_t Analyzer::Cut(Long64_t entry) {
    return 1;
}

double Analyzer::GenerateValue(double parameter) {
    return randomGenerator->Exp(1.0 / parameter);
}

double Analyzer::CalculateMedian(vector<double>& data) {
    sort(data.begin(), data.end());
    size_t mid = data.size() / 2;
    return data.size() % 2 == 0 ? (data[mid - 1] + data[mid]) / 2.0 : data[mid];
}

