#ifndef HERO_H
#define HERO_H

#include <string>
#include <list>
#include "world.h"
#include "city.h"

/*
Header file for Hero class.
1. Heroes can own cards in their hand.
2. Heroes have a city they are located in. This is implemented as a pointer to the city object.
3. Heroes have a specialization which gives them particular powers, this is represented by a string.
*/

class Hero {
public:
  Hero();
 Hero(City* _ptr_city, World* _ptr_world, std::string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec);
  Hero(const Hero& _copy); // Copy constructor to ensure good behaviour with STL data structures.
  Hero& operator =(const Hero& _assign); // Assignment operator needed for good behaviour with STL iterators.
  string get_spec() { return spec; }
  bool fly(City& _to); // Split into two versions: charter_flight and direct_flight.
  bool charter_flight(City& _to);
  bool direct_flight(City& _to);
  bool move(City& _to);
  void disinfect(int _did); // treat disease - redefined by Medic class
  void build_centre(City& _city); //build research centre - Redefined by OpExpert class
  void give_card(PCard* card, Hero& p_to); //give a card to another player
  void take_card(PCard* card, Hero& p_from); //take card from another player
  void cure(int disease_id); // NOTE: Scientist class redefines this, as scientist needs 4 cards of same colour
  void end_turn(); // World should now infect cities and then draw player cards then switch to another player.
  friend void World::draw_infection_deck(Hero& hero);
  friend void World::draw_player_deck(Hero& hero);
private:
  World* ptr_world;
  City* ptr_city;
  int hero_id;
  int moves;
  std::string spec;
  std::list<PCard> hand;
  virtual void spec_action()=0; // Pure virtual function to be instantiated in the subclasses.
};

#endif
