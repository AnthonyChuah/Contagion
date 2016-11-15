// Implementation file for the Scientist class.

#include "macros.h"

#include <string>
#include <iostream>

Scientist::Scientist() : Hero()
{}

Scientist::Scientist(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(_ptr_city, _ptr_world, _hid, _spec)
{}

bool Scientist::scientist_cure(int _did, std::string _one, std::string _two, std::string _three, std::string _four)
{
  std::cout << "Calling Scientist::cure() on disease ID " << _did << ".\n";
  std::vector<PCard>::iterator it;
  int count_matches = 0;
  for (it = hand.begin(); it != hand.end(); it++)
    if (it->disease_id == _did &&
	(it->name == _one || it->name == _two || it->name == _three || it->name == _four))
      count_matches++;
  if (count_matches == 4) {
    for (it = hand.begin(); it != hand.end(); ) {
      if (it->name == _one || it->name == _two || it->name == _three || it->name == _four) {
	ptr_world->player_discard.push_back(*it);
	hand.erase(it++);
      }
      else
	it++;
    }
    ptr_world->disease_status[_did] = CURED; // CURED is a macro for 1.
    moves--;
    ptr_world->check_eradication(_did);
    // Finally check if this was the final cure needed to win the game.
    if (ptr_world->victory()) {
      exit(1);
    }
    return true;
  }
  else
    {
      std::cout << "Not all 4 cards matching the disease colour for the scientist-cure are in the hero's hand.\n";
      return false;
    }
}
