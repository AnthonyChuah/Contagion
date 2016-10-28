#ifndef MEDIC_H
#define MEDIC_H

#include "hero.h"

#include <iostream>


class Medic: public Hero {
 public:
  // Constructor
  Medic(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}

  void disinfect(int d_id); //Redefined -- removes ALL cubes of the same colour when doing "disinfect" action
  
 private:
  // Function to implement the Medic specialist action - Medic has no specialist action
  virtual void spec_action()  {
    std::cout<<"The medic does not have a separate specialist action.";
  }

  
};

#endif
