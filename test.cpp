/* Test file for World class. */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "macros.h"
#include "pcard.h"
#include "icard.h"
#include "city.h"
#include "hero.h"
#include "world.h"

#include "contplanner.h"
#include "dispatcher.h"
#include "medic.h"
#include "opexpert.h"
#include "qspecialist.h"
#include "researcher.h"
#include "scientist.h"

int main()
{
  std::cout << "Testing the Contagion game logic with a text UI!\n";
  std::cout << "First, construct the World.\n";
  std::cout << "How many epidemics do you want? 4 for easy, 5 for medium, 6 for hard.\n";
  int number_of_epidemics;
  std::cin >> number_of_epidemics;
  World new_world(number_of_epidemics);
  std::cout << "I have just called the Constructor with " << number_of_epidemics << " epidemics.\n";

  std::cout << "Now I will load the city data into the World.\n";
  new_world.load_city_data("cities.dat");
  std::cout << "And then I will load the event cards data.\n";
  new_world.load_eventcards_data("eventcards.dat");
  std::cout << "Then I load the heroes data.\n";
  new_world.load_hero_data("heroes.dat");
  std::cout << "Then I run the Setup for the world.\n";
  new_world.setup();
  new_world.render_world_ascii();

  std::cout << "Starting the main game loop.\n";
  new_world.game_loop();
  
  return 0;
}
