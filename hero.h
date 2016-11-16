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
  void start_turn(); // Set moves to 4.
  // Heroes have their own functions, however the program will not compile if we do not define a virtual function
  // that has the same name as the specialist subclass function, because there will be no late-binding of function
  // names. Here I declare virtual specialist functions.
  virtual bool play_special_eventcard(std::string _arguments);
  virtual bool get_special_eventcard(std::string _eventname);
  virtual bool dispatch_control(int _hid, std::string _arguments);
  virtual bool dispatch_move(int _hidfrom, int _hidto);
  virtual bool opex_flight(City& _to, std::string _card);
  virtual bool scientist_cure(int _did, std::string _one, std::string _two, std::string _three, std::string _four);
  std::string spec;
  std::vector<PCard> hand;
  City* ptr_city;
  World* ptr_world;
  int hero_id;
  int moves;
};

#endif
