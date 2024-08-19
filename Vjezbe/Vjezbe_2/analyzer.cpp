#include<ElementaryParticle.h>

int main()
{
  ElementaryParticle Higgs("Higgs boson",125,1);
  ElementaryParticle TopQuark("Top quark",173,0);
  ElementaryParticle *Z = new ElementaryParticle("Z boson", 90,1);
  Higgs.printInfo();
  TopQuark.printInfo();
  Z->printInfo();
  delete Z;
  return 0;
}