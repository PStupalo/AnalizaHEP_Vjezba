#ifndef Analyzer_h
#define Analyzer_h

#include <TMath.h>
#include <TRandom3.h>
#include <TH1F.h>
#include <iostream>

using namespace std;

class Analyzer {
public:
    Analyzer();
    void CentralLimitTheorem();

//private:
    TRandom3 *rand;
    TH1F *histogram;
};

#endif
