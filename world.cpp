/*
Implementation file for the World class.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

#include "pcard.h"
#include "icard.h"
#include "city.h"
#include "hero.h"
// Include Jukka's specializations header file.
#include "world.h"

World::World()
{
  init(); // This is a private helper function to do the constructor.
}

World::World(int epidemics)
{
  init();
  num_epidemics = epidemics;
}

void World::load_city_data(char filename[])
{
  ifstream ins;
  ins.open(filename);
  if (ins.fail())
    {
      std::cout << "Failed to open city input file.\n";
      exit(1);
    }
  string rowdata;
  vector<int> cityneighbours;
  string cityname;
  int city_id, d_id, x_coord, y_coord;
  // First line of data file is just headers, drop them.
  getline(ins, rowdata);
  while(ins.good())
    {
      std::cout << "DEBUG: reading row data.\n";
      getline(ins, rowdata);
      // If rowdata is simply empty (last line) then continue.
      if (rowdata.empty()) continue;
      // Split by comma delimiter to get data, split neighbours by colon delimiter.
      stringstream ss(rowdata);
      string item;
      vector<string> inline_elements;
      while (getline(ss, item, ','))
	inline_elements.push_back(item);
      // Call constructor for City object and push into back or front of vector<City> on World.
      // Call constructor for ICard and PCard and push them into respective vectors too.
    }
  ins.close();
  std::cout << "City reading complete: please use GDB to inspect the 3 vectors and make sure they're correct.\n";
  // Remember to inspect the vectors.
}

void World::load_eventcards_data(char filename[])
{
  ifstream ins;
  ins.open(filename);
  if (ins.fail())
    {
      std::cout << "Failed to open event cards input file.\n";
      exit(1);
    }
  string rowdata;
  string eventname;
  while (ins.good())
    {
      std::cout << "DEBUG: reading event row data.\n";
      getline(ins, rowdata);
      // rowdata should simply be the event name, unless it read a blank row (end of file).
      // If string is not empty, record it directly in eventname.
      // Call constructor for PCard and push onto the PCard vector.
    }
  ins.close();
  std::cout << "Event card reading complete: please use debugger to inspect.\n";
  // Remember to inspect the vector.
}

void World::load_hero_data(char filename[]);
{
  ifstream ins;
  ins.open(filename);
  if (ins.fail())
    {
      std::cout << "Failed to open heroes input file.\n";
      exit(1);
    }
  string rowdata;
  string hero_spec;
  while (ins.good())
    {
      std::cout << "DEBUG: reading hero row data.\n";
      getline(ins, rowdata);
      // rowdata should simply be the hero's specialization, unless it is just a blank.
      // If string is not empty, record it directly in hero_spec then call constructor and push to heroes vector.
    }
  ins.close();
  std::cout << "Heroes reading complete: please use debugger to inspect.\n";
}

void World::setup()
{
  // Do the steps according to the rules in the rulebook.
}

void World::render_world_ascii()
{
  // We do not yet know how exactly we will render the world in ASCII.
}

void World::render_world_gui()
{
  // We do not yet know how exactly we will render the world graphically.
}

void World::shuffle_deck(vector<PCard>& deck)
{
  // Call random_shuffle on the vector of PCards.
}

void World::shuffle_deck(vector<ICard>& deck)
{
  // Call random_shuffle on the vector of ICards. Needs overloading due to different input type.
}

void World::draw_infection_deck()
{
  // Pop off the front or back of the infection deck. Read city ID. Call the city's infection function accordingly.
}

void World::init()
{
  centres_remaining = 5;
  outbreaks = 0;
  infection_rate_base = 0;
  for (int i = 0; i < 4; i++)
    {
      disease_status[i] = 0;
      disease_blocks[i] = 24;
    }
  num_epidemics = 0;
}
