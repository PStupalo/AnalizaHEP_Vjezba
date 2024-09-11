
#include "Analyzer.h"

int main() {
    Analyzer* analyzer = new Analyzer();

    analyzer->GeneratePseudoExperiments(); // Generiraj pseudo-eksperimente
    analyzer->ChiSquareDistribution(); // Prikaži Chi-Square distribuciju
    analyzer->CalculateChiSquare(); // Izračunaj Chi-Square za stvarni histogram i dodaj liniju

    delete analyzer;
    return 0;
}
