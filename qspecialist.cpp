// Implementation file for the Quarantine Specialist class.

#include "macros.h"

#include <string>
#include <iostream>

QSpecialist::QSpecialist() : Hero()
{}

QSpecialist::QSpecialist(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(_ptr_city, _ptr_world, _hid, _spec)
{}
