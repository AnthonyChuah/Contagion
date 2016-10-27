#ifndef QSPECIALIST_H
#define QSPECIALIST_H

#include "hero.h"

#include <iostream>

class QSpecialist: public Hero {
 public:
  // Constructor
  QSpecialist(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}

 private:
  // Function to implement any specialist action - Quarantine Specialist has no specialist action, only a passive special
  virtual void spec_action()  {
    std::cout<<"The quarantine specialist does not have a specialist action.";
  }
 
}

#endif
