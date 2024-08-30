#include "Analyzer.h"

int main() {
    // Kreiranje objekta klase Analyzer
    Analyzer *analyzer = new Analyzer();

    // Fitanje histograma pomoću binned Maximum Likelihood metode
    analyzer->FitHistogram();

    // Crtanje dvostrukog negativnog logaritma Likelihood funkcije (-2lnL) u ovisnosti o parametru a
    analyzer->PlotNegativeLogLikelihood();

    // Brisanje objekta kako bi se oslobodili resursi
    delete analyzer;

    return 0;
}

