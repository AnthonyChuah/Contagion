// Implementation file for the Medic class

#include <iostream>
#include <cmath>
#include "hero.h"
#include "Medic.h"


/* -- Disinfect function: removes ALL cubes of the same colour when doing 
      the "disinfect" action.                                              -- */
void Medic::disinfect(int d_id) {
  //ptr_world->
  // Setting the disease counter to zero for the disease "d_id"
  ptr_city->disease_counters[d_id] = 0;   
}
