// Implementation file for the Operations Expert class

#include <iostream>
#include <string>

#include "world.h"
#include "city.h"
#include "pcard.h"
#include "hero.h"
#include "opexpert.h"

OpExpert::OpExpert() : Hero() { bool opex_flew_this_turn = false; }

OpExpert::OpExpert(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec)
{}

void OpExpert::start_turn() { opex_flew_this_turn = false; moves = 4; }

bool OpExpert::opex_flight(City& _to, std::string _card)
{
  // City OpExpert is in must have a RC.
  if (ptr_city->has_rc()) {
    std::list<PCard>::iterator it;
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

void OpExpert::spec_action()
{
  std::cout << "Presently implementation of OpExpert rests in special function build_centre.\n";
}
