// Implementation file for the Hero class.

#include <iostream>
#include <string>
#include <list>

#include "macros.h"
#include "pcard.h"
#include "icard.h"
#include "city.h"
#include "hero.h"
#include "world.h"

Hero::Hero() : ptr_city(NULL), ptr_world(NULL), hero_id(-1), spec("Empty Hero Constructor"), moves(-1)
{}

Hero::Hero(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  ptr_city(_ptr_city), ptr_world(_ptr_world), hero_id(_hid), spec(_spec), moves(0)
{}

Hero::Hero(const Hero& _copy)
{
  ptr_city = _copy.ptr_city;
  ptr_world = _copy.ptr_world;
  hero_id = _copy.hero_id;
  spec = _copy.spec;
  moves = _copy.moves;
}

Hero& Hero::operator =(const Hero& _assign)
{
  ptr_city = _assign.ptr_city;
  ptr_world = _assign.ptr_world;
  hero_id = _copy.hero_id;
  spec = _assign.spec;
  moves = _copy.moves;
}

std::string Hero::get_spec() { return spec; }

bool Hero::charter_flight(City& _to)
{
  std::list<PCard>::iterator it;
  for (it = hand.begin(); it != hand.end(); it++) {
    if (it->city_id == ptr_city->city_id) {
      ptr_city->depart_hero(hero_id);
      ptr_city = &_to;
      ptr_city->arrive_hero(hero_id);
      hand.erase(it);
      moves--;
      check_end();
      return true;
    }
  }
  return false;
}

bool Hero::direct_flight(City& _to)
{
  std::list<PCard>::iterator it;
  for (it = hand.begin(); it != hand.end(); it++) {
    if (it->city_id == _to.city_id) {
      ptr_city->depart_hero(hero_id); // First remove hero_id from the city's heroes.
      ptr_city = &_to; // Point hero's ptr_city to the new city.
      ptr_city->arrive_hero(hero_id); // Now add hero_id to the new city's heroes.
      hand.erase(it);
      moves--;
      check_end();
      return true;
    }
  }
  return false;
}

bool Hero::move(City& _to)
{
  // Override function for Medic so that city from/to which he moves lose all CURED diseases.
  int cid_to = _to.city_id;
  std::vector<int>::iterator it;
  for (it = ptr_city->neighbours.begin(); it != ptr_city->neighbours.end(); it++) {
    if (it == cid_to) {
      ptr_city->depart_hero(hero_id);
      ptr_city = &_to;
      ptr_city->arrive_hero(hero_id);
      moves--;
      check_end();
      return true;
    }
  }
  return false;
}

bool Hero::disinfect(int _did)
{
  int existing_cubes = ptr_city->disease_counters[_did];
  if (ptr_city->disease_counters[_did] > 0) {
    // If Medic, set to 0. If disease cured, set to 0. Else, decrement by 1.
    if (spec == "Medic") {
      ptr_city->disease_counters[_did] = 0;
      ptr_world->disease_blocks[_did] += existing_cubes;
    }
    else if (ptr_world->disease_status[_did] >= CURED) {
      ptr_city->disease_counters[_did] = 0;
      ptr_world->disease_blocks[_did] += existing_cubes;
    }
    else {
      ptr_city->disease_counters[_did]--;
      ptr_world->disease_blocks[_did]++;
    }
    moves--;
    ptr_world->check_eradication(_did);
    check_end();
    return true;
  }
  else
    return false;
}

bool Hero::build_centre(City& _city)
{
  std::list<PCard>::iterator it;
  if (ptr_world->centres_remaining > 0 && _city->has_rc() == false)
    {
      if (spec == "Operations Expert") {
	_city.build_rc();
	ptr_world->centres_remaining--;
	moves--;
	check_end();
	return true;
      }
      for (it = hand.begin(); it != hand.end(); it++) {
	if (it->city_id == _city.city_id)
	  {
	    hand.erase(it);
	    _city.build_rc();
	    ptr_world->centres_remaining--;
	    moves--;
	    check_end();
	    return true;
	  }
      }
    }
  return false;
}

bool Hero::give_card(std::string _card, Hero& _to)
{
  std::list<PCard>::iterator it;
  // If the _card string matches the name of the city that hero is currently in and the receiver is also there:
  if ((_card == ptr_city->name && _card == _to.ptr_city->name) || spec == "Researcher")
    {
      // Search for the card that you would like to give.
      for (it = hand.begin(); it != hand.end(); ) {
	if (it->name == _card) {
	  _to.hand.push_back(*it); // Dereference iterator to get the object to push onto the receiver's hand.
	  hand.erase(it++); // Subtle note: I cannot delete the element before incrementing. Super clever.
	  moves--;
	  return true;
	}
	else
	  it++;
      }
    }
  else
    std::cout << "City name does not match the card's name.\n";
  return false;
}

bool Hero::take_card(std::string _card, Hero& _from)
{
  std::list<PCard>::iterator it;
  if ((_card == ptr_city->name && _card == _from.ptr_city->name) || _from.spec == "Researcher")
    {
      for (it = _from.hand.begin(); it != _from.hand.end(); )
	{
	  if (it->name == _card)
	    {
	      hand.push_back(*it);
	      _from.hand.erase(it);
	      moves--;
	      check_end();
	      return true;
	    }
	  else
	    it++;
	}
    }
  return false;
}

bool Hero::cure(int _did, std::string _one, std::string _two, std::string _three, std::string _four, std::string _five)
{
  // Scientist should have an overloaded function with 4 inputs only.
  // Player should be able to specify exactly which cards he wants to use.
  // First, verify that every card he wants to use exists in his hand.
  // Then, erase each card from his hand and CURE THE DISEASE!
  std::list<PCard>::iterator it;
  int count_matches = 0;
  for (it = hand.begin(); it != hand.end(); it++)
    if (it->name == _one || it->name == _two || it->name == _three || it->name == _four || it->name == _five)
      count_matches++;
  if (count_matches == 5)
    {
      for (it = hand.begin(); it != hand.end(); ) {
	if (it->name == _one || it->name == _two || it->name == _three || it->name == _four || it->name == _five)
	  {
	    ptr_world->player_discard.push_back(*it);
	    hand.erase(it++);
	  }
	else
	  it++;
      }
      ptr_world->disease_status[_did] = CURED; // CURED is a macro for 1.
      moves--;
      ptr_world->check_eradication(_did);
      check_end();
      return true;
    }
  else
    {
      std::cout << "Not all 5 cards for the cure are in the hero's hand.\n";
      return false;
    }
}

bool Hero::check_end()
{
  if (moves <= 0)
    {
      moves = 0;
      ptr_world->draw_player_deck(*this); // Deals player cards to this hero.
      ptr_world->draw_infection_deck();
      // Now switch to next hero's turn.
      int next_hid = (hero_id+1) % ptr_world->heroes.size();
      ptr_world->players_turn = next_hid;
      ptr_world->heroes[next_hid].start_turn();
      return true;
    }
  else
    return false;
}

void Hero::start_turn() { moves = 4; }
