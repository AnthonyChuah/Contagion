// Implementation file for the Hero class.

#include "macros.h"

#include <iostream>
#include <string>
#include <vector>

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
  hero_id = _assign.hero_id;
  spec = _assign.spec;
  moves = _assign.moves;
}

std::string Hero::get_spec() { return spec; }

int Hero::get_heroid() { return hero_id; }

bool Hero::charter_flight(City& _to, Hero* _user)
{
  std::cout << "Calling Hero::charter_flight().\n";
  // _user specifies the person who provides cards/moves for this action.
  // This is ALWAYS the hero itself unless the hero has been dispatched
  // by someone else.
  if (_user == NULL) {
    _user = this;
  }
  std::vector<PCard>::iterator it;
  for (it = _user->hand.begin(); it != _user->hand.end(); it++) {
    if (it->city_id == ptr_city->city_id) {
      ptr_city->depart_hero(hero_id);
      ptr_city = &_to;
      ptr_city->arrive_hero(hero_id);
      _user->hand.erase(it);
      // If Medic and the disease is cured, the arrive_hero function in City will auto-disinfect blocks of that disease.
      _user->moves--;
      return true;
    }
  }
  return false;
}

bool Hero::direct_flight(City& _to, Hero* _user)
{
  std::cout << "Calling Hero::direct_flight().\n";
  if (_user == NULL) {
    _user = this;
  }
  std::vector<PCard>::iterator it;
  for (it = _user->hand.begin(); it != _user->hand.end(); it++) {
    if (it->city_id == _to.city_id) {
      ptr_city->depart_hero(hero_id); // First remove hero_id from the city's heroes.
      ptr_city = &_to; // Point hero's ptr_city to the new city.
      ptr_city->arrive_hero(hero_id); // Now add hero_id to the new city's heroes.
      _user->hand.erase(it);
      // ADD EXCEPTION: if hero is a Medic, and if a disease is cured, remove all of that disease from destination.
      _user->moves--;
      return true;
    }
  }
  return false;
}

bool Hero::shuttle_flight(City& _to, Hero* _user)
{
  std::cout << "Calling Hero::shuttle_flight().\n";
  if (_user == NULL) {
    _user = this;
  }
  if (ptr_city->has_rc()) {
    if (_to.has_rc()) {
      ptr_city->depart_hero(hero_id);
      ptr_city = &_to;
      ptr_city->arrive_hero(hero_id);
      _user->moves--;
      return true;
    }
  }
  return false;
}

bool Hero::move(City& _to, Hero* _user)
{
  std::cout << "Calling Hero::move().\n";
  if (_user == NULL) {
    _user = this;
  }
  // Override function for Medic so that city from/to which he moves lose all CURED diseases.
  int cid_to = _to.get_cityid();
  std::vector<int>::iterator it;
  for (it = ptr_city->neighbours.begin(); it != ptr_city->neighbours.end(); it++) {
    if (*it == cid_to) {
      ptr_city->depart_hero(hero_id);
      ptr_city = &_to;
      ptr_city->arrive_hero(hero_id);
      _user->moves--;
      std::cout << "Hero " << spec << " moved to " << _to.name << ".\n";
      return true;
    }
  }
  return false;
}

bool Hero::disinfect(int _did)
{
  std::cout << "Calling Hero::disinfect() on disease ID " << _did << ".\n";
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
    return true;
  }
  else
    return false;
}

bool Hero::build_centre(City& _city)
{
  // First check if the Hero is in the City.
  if (ptr_city->get_cityid() == _city.get_cityid()) {
    std::vector<PCard>::iterator it;
    if (ptr_world->centres_remaining > 0 && _city.has_rc() == false)
      {
	if (spec == "Operations Expert") {
	  _city.build_rc();
	  ptr_world->centres_remaining--;
	  moves--;
	  std::cout << "Built RC in " << _city.name << ".\n";
	  return true;
	}
	for (it = hand.begin(); it != hand.end(); it++) {
	  if (it->city_id == _city.city_id)
	    {
	      hand.erase(it);
	      _city.build_rc();
	      ptr_world->centres_remaining--;
	      moves--;
	      std::cout << "Built RC in " << _city.name << ".\n";
	      return true;
	    }
	}
      }
  }
  return false;
}

