#include <Analyzer.h>

int main()
{
  // Declare Analyzer
  Analyzer *analyzer = new Analyzer();
 
  analyzer->PlotHistogram();

  analyzer->~Analyzer();

  return 0;
}
