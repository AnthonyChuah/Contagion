/*
Implementation file for the City class.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

#include "macros.h"
#include "city.h"
#include "world.h"
#include "hero.h"
#include "pcard.h"
#include "icard.h"

#include "contplanner.h"
#include "dispatcher.h"
#include "medic.h"
#include "opexpert.h"
#include "qspecialist.h"
#include "researcher.h"
#include "scientist.h"

City::City() : city_id(-1), name("Empty City Constructor"), disease_id(-1), x_coord(-1), y_coord(-1),
	       world_ptr(NULL), research_centre(false), skip_next_infect_cities(false)
{
  shortname = "Nul";
  for (int i = 0; i < 4; i++)
    disease_counters[i] = 0;
}

City::City(int _id, std::string _name, int _did, int _xcoord, int _ycoord, const std::vector<int>& _neighbour, World* _worldptr, bool _research_centre) :
  city_id(_id), name(_name), disease_id(_did), x_coord(_xcoord), y_coord(_ycoord), world_ptr(_worldptr),
  research_centre(_research_centre), skip_next_infect_cities(false)
{
  std::string substring = _name.substr(0, 4);
  substring = substring.c_str();
  std::strncpy(shortname, substring, 4);
  neighbours = _neighbour;
}

City::City(const City& _copy_from)
{
  city_id = _copy_from.city_id;
  name = _copy_from.name;
  disease_id = _copy_from.disease_id;
  x_coord = _copy_from.x_coord;
  y_coord = _copy_from.y_coord;
  world_ptr = _copy_from.world_ptr;
  research_centre = _copy_from.research_centre;
  skip_next_infect_cities = _copy_from.skip_next_infect_cities;
  neighbours = _copy_from.neighbours;
  heroes = _copy_from.heroes;
  shortname = _copy_from.shortname;
  for (int i = 0; i < 4; i++) {
    disease_counters[i] = _copy_from.disease_counters[i];
    shortname[i] = _copy_from.shortname[i];
  }
}

City& City::operator =(const City& _assign_from)
{
  city_id = _assign_from.city_id;
  name = _assign_from.name;
  disease_id = _assign_from.disease_id;
  x_coord = _assign_from.x_coord;
  y_coord = _assign_from.y_coord;
  world_ptr = _assign_from.world_ptr;
  research_centre = _assign_from.research_centre;
  skip_next_infect_cities = _assign_from.skip_next_infect_cities;
  neighbours = _assign_from.neighbours;
  heroes = _assign_from.heroes;
  shortname = _assign_from.shortname;
  for (int i = 0; i < 4; i++) {
    disease_counters[i] = _assign_from.disease_counters[i];
    shortname[i] = _assign_from.shortname[i];
  }
}

void City::outbreak(int _did)
{
  // This triggers if you attempt to add a cube to a city which already has 3 cubes of that colour.
  // For each neighbour of this city, add a cube of THIS CITY'S disease_id to the neighbour.
  // Neighbours is a vector that has random access iterators, so I'm going to be lazy and not use an iterator:
  world_ptr->outbreaks++;
  for (int i = 0; i < neighbours.size(); i++) {
    // Use World pointer to access the neighbouring City, and call that City's infect() function.
    world_ptr->cities[neighbours[i]].infect(_did, 1);
  }
}

void City::infect(int _did, int _numcubes)
{
  // Add a check for whether Quarantine Specialist is in this city or any neighbouring city. If yes, return.
  for (int i = 0; i < _numcubes; i++)
    {
      if (disease_counters[_did] == 3) {
	outbreak(_did);
	return;
      }
      else {
	if (world_ptr->disease_blocks[_did] == 0)
	  world_ptr->death("Lost game because you ran out of disease blocks on the board.\n");
	else {
	  world_ptr->disease_blocks[_did]--;
	  disease_counters[_did]++;
	}
      }
    }
}

bool City::has_rc() { return research_centre; }

// Normally the Hero will build this and Hero has a pointer to the City,
// so strictly speaking you do not need this setter function. But whatever, pretty code.
void City::build_rc() { research_centre = true; }

int City::get_disease_id() { return disease_id; }

int City::get_ncubes(int _did) { return disease_counters[_did]; }

void City::arrive_hero(int _hid) { heroes.push_back(_hid); }

bool City::depart_hero(int _hid)
{
  std::vector<int>::iterator iter = std::find(heroes.begin(), heroes.end(), _hid);
  if (iter != heroes.end()) {
    int index_to_delete = iter - heroes.begin();
    heroes.erase(heroes.begin() + index_to_delete);
    return true;
  }
  return false;
}
