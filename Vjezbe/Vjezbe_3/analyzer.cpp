#include "ElementaryParticle.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
int main()
{
  // sjeme randoma
    srand(static_cast<unsigned>(time(0)));
    // otvaranje datoteke za pisanje
     ofstream myfile;
  myfile.open ("Analysis.txt");
  myfile << "DecayParticle1_Name DecayParticle1_isBoson DecayParticle1_mass DecayParticle1_E DecayParticle1_px DecayParticle1_py DecayParticle1_pz"<<" "
         << "DecayParticle2_Name DecayParticle2_isBoson DecayParticle2_mass DecayParticle2_E DecayParticle2_px DecayParticle2_py DecayParticle2_pz" << endl;
  //1. i 2. zad
  /*ElementaryParticle Higgs("Higgs boson",125,1);
  // Kreiramo čestice koje će biti produkti raspada
  ElementaryParticle decayParticle_1, decayParticle_2;
  //Higgs.SetMomentumComponents(40,30,60); 1.zad
  Higgs.printInfo(); //info prije raspada
  //raspad Higgsovog bozona
  Higgs.bosonDecay(decayParticle_1, decayParticle_2);
  // Ispisujemo informacije o raspadnim česticama
  std::cout << "Decay products:\n";
  decayParticle_1.printInfo();
  decayParticle_2.printInfo();*/


  for (int i = 0; i < 10000; ++i) { //zelimo generirati 10 000 Higgsovih bozona
        ElementaryParticle Higgs("Higgs Boson", 125.1, true); //stvaramo Higgsa
        //generiramo random vrijednosti komponenti kol.gib. u zadanom rangeu (-100, 100)
        float px = -100 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(200)));
        float py = -100 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(200)));
        float pz = -100 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(200)));

        Higgs.SetMomentumComponents(px, py, pz); //postavljamo generirane vrijednosti u objekt

        ElementaryParticle decayParticle_1, decayParticle_2; //raspadnute cestice
        Higgs.bosonDecay(decayParticle_1, decayParticle_2); //raspad

        //ispis dobivenih podataka u datoteku
        myfile << decayParticle_1.name<<" "<<decayParticle_1.isBoson<<" "<<decayParticle_1.mass<<" "<<decayParticle_1.E
           <<" "<<decayParticle_1.px<<" "<<decayParticle_1.py<<" "<<decayParticle_1.pz<<" "
           <<decayParticle_2.name<<" "<<decayParticle_2.isBoson<<" "<<decayParticle_2.mass<<" "<<decayParticle_2.E
           <<" "<<decayParticle_2.px<<" "<<decayParticle_2.py<<" "<<decayParticle_2.pz<<endl;
        
      }  
  myfile.close();
  return 0;
}