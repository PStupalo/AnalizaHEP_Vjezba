#include "Analyzer.h"
int main()
{
  Analyzer* analyzer = new Analyzer();
  analyzer->LifetimeFit();
  analyzer->~Analyzer();
  return 0;
}