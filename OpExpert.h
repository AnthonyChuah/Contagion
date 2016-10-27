#ifndef OPEXPERT_H
#define OPEXPERT_H

#include "hero.h"

class OpExpert: public Hero {
 public:
  // Constructor
  OpExpert(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}

  void build_centre(City& city); //build research centre WITHOUT DISCARDING a city card, redefines build_centre
  
 private:
  // Function to implement the Operations Expert specialist action:
  // - fly from a research station to any city by discarding any city card
  virtual void action();
}

#endif
