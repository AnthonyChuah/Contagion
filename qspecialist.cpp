// Implementation file for the Quarantine Specialist class.

#include <string>
#include <iostream>

#include "hero.h"
#include "city.h"
#include "world.h"
#include "pcard.h"
#include "qspecialist.h"

QSpecialist::QSpecialist() : Hero()
{}

QSpecialist::QSpecialist(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec)
{}

bool QSpecialist::spec_action()
{
  std::cout << "No specialist action for the Quarantine Specialist.\n";
  return false;
}
