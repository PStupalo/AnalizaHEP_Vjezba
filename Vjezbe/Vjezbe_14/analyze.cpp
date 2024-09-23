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

  analyzer->GenerateTestStatisticPDF(1000);

  analyzer->ExpectedPValueScan();

  delete analyzer;

  return 0;
}