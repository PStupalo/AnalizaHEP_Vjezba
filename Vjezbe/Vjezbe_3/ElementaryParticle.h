#include <string>
#include<iostream>
#include<cmath>
#include<cstdlib> // Za korištenje random funkcije

using namespace std;

class ElementaryParticle
{
   public:
   //ElementaryParticle();// Konstruktor bez parametara (override)
   ElementaryParticle(string _name, float _mass, bool _isBoson); // Konstruktor s parametrima
   ElementaryParticle();
   ~ElementaryParticle();
   
   void SetMomentumComponents(float _px, float _py, float _pz); // Funkcija za postavljanje komponenata količine gibanja
   void SetVariables(string _name, float _mass, bool _isBoson);
   void PrintTransverseMomentum(); // Funkcija za ispis transverzalne količine gibanja
   void printInfo();  // Funkcija za ispis informacija o čestici
   void bosonDecay(ElementaryParticle& decayParticle_1, ElementaryParticle& decayParticle_2); // Funkcija za raspad bozona
   string name;
   float mass, px, py, pz, E;
   bool isBoson;

private:
    // Pomoćna funkcija za generiranje random brojeva između 0 i 1
    double getRandomNumber() const;

};