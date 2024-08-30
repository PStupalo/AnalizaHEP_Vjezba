#include "Analyzer.h"

int main() {
    TTree *tree = nullptr;
    Analyzer *analyzer = new Analyzer(tree);
    analyzer->RunAnalysis();
    analyzer->TestHypotheses();
    delete analyzer;
    return 0;
}

