#include "Analyzer.h"

int main(void){

    Analyzer *analyzer = new Analyzer();
    analyzer->CentralLimitTheorem();

    delete analyzer;
    return 0;
}
