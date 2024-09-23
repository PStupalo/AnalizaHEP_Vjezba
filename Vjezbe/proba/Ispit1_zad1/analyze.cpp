#include<Analyzer.h>
int main()
{
  Analyzer *analyzer=new Analyzer();
  analyzer->ProoveCLT();
  analyzer->~Analyzer();
  return 0;
}