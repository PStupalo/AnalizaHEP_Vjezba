#include<ElementaryParticle.h>

ElementaryParticle::ElementaryParticle(string _name, float _mass, bool _isBoson)
{
  name=_name;
  mass=_mass;
  isBoson=_isBoson;
}
void ElementaryParticle::printInfo()
{
  cout<<"Particle properties"<<endl<<"name:"<<name<<endl<<"mass:"<<mass<<endl<<"isBoson:"<<isBoson<<endl;
}