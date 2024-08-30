#include "Analyzer.h"

int main() {
    Analyzer *analyzer = new Analyzer();

    analyzer->FitHistogram(); // Fitanje histograma
    analyzer->DrawNegativeLogLikelihood(); // Nacrtaj -2lnL funkciju
    analyzer->DrawFitAndHistogram(); // Nacrtaj histogram i fitanu funkciju

    delete analyzer; // Oslobodi memoriju

    return 0;
}

