// Implementation file for the Medic class

#include <iostream>
#include <cmath>
#include <string>
#include <list>

#include "hero.h"

Hero::Hero() : ptr_city(NULL), ptr_world(NULL), hero_id(-1), spec("Empty Hero Constructor")
{
}

Hero::Hero(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  ptr_city(_ptr_city), ptr_world(_ptr_world), hero_id(_hid), spec(_spec)
{
}

Hero::Hero(const Hero& _copy)
{
  ptr_city = _copy.ptr_city;
  ptr_world = _copy.ptr_world;
  hero_id = _copy.hero_id;
  spec = _copy.spec;
}

Hero& Hero::operator =(const Hero& _assign)
{
  ptr_city = _assign.ptr_city;
  ptr_world = _assign.ptr_world;
  hero_id = _copy.hero_id;
  spec = _assign.spec;
}

bool Hero::charter_flight(City& _to)
{
  std::list<PCard>::iterator it;
  for (it = hand.begin(); it != hand.end(); it++) {
    if (it->city_id == ptr_city->city_id) {
      ptr_city->depart_hero(hero_id);
      ptr_city = &_to;
      ptr_city->arrive_hero(hero_id);
      hand.erase(it);
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
      return true;
    }
  }
  return false;
}

bool Hero::move(City& _to)
{
  int cid_to = _to.city_id;
  std::vector<int>::iterator it;
  for (it = ptr_city->neighbours.begin(); it != ptr_city->neighbours.end(); it++) {
    if (it == cid_to) {
      ptr_city->depart_hero(hero_id);
      ptr_city = &_to;
      ptr_city->arrive_hero(hero_id);
      return true;
    }
  }
  return false;
}

void Hero::disinfect(int d_id) {
  if(ptr_city->disease_counters[d_id] > 0)
    ptr_city->disease_counters[d_id]--;   
}



/* -- Build centre: adds a research centre to the city specified.          -- */
void Hero::build_centre(City& city) {
  std::list<PCard>::iterator it; //list iterator

  // If remaining centres, and no centre exists in the city
  if(ptr_world->centres_remaining>0 && city.research_centre==false) {
    //Check if a city in hand matches city to build in
    for(it=hand.begin(); it!=hand.end(); it++) {
      if(it->city_id==city.city_id) {
	hand.erase(it); //remove the card from hand
	city.research_centre==true;
	ptr_world->centres_remaining--;
        break;
      }
    }
    cout<<"Unable to build a research centre, as no matching card!" << endl;
  }
  else {
    cout<<"Unable to build a research centre (existing centre in the city or no "; 
    cout<< "centres remaining)!" << endl;
    // NOTE: SHOULD TECHNICALLY ALLOW FOR MOVING CENTRES FROM THE BOARD!
  }
}



/* -- Cure: if five cards of same colour in hand, cure that disease.       -- */
void Hero::cure(int disease_id) {
  //std::list<PCard>::iterator it; //list iterator

  //for(it=hand.begin(); it!=hand.end(); it++) {
    //for(  //for all cities with d_id==disease_id ?
    //if(it->city_id==ptr_city->city_id) {
	  //}  
  cout<<"STUB - add the 'cure' functionality." << endl;
}
