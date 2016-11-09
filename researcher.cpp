// Implementation file for the Researcher class.

#include <string>
#include <iostream>

#include "hero.h"
#include "world.h"
#include "researcher.h"

Researcher::Researcher() : Hero()
{}

Researcher::Researcher(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec)
{}

bool Researcher::spec_action()
{
  std::cout << "No specialist action for the Researcher.\n";
  return false;
}
