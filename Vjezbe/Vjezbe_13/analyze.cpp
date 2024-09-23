// C++
#include <iostream>
#include <fstream>

// My own class
#include <Analyzer.h>

using namespace std;

int main()
{
  // Declare Analyzer
  Analyzer *analyzer;

  analyzer = new Analyzer();

  analyzer->Generate_TestStatistic_H0();
  analyzer->PValueCalculation();

  analyzer->CompareHypothesis("France", 164.7, 7.1);
  analyzer->CompareHypothesis("Italy", 166.1, 6.5);
  analyzer->CompareHypothesis("Netherlands", 170.3, 7.5);

  delete analyzer;

  return 0;
}