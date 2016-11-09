#ifndef QSPECIALIST_H
#define QSPECIALIST_H

/*
Quarantine Specialist exceptions:
1. If QS is in a city, that city cannot be infected at all.
2. If QS is in a city, all neighbouring cities cannot be infected at all.
Implemented as exception in City::infect(int _did, int _ncubes).
*/

#include <string>

#include "city.h"
#include "world.h"
#include "hero.h"

class QSpecialist: public Hero
{
public:
  QSpecialist();
  QSpecialist(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
private:
  virtual bool spec_action();
}

#endif
