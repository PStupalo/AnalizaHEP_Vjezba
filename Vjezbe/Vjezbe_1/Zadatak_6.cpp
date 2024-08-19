#include<iostream>
#include<string>
using namespace std;

class ElementaryParticle
{
  public:
    string name; //ime cestice
    float mass; //masa
    bool isBoson; // je li bozon, da/ne (true;1/false;0)
//Konstruktor
ElementaryParticle(string _name, float _mass, bool _isBoson)
{
   name=_name;
   mass=_mass;
   isBoson=_isBoson;
}
//ispis
void printInfo()
{
    //ispisujemo podatke o cestici
  cout<<"Particle properties"<<endl<<"name:"<<name<<endl<<"mass:"<<mass<<endl<<"isBoson:"<<isBoson<<endl;
}
};

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



    /* B. Kreiranje pokazivača na objekt za Z bozon
    ElementaryParticle* zBoson = new ElementaryParticle;
    zBoson->name = "Z bozon";
    zBoson->mass = 91.2;
    zBoson->isBoson = true;*/
}