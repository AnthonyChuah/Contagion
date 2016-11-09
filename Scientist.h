#ifndef SCIENTIST_H
#define SCIENTIST_H

/*
Scientist exceptions:
1. Scientist requires only 4 player cards of the same colour to cure a disease.
*/

#include <string>

#include "city.h"
#include "world.h"
#include "hero.h"

class Scientist: public Hero
{
public:
  Scientist();
  Scientist(City* _ptr_city, World* _ptr_world, std::string _spec);
  bool cure(int _did, std::string _one, std::string _two, std::string _three, std::string _four);
private:
  virtual bool spec_action();
}

#endif
