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

    TH1F* h_H0 = new TH1F("h_H0", "Median Distribution for H0", 100, 0, 10);
    TH1F* h_H1 = new TH1F("h_H1", "Median Distribution for H1", 100, 0, 10);

    for (int experiment = 0; experiment < numExperiments; experiment++) {
        vector<double> dataH0(numMeasurements), dataH1(numMeasurements);

        for (int i = 0; i < numMeasurements; i++) {
            dataH0[i] = GenerateValue(0.9);
            dataH1[i] = GenerateValue(1.1);
        }

        h_H0->Fill(CalculateMedian(dataH0));
        h_H1->Fill(CalculateMedian(dataH1));
    }

    h_H0->Scale(1.0 / h_H0->Integral());
    h_H1->Scale(1.0 / h_H1->Integral());

    TCanvas* canvas = new TCanvas("canvas", "Hypothesis Testing Results", 800, 600);
    h_H0->SetLineColor(kGreen + 2);
    h_H1->SetLineColor(kMagenta + 2);
    h_H0->Draw();
    h_H1->Draw("SAME");

    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_H0, "H0: parameter = 0.9", "l");
    legend->AddEntry(h_H1, "H1: parameter = 1.1", "l");
    legend->Draw();
    canvas->SaveAs("HypothesisResults.png");
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

