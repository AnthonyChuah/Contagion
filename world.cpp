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
#include "contPlanner.h"
#include "Dispatcher.h"
#include "Medic.h"
#include "OpExpert.h"
#include "QSpecialist.h"
#include "Researcher.h"
#include "Scientist.h"
#include "world.h"

World::World()
{
  init(); // This is a private helper function to do the constructor.
  num_epidemics = 4; // By default, we set it to the easiest level of 4 epidemics. 6 is the hardest.
}

World::World(int epidemics)
{
  if (epidemics < 4)
    {
      std::cout << "You cannot have fewer than 4 epidemics: that would be too easy!\n";
      exit(1);
    }
  if (epidemics > 6)
    {
      std::cout << "I applaud your insanity, but you cannot have more than 6 epidemics: that would be too hard!\n";
      exit(1);
    }
  init();
  num_epidemics = epidemics;
}

void World::load_city_data(char _filename[])
{
  ifstream ins;
  ins.open(_filename);
  if (ins.fail())
    {
      std::cout << "Failed to open city input file.\n";
      exit(1);
    }
  string rowdata;
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
      vector<string> elems;
      while (getline(ss, item, ','))
        elems.push_back(item);

      // CityID,CityName,XCoordinate,YCoordinate,DiseaseID,Neighbours
      // 0,Atlanta,236,524,2,4:8:10
      // Call constructor for City object and push into back or front of vector<City> on World.
      string cityname;
      int cityid, did, xcoord, ycoord;
      bool has_rc = false; // Only Atlanta begins with a RC.
      cityid = std::stoi(elems[0]); cityname = elems[1];
      xcoord = std::stoi(elems[2]); ycoord = std::stoi(elems[3]);
      if (cityid == 0) has_rc = true;
      did = std::stoi(elems[4]);
      vector<int> cityneighbours;
      stringstream sss(elems[5]);
      string subitem;
      while (getline(sss, subitem, ':'))
	cityneighbours.push_back(subitem);
      City a_city(cityid,cityname,xcoord,ycoord,did,cityneighbours,this,has_rc);
      cities.push_back(a_city);

      // Call constructor for ICard and PCard and push them into respective vectors too.
      ICard an_icard(cityname,cityid);
      infection_deck.push_back(an_icard);
      PCard a_pcard(cityname,cityid,false,false);
      player_deck.push_back(a_pcard);
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
      if (rowdata.empty()) continue;
      // If string is not empty, record it directly in eventname.
      eventname = rowdata;
      // Call constructor for PCard and push onto the PCard vector.
      PCard a_pcard(rowdata,-1,true,false);
      player_deck.push_back(a_pcard);
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
      if (rowdata.empty()) continue;
      hero_spec = rowdata;
      // If string is not empty, record it directly in hero_spec then call constructor and push to heroes vector.
      // ALWAYS call load_hero_data AFTER load_city_data, because Hero needs a pointer to Atlanta at init.
      City* ptr_atlanta = &cities[0]; // Set City pointer to first city in World::cities.
      if (hero_spec == "Contingency Planner")
	ContPlanner a_hero(ptr_atlanta,this,hero_spec);
      else if (hero_spec == "Dispatcher")
	Dispatcher a_hero(ptr_atlanta,this,hero_spec);
      else if (hero_spec == "Medic")
	Medic a_hero(ptr_atlanta,this,hero_spec);
      else if (hero_spec == "Operations Expert")
	OpExpert a_hero(ptr_atlanta,this,hero_spec);
      else if (hero_spec == "Quarantine Specialist")
	QSpecialist a_hero(ptr_atlanta,this,hero_spec);
      else if (hero_spec == "Researcher")
	Researcher a_hero(ptr_atlanta,this,hero_spec);
      else if (hero_spec == "Scientist")
	Scientist a_hero(ptr_atlanta,this,hero_spec);
      // Hero a_hero = Hero(ptr_atlanta,this,hero_spec);
      heroes.push_back(a_hero);
    }
  ins.close();
  std::cout << "Heroes reading complete: please use debugger to inspect.\n";
}

