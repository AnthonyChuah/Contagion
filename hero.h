#ifndef HERO_H
#define HERO_H

#include "world.h"

/*
Header file for Hero class.
1. Heroes can own cards in their hand.
2. Heroes have a city they are located in. This is implemented as a pointer to the city object.
3. Heroes have a specialization which gives them particular powers, this is represented by a string.
*/

class Hero {
public:
  Hero(City* _ptr_city, World* _ptr_world, string _spec) : ptr_city(_ptr_city), ptr_world(_ptr_world), spec(_spec) {}
  // NOTE: Hero's City pointer should be set to Atlanta at initialization - to be done in setup file.
  ~Hero() {}
  //Hero(const Hero& copy_from);
  
  friend void World::draw_infection_deck(Hero& hero);
  // Declare function to be a friend so it can access private attributes in Hero.
  friend void World::draw_player_deck(Hero& hero);
  // Declare function to be a friend so it can access private attributes in Hero.

private:
  World* ptr_world; //pointer to the World
  City* ptr_city; // Pointer to a city.
  string spec; // Medic, Dispatcher, Researcher, Quarantine, Scientist, Operations
  std::vector<Card> hand;

  virtual void action()=0; //pure virtual function 
};

#endif
