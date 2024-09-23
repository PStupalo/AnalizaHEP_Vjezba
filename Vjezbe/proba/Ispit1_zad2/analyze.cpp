#include<Analyzer.h>
int main()
{
  Analyzer *analyzer=new Analyzer();
  analyzer->MakeFit();
  analyzer->~Analyzer();
  return 0;
}