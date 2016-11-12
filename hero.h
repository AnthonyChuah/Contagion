#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>

/*
Header file for Hero class.
1. Heroes can own cards in their hand.
2. Heroes have a city they are located in. This is implemented as a pointer to the city object.
3. Heroes have a specialization which gives them particular powers, this is represented by a string.
*/

class Hero; // Forward-declaration necessary for Hero pointer used below.
class City;
class World;

class Hero
{
public:
  Hero();
  Hero(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
  Hero(const Hero& _copy); // Copy constructor to ensure good behaviour with STL data structures.
  Hero& operator =(const Hero& _assign); // Assignment operator needed for good behaviour with STL iterators.
  std::string get_spec();
  int get_heroid();
  bool charter_flight(City& _to, Hero* _user);
  bool direct_flight(City& _to, Hero* _user);
  bool shuttle_flight(City& _to, Hero* _user);
  bool move(City& _to, Hero* _user);
  bool disinfect(int _did);
  bool build_centre(City& _city); //build research centre - Redefined by OpExpert class
  bool give_card(std::string _card, Hero& _to); //give a card to another player
  bool take_card(std::string _card, Hero& _from); //take card from another player
  bool cure(int _did,std::string _one,std::string _two,std::string _three,std::string _four,std::string _five);
  bool check_end(); // Check if the player turn has ended.
  void start_turn(); // Set moves to 4.
  std::string spec;
  std::vector<PCard> hand;
  City* ptr_city;
  World* ptr_world;
  int hero_id;
  int moves;
};

#endif
