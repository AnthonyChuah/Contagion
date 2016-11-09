#ifndef CONTPLANNER_H
#define CONTPLANNER_H

#include <string>

#include "city.h"
#include "world.h"
#include "hero.h"

class ContPlanner: public Hero
{
public:
  // Constructors are not automatically inherited from Hero, but these will call Hero's constructors.
  ContPlanner();
  ContPlanner(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
  bool play_special_eventcard(std::string _arguments);
  bool get_special_eventcard(std::string _eventname);
private:
  virtual bool spec_action();
  PCard eventcard; // Contingency Planner has a special slot for an event card that does not occupy the hand.
};

// Function to implement the Contingency Planner specialist action - take event card in discard pile
// Let's have viewing of cards done at World, since all players can view.
// void view_discarded_events(std::list<PCard>& list);

#endif
