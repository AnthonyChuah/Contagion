#ifndef MEDIC_H
#define MEDIC_H

/*
Medic exceptions:
1. Disinfect will remove all cubes of the colour.
2. If disease cured, simply being in the city will prevent cube placement.
3. Upon curing a disease, wherever the Medic is should be wiped of that disease's cubes.
4. Upon moving to a new city, that new city should have all CURED cubes removed.
5. Upon flying to a new city, that new city should have all CURED cubes removed.
6. Upon BEING DISPATCHED by the dispatcher's ability, destination should have CURED cubes removed.
*/

#include <string>

class Medic : public Hero
{
public:
  // Constructor calls superclass constructor. Hero::Hero() constructors not automatically inherited.
  Medic();
  Medic(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
  // All other functions are automatically inherited.
};

#endif
