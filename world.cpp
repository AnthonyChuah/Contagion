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
      cout << "Failed to open input file.\n";
      exit(1);
    }
  // Code to be filled in for loading city data from 
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
