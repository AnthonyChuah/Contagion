#ifndef HERO_H
#define HERO_H

/*
Header file for Hero class.
1. Heroes can own cards in their hand.
2. Heroes have a city they are located in. This is implemented as a pointer to the city object.
3. Heroes have a specialization which gives them particular powers, this is represented by a string.
*/

class Hero
{
public:
  Hero();
  Hero(string specialization); // Hero's City pointer should be set to Atlanta at initialization.
  ~Hero();
  Hero(const Hero& copy_from);
  string get_spec();
  bool fly(City& to_city);
  bool move(City& to_city);
  void disinfect(int d_id);
  void build_centre(City& city);
  friend void World::draw_infection_deck(Hero& hero);
  // Declare function to be a friend so it can access private attributes in Hero.
  friend void World::draw_player_deck(Hero& hero);
  // Declare function to be a friend so it can access private attributes in Hero.
private:
  City* ptr_city; // Pointer to a city.
  string spec; // Medic, Dispatcher, Researcher, Quarantine, Scientist, Operations
  list<Card> hand;
};

#endif
