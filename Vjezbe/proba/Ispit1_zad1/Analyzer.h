#include<iostream>
#include <TROOT.h>
#include <TH1F.h>
#include <cmath>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
using namespace std;
class Analyzer
{
  public:
   Analyzer();
   ~Analyzer();
   void ProoveCLT();
};