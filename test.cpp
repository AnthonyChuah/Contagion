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

int main() {
  cout << "Testing the Contagion game logic with a text UI!\n";
  cout << "First, construct the World.\n";
  cout << "How many epidemics do you want? 4 for easy, 5 for medium, 6 for hard.\n";
  int number_of_epidemics;
  cin >> number_of_epidemics;
  World new_world(number_of_epidemics);
  cout << "I have just called the Constructor with your specified number of epidemics.\n";
  new_world.render_world_ascii();
  cout << "Happy with what you see? Enter anything to continue:\n";
  char dummy;
  cin >> dummy;

  cout << "Now I will load the city data into the World.\n";
  new_world.load_hero_data("heroes.dat");
  cout << "And then I will load the event cards data.\n";
  new_world.load_eventcards_data("eventcards.dat");
  cout << "Then I load the heroes data.\n";
  new_world.load_hero_data("heroes.dat");
  cout << "Then I run the Setup for the world.\n";
  new_world.setup();
  cout << "Now you may inspect the world again. Do you like it?\n";
  new_world.render_world.ascii();
  cout << "Happy with what you see? Enter anything to continue:\n";
  cin >> dummy;
}
