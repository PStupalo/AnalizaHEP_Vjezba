#include<ElementaryParticle.h>

ElementaryParticle::ElementaryParticle() : name(""), mass(0), isBoson(false), px(0), py(0), pz(0), E(0) {}

ElementaryParticle::~ElementaryParticle() {}

ElementaryParticle::ElementaryParticle(string _name, float _mass, bool _isBoson)
{
  name=_name;
  mass=_mass;
  isBoson=_isBoson;
}
void ElementaryParticle::printInfo()
{
  cout<<"Particle properties"<<endl<<"name:"<<name<<endl<<"mass:"<<mass<<endl<<"isBoson:"<<isBoson<<endl;
  cout<<"Energy:"<<E<<endl<<"px:"<<px<<endl<<"py:"<<py<<endl<<"pz:"<<pz<<endl;
}
void ElementaryParticle::SetMomentumComponents(float _px, float _py, float _pz) //prvi zadatak, dodavanje clanova cetverovektora cestice
{
  px = _px;
  py = _py;
  pz = _pz;
  E = sqrt(pow(px,2)+pow(py,2)+pow(pz,2)+pow(mass,2)); //formula raspisana za svaku komponentu kol.gib.
}
void ElementaryParticle::PrintTransverseMomentum() //ispisivanje transverzalne kol.gib. po formuli iz zadatka
{
  cout<<"pT="<<sqrt(pow(px,2)+pow(py,2))<<"GeV"<<endl;
}

double ElementaryParticle::getRandomNumber() const { //funkcija kojom generiramo random broj izmedu 0 i 1
    return static_cast<double>(rand()) / RAND_MAX;
}

void ElementaryParticle::bosonDecay(ElementaryParticle& decayParticle_1, ElementaryParticle& decayParticle_2) {
    if (!isBoson) { //ako nije bozon, raspad je nemoguć
        std::cout << "Raspad nije moguc jer cestica nije bozon.\n";
        return;
    }
    double decayProbability = getRandomNumber(); //get random nam daje broj izmedu 0 i 1, za postotak mnozimo sa 100
    //na koje cestice raspad ide (iz zadatka, u kojem postotku)
    if (decayProbability <= 0.214) {
        decayParticle_1.SetVariables("W Boson", 80.379, true);
        decayParticle_2.SetVariables("W Boson", 80.379, true);
    } else if (decayProbability <= 0.214 + 0.064) {
        decayParticle_1.SetVariables("Tau Lepton", 1.776, false);
        decayParticle_2.SetVariables("Tau Lepton", 1.776, false);
    } else if (decayProbability <= 0.214 + 0.064 + 0.026) {
        decayParticle_1.SetVariables("Z Boson", 91.1876, true);
        decayParticle_2.SetVariables("Z Boson", 91.1876, true);
    } else {
        decayParticle_1.SetVariables("b Quark", 4.18, false);
        decayParticle_2.SetVariables("b Quark", 4.18, false);
    }

    //decayParticle_1.mass = decayParticle_2.mass = mass / 2.0;
    // Nasumično raspodjeljujemo komponente količine gibanja između dvije raspadne čestice.
    decayParticle_1.SetMomentumComponents(px * getRandomNumber(), py * getRandomNumber(), pz * getRandomNumber());
    decayParticle_2.SetMomentumComponents(px * (1.0 - getRandomNumber()), py * (1.0 - getRandomNumber()), pz * (1.0 - getRandomNumber()));

}

void ElementaryParticle::SetVariables(std::string _name, float _mass, bool _isBoson) {
    name = _name;
    mass = _mass;
    isBoson = _isBoson;
    px = py = pz = E = 0;
}