bool Hero::give_card(std::string _card, Hero& _to)
{
  std::vector<PCard>::iterator it;
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
  std::vector<PCard>::iterator it;
  if ((_card == ptr_city->name && _card == _from.ptr_city->name) || _from.spec == "Researcher")
    {
      for (it = _from.hand.begin(); it != _from.hand.end(); )
	{
	  if (it->name == _card)
	    {
	      hand.push_back(*it);
	      _from.hand.erase(it);
	      moves--;
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
  std::cout << "Calling Hero::cure() on disease ID " << _did << ".\n";
  if (spec == "Scientist") {
    std::cout << "Do not use the regular cure function, instead use the Scientist's overloaded cure.\n";
    return false;
  }
  // Player should be able to specify exactly which cards he wants to use.
  // First, verify that every card he wants to use exists in his hand.
  // Then, erase each card from his hand and CURE THE DISEASE!
  std::vector<PCard>::iterator it;
  int count_matches = 0;
  for (it = hand.begin(); it != hand.end(); it++)
    if (it->disease_id == _did &&
	(it->name == _one || it->name == _two || it->name == _three || it->name == _four || it->name == _five))
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
      // Final check: wherever Medic is, needs to be wiped of the cured disease.
      std::vector<Hero>::iterator it;
      int medic_id = -1;
      City* medic_city = NULL;
      for (it = ptr_world->heroes.begin(); it != ptr_world->heroes.end(); it++) {
	if (it->get_spec() == "Medic")
	  {
	    medic_id = it->get_heroid();
	    medic_city = it->ptr_city;
	  }
      }
      // If there is a medic in the game, remove all disease cubes of the cured colour in city medic is in.
      if (medic_id > -1) {
	int cubes_to_putback = medic_city->disease_counters[_did];
	medic_city->disease_counters[_did] = 0;
	ptr_world->disease_blocks[_did] += cubes_to_putback;
      }
      // Finally check if this was the final cure needed to win the game.
      if (ptr_world->victory()) {
	exit(1);
      }
      return true;
    }
  else
    {
      std::cout << "Not all 5 cards matching the disease colour for the cure are in the hero's hand.\n";
      return false;
    }
}

void Hero::start_turn()
{
  std::cout << "Hero::start_turn called.\n";
  moves = 4;
}

bool Hero::play_special_eventcard(std::string _arguments)
{
  std::cout << "Hero::play_special_eventcard is a purely virtual function. It should not have been possible to "
	    << "call this function. This should be called only as ContPlanner::play_special_eventcard.\n";
  exit(1);
}

bool Hero::get_special_eventcard(std::string _eventname)
{
  std::cout << "Hero::get_special_eventcard is a purely virtual function. It should not have been possible to "
	    << "call this function. This should be called only as ContPlanner::get_special_eventcard.\n";
  exit(1);
}

bool Hero::dispatch_control(int _hid, std::string _arguments)
{
  std::cout << "Hero::dispatch_control is a purely virtual function. It should not have been possible to "
	    << "call this function. This should be called only as Dispatcher::dispatch_control.\n";
  exit(1);
}

bool Hero::dispatch_move(int _hidfrom, int _hidto)
{
  std::cout << "Hero::dispatch_move is a purely virtual function. It should not have been possible to "
	    << "call this function. This should be called only as Dispatcher::dispatch_move.\n";
  exit(1);
}

bool Hero::opex_flight(City& _to, std::string _card)
{
  std::cout << "Hero::opex_flight is a purely virtual function. It should not have been possible to "
	    << "call this function. This should be called only as OpExpert::opex_flight.\n";
  exit(1);
}

bool Hero::scientist_cure(int _did, std::string _one, std::string _two, std::string _three, std::string _four)
{
  std::cout << "Hero::scientist_cure is a purely virtual function. It should not have been possible to "
	    << "call this function. This should be called only as Scientist::scientist_cure.\n";
  exit(1);
}
