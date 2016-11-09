#ifndef RESEARCHER_H
#define RESEARCHER_H

/*
Researcher exceptions:
1. Researcher may give any card to another hero in the same city.
2. Another player in the same city may take any card from the Researcher's hand.
These are implemented as exceptions in give_card and take_card.
*/

#include <string>

#include "city.h"
#include "world.h"
#include "hero.h"

class Researcher: public Hero
{
public:
  // Constructors are not automatically inherited from Hero, but these will call Hero's constructors.
  Researcher();
  Researcher(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
private:
  virtual bool spec_action();
}

#endif
