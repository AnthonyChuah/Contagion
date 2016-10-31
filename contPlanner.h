#ifndef CONTPLANNER_H
#define CONTPLANNER_H

#include "hero.h"

class ContPlanner: public Hero {
 public:
  // Constructor
  ContPlanner(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}
  
 private:
  // Function to implement the Contingency Planner specialist action - take event card in discard pile
  virtual void spec_action();

  // Helper function
  void view_discarded_events(std::list<PCard>& list);

};

#endif
