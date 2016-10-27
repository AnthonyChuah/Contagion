#ifndef RESEARCHER_H
#define RESEARCHER_H

#include "hero.h"

class Researcher: public Hero {
 public:
  // Constructor
  Researcher(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}
  
 private:
  // Function to implement the Researcher specialist action
  // - give ANY city card to another player in same city, without it having to match the city
  virtual void spec_action();
}

#endif
