#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "hero.h"

class Dispatcher: public Hero {
 public:
  // Constructor
  Dispatcher(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}

 private:
  // Function to implement the Dispatcher specialist action:
  //   move any pawn to any city containing other pawn, or move another player's pawn as if it was the player's own
  virtual void spec_action();
}

#endif
