#ifndef HERO_H
#define HERO_H

/*
Header file for Hero class.
*/

class Hero
{
public:
  string get_spec();
  void fly(City& to_city);
  void move(City& to_city);
  void disinfect(int d_id);
  void build_centre(City& city);
private:
  City* ptr_city;
  string spec;
  string spec_full;
  // medic, quarantine, scientist, researcher, dispatcher, ops.
  list<Card> hand;
};

#endif