void World::setup()
{
  // Do the steps according to the rules in the rulebook.
  // Check how many players there are and record this in World::num_players.
  num_players = heroes.size();
  num_cities = cities.size();
  if (num_players > 4) {std::cout << "You cannot have more than 4 players.\n"; exit(1)}
  else if (num_players < 2) {std::cout << "You cannot have fewer than 2 players.\n"; exit(1)}
  int starting_hand = 6 - num_players; // 4 for 2 players, 3 for 3 players, 2 for 4 players.
  // First shuffle the PCard deck. Make sure this includes event cards.
  std::random_shuffle(player_deck.begin(),player_deck.end()); // <algorithm>'s function shuffles cards.
  // Note: do not use draw_player_deck because that will perform 2 draws and discard cards above 7.
  for (int i = 0; i < num_players; i++)
    for (int j = 0; j < starting_hand; j++)
      {
	heroes[i].hand.push_back(player_deck.back());
	player_deck.pop_back();
      }
  // Now the players' cards are dealt. Add epidemic cards to player_deck and shuffle again.
  for (int i = 0; i < num_epidemics; i++)
    {
      PCard an_epidemic("Epidemic",-1,false,true);
      player_deck.push_back(an_epidemic);
    }
  std::random_shuffle(player_deck.begin(),player_deck.end());
  // NOTE: this algorithm can lead to concentrations of epidemics, which is not good.
  // TO UPDATE: follow the rules and split into N piles and insert the N epidemics into each and shuffle each,
  // then put them back together.
  // Now shuffle the infection deck and begin infecting cities.
  std::random_shuffle(infection_deck.begin(),infection_deck.end());
  // First 3 cities get 3 cubes each. Next 3 get 2, next 3 get 1.
  for (int i = 3; i > 0; i--)
    for (int j = 0; j < 3; j++)
      {
	ICard chosen_card = infection_deck.back();
	infection_deck.pop_back();
	int cid_to_infect = chosen_card.city_id;
	cities[cid_to_infect].infect(cities[cid_to_infect].get_disease_id(), i);
	infection_discard.push_back(chosen_card);
      }
  // Now determine whose turn it is. Technically the rules require it's player with highest pop city in hand.
  players_turn = 0;
}

void World::render_world_ascii()
{
  // We do not yet know how exactly we will render the world in ASCII.
}

void World::render_world_gui()
{
  // We do not yet know how exactly we will render the world graphically.
}

void World::draw_infection_deck()
{
  // Pop off the front or back of the infection deck. Read city ID. Call the infection function accordingly.
  int ncards = calculate_infection_rate();
  for (int i = 0; i < ncards; n++)
    {
      ICard chosen_card = infection_deck.back();
      infection_deck.pop_back();
      int cid_to_infect = chosen_card.city_id;
      cities[cid_to_infect].infect(cities[cid_to_infect].get_disease_id(), 1);
      infection_discard.push_back(chosen_card);
    }
}

int World::calculate_infection_rate()
{
  if (infection_rate_base <= 2) return 2;
  else if (infection_rate_base >= 3 && infection_rate_base <= 4) return 3;
  else return 4;
}

void World::epidemic()
{
  infection_rate_base++;
  int infection_rate = calculate_infection_rate();
  int cid_target = infection_deck.front().city_id;
  infection_discard.push_back(infection_deck.front());
  infection_deck.pop_front();
  cities[cid_target].infect(cities[cid_target].get_disease_id(), 3);
  std::random_shuffle(infection_discard.begin(), infection_discard.end());
  while (infection_discard.size > 0)
    {
      infection_deck.push_back(infection_discard.back());
      infection_discard.pop_back();
    }
}

void World::play_event_card(Hero& hero)
{
  // Use iterator to find the relevant card in the player's hand, then pop it, then make the event happen.
}

void World::init()
{
  centres_remaining = 5;
  outbreaks = 0;
  infection_rate_base = 0;
  for (int i = 0; i < 4; i++)
    {
      disease_status[i] = UNCURED; // UNCURED is defined to be 0 by preprocessor directive.
      disease_blocks[i] = 24;
    }
  num_epidemics = 0;
}
