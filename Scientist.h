#ifndef SCIENTIST_H
#define SCIENTIST_H

#include "hero.h"

#include <iostream>

class Scientist: public Hero {
 public:
  // Constructor
  Scientist(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}

  virtual void cure(int disease_id); //Scientist redefines the function in the Superclass
  
 private:
  // Function to implement the specialist action (not available for Scientist, so does nothing) 
  virtual void spec_action() {
    std::cout<<"The scientist does not have a specialist action.";
  }
}

#endif
