#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>
#include "world.h"
#include "city.h"

using namespace std;

/*
Header file for Hero class.
1. Heroes can own cards in their hand.
2. Heroes have a city they are located in. This is implemented as a pointer to the city object.
3. Heroes have a specialization which gives them particular powers, this is represented by a string.
*/

class Hero {
public:
  Hero(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}
  // NOTE: Hero's City pointer should be set to Atlanta at initialization.
  Hero(const Hero& copy_from); // Copy constructor to ensure good behaviour with STL data structures.
  ~Hero() {}

  string get_spec() { return spec; }
  bool fly(City& to_city);
  bool move(City& to_city);
  void disinfect(int d_id); // treat disease - redefined by Medic class
  void build_centre(City& city); //build research centre - Redefined by OpExpert class

  // Share cards
  void give_card(PCard* card, Hero& p_to); //give a card to another player
  void take_card(PCard* card, Hero& p_from); //take card from another player

  // Cure a disease -- if five cards of same colour in hand, cure disease of that colour
  void cure(int disease_id);
    // NOTE: Scientist class redefines this, as scientist needs 4 cards of same colour
  
  friend void World::draw_infection_deck(Hero& hero);
  // Declare function to be a friend so it can access private attributes in Hero.
  friend void World::draw_player_deck(Hero& hero);
  // Declare function to be a friend so it can access private attributes in Hero.

private:
  World* ptr_world; //pointer to the World
  City* ptr_city; // Pointer to a city.
  string spec; // Medic, Dispatcher, Researcher, Quarantine, Scientist, Operations
  list<PCard> hand;

  virtual void spec_action()=0; //pure virtual function for special actions 
};

#endif
