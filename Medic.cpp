// Implementation file for the Medic class.

#include <string>
#include <iostream>

#include "hero.h"
#include "world.h"
#include "city.h"
#include "pcard.h"
#include "medic.h"

Medic::Medic() : Hero()
{}

Medic::Medic(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec)
{}

bool Medic::spec_action()
{
  std::cout << "No specialist action for the Medic.\n";
  return false;
}
