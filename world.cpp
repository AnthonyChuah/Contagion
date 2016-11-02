/*
Implementation file for the World class.
*/

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <string>
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

World::World()
{
  init(); // This is a private helper function to do the constructor.
  num_epidemics = 4; // By default, we set it to the easiest level of 4 epidemics. 6 is the hardest.
}

World::World(int _epidemics)
{
  if (_epidemics < 4) {
    std::cout << "You cannot have fewer than 4 epidemics: that would be too easy!\n";
    exit(1);
  }
  if (_epidemics > 6) {
    std::cout << "I applaud your insanity, but you cannot have more than 6 epidemics: that would be too hard!\n";
    exit(1);
  }
  init();
  num_epidemics = _epidemics;
}

void World::load_city_data(std::string _filename)
{
  std::ifstream ins;
  ins.open(_filename);
  if (ins.fail()) {
    std::cout << "Failed to open city input file.\n";
    exit(1);
  }
  std::string rowdata;
  // First line of data file is just headers, drop them.
  std::getline(ins, rowdata);
  while(ins.good()) {
    std::cout << "DEBUG: reading row data.\n";
    std::getline(ins, rowdata);
    // If rowdata is simply empty (last line) then continue.
    if (rowdata.empty()) continue;
    
    // Split by comma delimiter to get data, split neighbours by colon delimiter.
    std::stringstream ss(rowdata);
    std::string item;
    std::vector<string> elems;
    while (std::getline(ss, item, ','))
      elems.push_back(item);
    
    // CityID,CityName,XCoordinate,YCoordinate,DiseaseID,Neighbours
    // 0,Atlanta,0.196666666666667,0.617196702002356,2,4:8:10
    // Call constructor for City object and push into back or front of vector<City> on World.
    std::string cityname;
    int cityid, did;
    double xcoord, ycoord;
    bool has_rc = false; // Only Atlanta begins with a RC.
    cityid = std::stoi(elems[0]); cityname = elems[1];
    xcoord = std::atof(elems[2]); ycoord = std::atof(elems[3]);
    if (cityid == 0) has_rc = true;
    did = std::stoi(elems[4]);
    std::vector<int> cityneighbours;
    std::stringstream sss(elems[5]);
    std::string subitem;
    while (std::getline(sss, subitem, ':'))
      cityneighbours.push_back(subitem);
    City a_city(cityid,cityname,did,xcoord,ycoord,cityneighbours,this,has_rc);
    cities.push_back(a_city);
    
    // Call constructor for ICard and PCard and push them into respective vectors too.
    ICard an_icard(cityname,cityid);
    infection_deck.push_back(an_icard);
    PCard a_pcard(cityname,cityid,did,false,false);
    player_deck.push_back(a_pcard);
  }
  ins.close();
  std::cout << "City reading complete: please use GDB to inspect the 3 vectors and make sure they're correct.\n";
  // Remember to inspect the vectors.
}

void World::load_eventcards_data(std::string _filename)
{
  std::ifstream ins;
  ins.open(_filename);
  if (ins.fail()) {
    std::cout << "Failed to open event cards input file.\n";
    exit(1);
  }
  std::string rowdata;
  std::string eventname;
  while (ins.good()) {
    std::cout << "DEBUG: reading event row data.\n";
    std::getline(ins, rowdata);
    // rowdata should simply be the event name, unless it read a blank row (end of file).
    if (rowdata.empty()) continue;
    // If string is not empty, record it directly in eventname.
    eventname = rowdata;
    // Call constructor for PCard and push onto the PCard vector.
    PCard a_pcard(rowdata,-1,-1,true,false);
    player_deck.push_back(a_pcard);
  }
  ins.close();
  std::cout << "Event card reading complete: please use debugger to inspect.\n";
  // Remember to inspect the vector.
}

