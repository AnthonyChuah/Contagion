#ifndef OPEXPERT_H
#define OPEXPERT_H

/*
Exceptions for Operations Expert:
1. Build RC in the city it is in without using a city card.
2. Once per turn, teleport from an RC to any city by using any city card (no match needed).
Implemented as exception in build_centre function, and as a special function called opex_flight.
*/

#include <string>

class OpExpert : public Hero
{
public:
  OpExpert();
  OpExpert(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
  // Build research centre WITHOUT DISCARDING a city card, implemented as exception in build_centre.
  // When starting a new turn, set opex_flew_this_turn to false.
  void start_turn(); // REDEFINES Hero::start_turn().
  bool opex_flight(City& _to, std::string _card);
  // Special power allows OpExpert to fly to another city by discarding any city card.
private:
  bool opex_flew_this_turn;
};

#endif
