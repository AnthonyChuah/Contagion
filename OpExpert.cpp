// Implementation file for the Operations Expert class

#include "macros.h"

#include <iostream>
#include <string>

/*
1. OpExpert can build RCs without using cards. This is done directly in Hero::build_centre.
2. OpExpert can fly to any city by discarding any card at all, as long as he is at a RC. opex_flight function.
   He can only do this once per turn, so he gets a flag called opex_flew_this_turn.
*/

OpExpert::OpExpert() : Hero() { bool opex_flew_this_turn = false; }

OpExpert::OpExpert(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(_ptr_city, _ptr_world, _hid, _spec)
{
  opex_flew_this_turn = false;
}

void OpExpert::start_turn()
{
  std::cout << "OpExpert::start_turn called.\n";
  opex_flew_this_turn = false; moves = 4;
}

bool OpExpert::opex_flight(City& _to, std::string _card)
{
  // City OpExpert is in must have a RC.
  if (ptr_city->has_rc()) {
    // OpExpert can discard ANY card to flyto ANY city as long as he is at a RC.
    std::vector<PCard>::iterator it;
    for (it = hand.begin(); it != hand.end(); it++) {
      if (it->name == _card) {
	ptr_city->depart_hero(hero_id);
	ptr_city = &_to;
	ptr_city->arrive_hero(hero_id);
	hand.erase(it);
	opex_flew_this_turn = true;
	moves--;
	return true;
      }
    }
    return false;
  } else {
    return false;
  }
}