void World::load_hero_data(std::string _filename);
{
  std::ifstream ins;
  ins.open(_filename);
  if (ins.fail()) {
    std::cout << "Failed to open heroes input file.\n";
    exit(1);
  }
  std::string rowdata;
  std::string hero_spec;
  while (ins.good()) {
    std::cout << "DEBUG: reading hero row data.\n";
    std::getline(ins, rowdata);
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
    for (int j = 0; j < starting_hand; j++) {
      heroes[i].hand.push_back(player_deck.back());
      player_deck.pop_back();
    }
  // Now the players' cards are dealt. Add epidemic cards to player_deck and shuffle again.
  for (int i = 0; i < num_epidemics; i++) {
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
  heroes[players_turn].start_turn(); // Set this player's moves to 4.
}

void World::render_world_ascii(ofstream& outs, int width, int height)
{
  // We do not yet know how exactly we will render the world in ASCII.
  // Default width 180 characters, height 60 characters.
  char map[width][height]; // 2d character array represents the map.
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      map[i][j] = 0;
  for (int i = 0; i < cities.size(); i++) {
    // Get city's x and y coordinates.
    int x_position = cities[i].x_coord * width; // Should add code to make sure it rounds off instead of truncates.
    int y_position = cities[i].y_coord * height;
    map[x_position][y_position] = '*';
    for (int j = 0; j < 4; j++)
      map[x_position+1+j][y_position] = cities[i].shortname[j];
    if (cities[i].has_rc())
      map[x_position][y_position+1] = 'R';
    for (int j = 0; j < 4; j++)
      map[x_position+1+j][y_position+1] = cities[i].get_ncubes(j);
    map[x_position][y_position+2] = cities[i].get_disease_id();
  }
  // Output the map.
  for (int j = 0; j < height; j++)
    for (int i = 0; i < width; i++) {
      std::cout << map[i][j];
      if (i == width-1) {
	std::cout << "\n";
      }
    }
  // Output the disease statuses.
  for (int k = 0; k < 4; k++) {
    std::cout << "Disease " << k << " status: " << disease_status[k] << "  ";
  }
  std::cout << "\n";
  for (int k = 0; k < 4; k++) {
    std::cout << "Disease " << k << " cubes: " << disease_status[k] << "  ";
  }
  std::cout << "\n";
  std::cout << "Infection deck: " << infection_deck.size() << " cards. ";
  std::cout << "Infection discards: " << infection_discard.size() << " cards.\n";
  std::cout << "Player deck: " << player_deck.size() << " cards. ";
  std::cout << "Player discards: " << player_discard.size() << " cards.\n";
  std::cout << "Infection rate: " << calculate_infection_rate() << "\n";
  std::cout << "Player turn: Player " << players_turn << " of " << num_players+1 << " total players.\n";
}

void World::render_world_gui()
{
  // We do not yet know how exactly we will render the world graphically.
}

void World::draw_infection_deck()
{
  // If One Quiet Night event card has been played, do nothing and set skip_next_infect_cities back to false.
  if (skip_next_infect_cities)
    {
      std::cout << "The One Quiet Night event card has saved you from this round of infection.\n";
      skip_next_infect_cities = false;
      return;
    }
  else
    {
      std::cout << "Commencing the infect cities process.\n";
      // Pop off the front or back of the infection deck. Read city ID. Call the infection function accordingly.
      for (int i = 0; i < calculate_infection_rate(); n++)
	{
	  ICard chosen_card = infection_deck.back();
	  infection_deck.pop_back();
	  int cid_to_infect = chosen_card.city_id;
	  cities[cid_to_infect].infect(cities[cid_to_infect].get_disease_id(), 1);
	  infection_discard.push_back(chosen_card);
	}
    }
}

void World::draw_player_deck(Hero& hero)
{
  for (int i = 0; i < 2; i++)
    {
      PCard chosen_card = player_deck.back();
      player_deck.pop_back();
      std::cout << "Player " << players_turn << " has drawn card: " << chosen_card.name << "\n";
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
  std::cout << "Epidemic!\n";
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

bool World::play_event_card(Hero& _hero, std::string _event, std::string _arguments)
{
  // Use iterator to find the relevant card in the player's hand, then pop it, then make the event happen.
  if (_event == "Government Grant")
    {
      // Check that hero's hand contains that card.
      PCard govgrant("Government Grant", -1, true, false);
      std::list<PCard>::iterator iter = std::find(_hero.hand.begin(), _hero.hand.end(), govgrant);
      if (iter != _hero.hand.end())
	{
	  // Call event_grant function: if it returns true, it's worked, so return true here too.
	  if (event_grant(_arguments))
	    {
	      int index_to_delete = iter - _hero.hand.begin();
	      _hero.hand.erase(_hero.hand.begin() + index_to_delete);
	      return true;
	    }
	  else
	    return false;
	}
      else
	{
	  std::cout << "No Government Grant event card in that hero's hand.\n";
	  return false;
	}
    }
  else if (_event == "One Quiet Night")
    {
      if (skip_next_infect_cities)
	{
	  std::cout << "We are already skipping the next infect cities.\n";
	  return false;
	}
      else
	skip_next_infect_cities = true;
    }
  else if (_event == "Forecast")
    {
      PCard forecast("Forecast", -1, true, false);
      std::list<PCard>::iterator iter = std::find(_hero.hand.begin(), _hero.hand.end(), forecast);
      if (iter != _hero.hand.end())
	{
	  event_forecast(); // INTERACTIVE function, tricky to program.
	  int index_to_delete = iter - _hero.hand.begin();
	  _hero.hand.erase(_hero.hand.begin() + index_to_delete);
	  return true;
	}
      else
	{
	  std::cout << "No Forecast event card in that hero's hand.\n";
	  return false;
	}
    }
  else if (_event == "Resilient Population")
    {
      PCard resilpop("Resilient Population", -1, true, false);
      std::list<PCard>::iterator iter = std::find(_hero.hand.begin(), _hero.hand.end(), resilpop);
      /* std::string string_name = _event;
	 iter = std::find_if(infection_discard.begin(), infection_discard.end(),
	 [&string_name] (const PCard& obj) {return obj.name == string_name}); 
	 This code above does something very smart: it passes a lambda (like R's anon functions) into find_if that
	 can find the iterator matching Resilient Population. You MUST use C++11 to use lambdas.
	 But it's easier at the moment to use std::find() since I have an overloaded == operator for PCard.
      */
      if (iter != _hero.hand.end())
	{
	  if (event_resilient(_arguments))
	    {
	      int index_to_delete = iter - _hero.hand.begin();
	      _hero.hand.erase(_hero.hand.begin() + index_to_delete);
	      return true;
	    }
	  else
	    return false;
	}
      else
	{
	  std::cout << "No Resilient Population event card in that hero's hand.\n";
	  return false;
	}
    }
  else if (_event == "Airlift")
    {
      // Arguments should look like this: 0:0 means move hero 0 to Atlanta, which is city_id 0.
      PCard airlift("Airlift", -1, true, false);
      std::list<PCard>::iterator iter = std::find(_hero.hand.begin(), _hero.hand.end(), airlift);
      if (iter != _hero.hand.end())
	{
	  int index_to_delete = iter - _hero.hand.begin();
	  _hero.hand.erase(_hero.hand.begin() + index_to_delete);
	  event_airlift(_arguments);
	  return true;
	}
      else
	return false;
    }
  else
    {
      std::cout << "Event is not recognized.";
      return false;
    }
}

bool World::event_grant(std::string _arguments)
{
  int cid = std::stoi(_arguments);
  // Now get the city in question from the cities vector.
  if (cities[cid].has_rc())
    {
      std::cout << "City already has a research centre.\n";
      return false;
    }
  else
    {
      cities[cid].build_rc();
      return true;
    }
}

void World::event_forecast()
{
  // Plan: make a GUI class that has an association link to World class. World will soon contain a pointer to GUI.
  std::vector<ICard> to_display;
  int decksize = min(infection_deck.size(), 6);
  for (int i = 0; i < decksize; i++)
    to_display.push_back(infection_deck[infection_deck.size()-decksize+i]);
  // Above code concisely expresses the different treatment if the deck contained less than 6 cards.

  display_deck(to_display); // This might stream data to the GUI once we build the GUI.
  std::vector<int> rearrange_mapping;
  intarray_input(rearrange_mapping, decksize); // e.g. 0 1 2 3 4 5 would be the original arrangement.

  // Using the arrangement given by players, make an arranged sub-deck.
  std::vector<ICard> arranged_subdeck = to_display; // vector<Template> overloads assignment. ICard MUST have too!
  for (int i = 0; i < decksize; i++)
    arranged_subdeck[i] = to_display[rearrange_mapping[i]]; // e.g. 3 1 2 0 4 5 would swap [0] and [3].

  // Copy the arranged subdeck into the top 6 cards of the infection_deck double-ended queue.
  for (int i = 0; i < decksize; i++)
    infection_deck[infection_deck.size()-decksize+i] = arranged_subdeck[i];
}

bool World::event_resilient(std::string _arguments)
{
  // Arguments should be a number referring to the city_id.
  int cid = std::stoi(_arguments);
  std::string cardname = cities[cid].name;
  // Make a copy of the infection card you want to destroy from infection discard pile.
  ICard to_remove(cardname, cid);
  // Note: since this event card rarely happens, happy to keep infection_discard a vector despite slow deletion.
  std::vector<ICard>::iterator iter = std::find(infection_discard.begin(), infection_discard.end(), to_remove);
  if (iter != infection_discard.end())
    {
      int index_to_delete = iter - infection_deck.begin();
      infection_deck.erase(infection_deck.begin() + index_to_delete);
      return true;
    }
  else
    return false;
}

void World::event_airlift(std::string _arguments)
{
  // Transport the hero in question to the city in question. Arguments syntax is 3:0 for hero 3 to Atlanta.
  // Parse the hero_id, and city_id.
  // Split by comma delimiter to get data, split neighbours by colon delimiter.
  std::stringstream ss(_arguments);
  std::string item;
  std::vector<string> elems;
  while (std::getline(ss, item, ':'))
    elems.push_back(item);
  int hid = std::stoi(elems[0]);
  int cid = std::stoi(elems[1]);
  // Get the present hero's city to pop the hero ID from City::vector<int> heroes.
  cities[heroes[hid].ptr_city->city_id].depart_hero(hid);
  // Get the hero (by id) to change its City* pointer to the new city.
  heroes[hid].ptr_city = &cities[cid];
  // Get the hero's new city to push the hero ID to City::vector<int> heroes.
  cities[cid].arrive_hero(hid);
}

void World::death(std::string _message)
{
  cout << _message;
  char dummy;
  cout << "The game is over. Press any key to end this game.\n";
  cin >> dummy;
}

void World::init()
{
  centres_remaining = 5;
  outbreaks = 0;
  infection_rate_base = 0;
  skip_next_infect_cities = false;
  for (int i = 0; i < 4; i++) {
    disease_status[i] = UNCURED; // UNCURED is defined to be 0 by preprocessor directive.
    disease_blocks[i] = 24;
  }
}
