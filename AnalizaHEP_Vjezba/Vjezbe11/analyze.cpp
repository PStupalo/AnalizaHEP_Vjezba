#include"Analyzer.h"
int main()
{
  Analyzer *analyzer=new Analyzer();
  //cout<<analyzer->Binomial(6,0.6,6)<<endl;
  //cout<<analyzer->CPinterval(0.683,10,1).second<<endl;
  //cout<<analyzer->CPinterval(0.683,10,1).first<<endl;
  analyzer->CPbelt(10,0.6827);
  analyzer->Game();
  analyzer->~Analyzer();
  return 0;
}