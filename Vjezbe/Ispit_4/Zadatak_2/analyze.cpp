// analyze.cpp
#include "Analyzer.h"

int main() {
    // Kreiraj objekt analizatora s navedenom datotekom
    Analyzer* analyzer = new Analyzer("/home/public/data/BinomialHisto.root");

    // Učitaj histogram i generiraj pseudoeksperimente
    analyzer->LoadHistogram();

    // Oslobađanje memorije
    delete analyzer;
    return 0;
}
