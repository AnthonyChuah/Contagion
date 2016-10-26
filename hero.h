#ifndef HERO_H
#define HERO_H

/*
Header file for Hero class.
1. Heroes can own cards in their hand.
2. Heroes have a city they are located in. This is implemented as a pointer to the city object.
3. Heroes have a specialization, 
*/

class Hero
{
public:
  Hero();
  Hero(string specialization);
  string get_spec();
  bool fly(City& to_city);
  bool move(City& to_city);
  void disinfect(int d_id);
  void build_centre(City& city);
  void get_card(Card card);
private:
  City* ptr_city; // Pointer to a city.
  string spec; // Medic, Dispatcher, Researcher, Quarantine, Scientist, Operations
  list<Card> hand;
};

#endif
