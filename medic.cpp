// Implementation file for the Medic class.

#include "macros.h"

#include <string>
#include <iostream>

Medic::Medic() : Hero()
{}

Medic::Medic(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(_ptr_city, _ptr_world, _hid, _spec)
{}
