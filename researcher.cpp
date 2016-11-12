// Implementation file for the Researcher class.

#include "macros.h"

#include <string>
#include <iostream>

Researcher::Researcher() : Hero()
{}

Researcher::Researcher(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(_ptr_city, _ptr_world, _hid, _spec)
{}
