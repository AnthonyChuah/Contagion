// Implementation file for the Operations Expert class

#include "macros.h"

#include <iostream>
#include <string>

OpExpert::OpExpert() : Hero() { bool opex_flew_this_turn = false; }

OpExpert::OpExpert(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(_ptr_city, _ptr_world, _hid, _spec)
{
  opex_flew_this_turn = false;
}

void OpExpert::start_turn() { opex_flew_this_turn = false; moves = 4; }

bool OpExpert::opex_flight(City& _to, std::string _card)
{
  // City OpExpert is in must have a RC.
  if (ptr_city->has_rc()) {
    std::vector<PCard>::iterator it;
    for (it = hand.begin(); it != hand.end(); it++) {
      if (it->name == _card) {
	ptr_city->depart_hero(hero_id);
	ptr_city = &_to;
	ptr_city->arrive_hero(hero_id);
	hand.erase(it);
	opex_flew_this_turn = true;
	moves--;
	check_end();
	return true;
      }
    }
    return false;
  } else {
    return false;
  }
}
