/*
Implementation file for the World class.
*/

#include "macros.h"

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

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
    std::getline(ins, rowdata);
    std::cout << "Read city rowdata: " << rowdata << "\n";
    // If rowdata is simply empty (last line) then continue.
    if (rowdata.empty()) continue;
    
    // Split by comma delimiter to get data, split neighbours by colon delimiter.
    std::stringstream ss(rowdata);
    std::string item;
    std::vector<std::string> elems;
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
    xcoord = std::stod(elems[2]); ycoord = std::stod(elems[3]);
    if (cityid == 0) has_rc = true;
    did = std::stoi(elems[4]);
    std::vector<int> cityneighbours;
    std::stringstream sss(elems[5]);
    std::string subitem;
    while (std::getline(sss, subitem, ':'))
      cityneighbours.push_back(std::stod(subitem));
    std::cout << "City constructor arguments: " << cityid << cityname << did
	      << did << xcoord << ycoord << "\n";
    City a_city(cityid,cityname,did,xcoord,ycoord,cityneighbours,this,has_rc);
    cities.push_back(a_city);
    
    // Call constructor for ICard and PCard and push them into respective vectors too.
    ICard an_icard(cityname,cityid);
    std::cout << "Infection card constructor: " << cityname << cityid << "\n";
    infection_deck.push_back(an_icard);
    PCard a_pcard(cityname,cityid,did,false,false);
    std::cout << "Player card constructor: " << cityname << cityid << did << "\n";
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
  while (ins.good()) {
    std::cout << "DEBUG: reading event row data.\n";
    std::getline(ins, rowdata);
    // rowdata should simply be the event name, unless it read a blank row (end of file).
    if (rowdata.empty()) continue;
    // Call constructor for PCard and push onto the PCard vector.
    PCard a_pcard(rowdata,-1,-1,true,false);
    player_deck.push_back(a_pcard);
  }
  ins.close();
  std::cout << "Event card reading complete: please use debugger to inspect.\n";
  // Remember to inspect the vector.
}

void World::load_hero_data(std::string _filename)
{
  std::ifstream ins;
  ins.open(_filename);
  if (ins.fail()) {
    std::cout << "Failed to open heroes input file.\n";
    exit(1);
  }
  std::string rowdata;
  std::string hero_spec;
  int hid = 0;
  bool contplanner = false, dispatcher = false, medic = false, opexpert = false;
  bool qspecialist = false, researcher = false, scientist = false;
  while (ins.good()) {
    std::getline(ins, rowdata);
    std::cout << "Read rowdata: " << rowdata << "\n";
    // rowdata should simply be the hero's specialization, unless it is just a blank.
    if (rowdata.empty()) continue;
    hero_spec = rowdata;
    // If string is not empty, record it directly in hero_spec then call constructor and push to heroes vector.
    // ALWAYS call load_hero_data AFTER load_city_data, because Hero needs a pointer to Atlanta at init.
    City* ptr_atlanta = &cities[0]; // Set City pointer to first city in World::cities.
    if (hero_spec == "Contingency Planner") {
      if (contplanner) {
	std::cout << "You cannot have multiple Contingency Planners in the game.\n";
	exit(1);
      }
      ContPlanner a_hero(ptr_atlanta,this,hid,hero_spec);
      contplanner = true;
      heroes.push_back(a_hero);
    } else if (hero_spec == "Dispatcher") {
      if (dispatcher) {
	std::cout << "You cannot have multiple Dispatchers in the game.\n";
	exit(1);
      }
      Dispatcher a_hero(ptr_atlanta,this,hid,hero_spec);
      heroes.push_back(a_hero);
    } else if (hero_spec == "Medic") {
      if (medic) {
	std::cout << "You cannot have multiple Medics in the game.\n";
	exit(1);
      }
      Medic a_hero(ptr_atlanta,this,hid,hero_spec);
      medic = true;
      heroes.push_back(a_hero);
    } else if (hero_spec == "Operations Expert") {
      if (opexpert) {
	std::cout << "You cannot have multiple Operations Experts in the game.\n";
	exit(1);
      }
      OpExpert a_hero(ptr_atlanta,this,hid,hero_spec);
      opexpert = true;
      heroes.push_back(a_hero);
    } else if (hero_spec == "Quarantine Specialist") {
      if (qspecialist) {
	std::cout << "You cannot have multiple Quarantine Specialists in the game.\n";
	exit(1);
      }
      QSpecialist a_hero(ptr_atlanta,this,hid,hero_spec);
      qspecialist = true;
      heroes.push_back(a_hero);
    } else if (hero_spec == "Researcher") {
      if (researcher) {
	std::cout << "You cannot have multiple Researchers in the game.\n";
	exit(1);
      }
      Researcher a_hero(ptr_atlanta,this,hid,hero_spec);
      researcher = true;
      heroes.push_back(a_hero);
    } else if (hero_spec == "Scientist") {
      if (scientist) {
	std::cout << "You cannot have multiple Scientists in the game.\n";
	exit(1);
      }
      Scientist a_hero(ptr_atlanta,this,hid,hero_spec);
      scientist = true;
      heroes.push_back(a_hero);
    } else {
      std::cout << "I see a hero that I cannot recognize. Abort this program now.\n";
      exit(1);
    }
    cities[0].heroes.push_back(hid);
    // Hero a_hero = Hero(ptr_atlanta,this,hero_spec);
    hid++;
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
  if (num_players > 4) {std::cout << "You cannot have more than 4 players.\n"; exit(1);}
  else if (num_players < 2) {std::cout << "You cannot have fewer than 2 players.\n"; exit(1);}
  std::cout << "Found " << num_players << " players and " << num_cities << " cities.\n";
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
    std::string epidemic("Epidemic");
    PCard an_epidemic(epidemic,-1,-1,false,true);
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

void World::render_world_ascii()
{
  int width = ui_width; int height = ui_height;
  // We do not yet know how exactly we will render the world in ASCII.
  // Default width 180 characters, height 60 characters.
  char map[width][height]; // 2d character array represents the map.
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      map[i][j] = 0;
  for (int i = 0; i < cities.size(); i++) {
    // Get city's x and y coordinates.
    int x_position = cities[i].x_coord * width;
    int y_position = cities[i].y_coord * height;
    map[x_position][y_position] = '*';
    for (int j = 0; j < 4; j++)
      map[x_position+1+j][y_position] = cities[i].shortname[j];
    int left_digit = cities[i].city_id / 10; int right_digit = cities[i].city_id % 10;
    map[x_position+5][y_position] = static_cast<char>(left_digit) + '0';
    map[x_position+6][y_position] = static_cast<char>(right_digit) + '0';
    if (cities[i].has_rc())
      map[x_position][y_position+1] = 'R';
    for (int j = 0; j < 4; j++)
      map[x_position+1+j][y_position+1] = (static_cast<char>(cities[i].get_ncubes(j)) + '0');
    map[x_position][y_position+2] = (static_cast<char>(cities[i].get_disease_id()) + '0');
    map[x_position+1][y_position+2] = 'D';
    map[x_position+2][y_position+2] = (static_cast<char>(cities[i].heroes.size() + '0'));
    map[x_position+3][y_position+2] = 'H';
  }
  // Output the map.
  for (int j = height-1; j >= 0; j--)
    for (int i = 0; i < width; i++) {
      std::cout << map[i][j];
      if (i == width-1) {
	std::cout << "\n";
      }
    }
  // Output the disease statuses.
  std::cout << "Disease status 0 is UNCURED, 1 is CURED, 2 is ERADICATED.\n";
  std::cout << "Disease cubes start from 24 each and are placed on cities. If you run out you lose.\n";
  std::cout << "Disease 0 is yellow, 1 is red, 2 is blue, 3 is black.\n";
  for (int k = 0; k < 4; k++) {
    std::cout << "Disease " << k << " status: " << disease_status[k] << "  ";
  }
  std::cout << "\n";
  for (int k = 0; k < 4; k++) {
    std::cout << "Disease " << k << " cubes:  " << disease_blocks[k] << "  ";
  }
  std::cout << "\n";
  std::cout << "Infection deck: " << infection_deck.size() << " cards. ";
  std::cout << "Infection discards: " << infection_discard.size() << " cards.\n";
  std::cout << "Player deck: " << player_deck.size() << " cards. ";
  std::cout << "Player discards: " << player_discard.size() << " cards.\n";
  std::cout << "Infection rate: " << calculate_infection_rate() << "\n";
  std::cout << "Player turn: Player " << players_turn << " of " << num_players << " total players. ";
  std::cout << "Moves left: " << heroes[players_turn].moves << "\n";
  for (int i = 0; i < num_players; i++) {
    std::cout << "HeroID " << i << " " << heroes[i].spec << ": " << heroes[i].ptr_city->name << "\n";
  }
}

bool World::victory()
{
  for (int i = 0; i < 4; i++) {
    if (disease_status[i] == UNCURED)
      return false;
  }
  std::cout << "CONGRATULATIONS! You have saved the world from plague!\n";
  return true;
}

void World::game_loop()
{
  std::string input;
  while (!victory()) {
    while (heroes[players_turn].moves > 0) {
      bool made_move = false;
      while (!made_move) {
	// Parse player input here. Once parsed with regex, go to the move-decrementing and turn-handling section.
	// Empty for now.
	std::getline(std::cin, input);
	made_move = handle_input(input);
      }
      // Now made_move has been set to true, the above while loop exited.
      // Moves are decremented inside the heroes' functions.
      render_world_ascii(); // Render the world again in text for the player to see.
    }
    // Now the hero in question has finished its turn. Draw player cards and then infect cities.
    draw_player_deck(heroes[players_turn]);
    draw_infection_deck();
    next_player_turn();
  }
}

bool World::handle_input(std::string _input)
{
  std::regex regex_viewcity("^display_city (.+)$"); // display_city CITY_ID
  std::regex regex_move("^move (.+)$"); // move CITY_ID
  std::regex regex_charter("^charter_flight (.+)$"); // charter_flight CITY_ID
  std::regex regex_direct("^direct_flight (.+)$"); // direct_flight CITY_ID
  std::regex regex_shuttle("^shuttle_flight (.+)$"); // shuttle_flight CITY_ID
  std::regex regex_disinfect("^disinfect (.+)$"); // disinfect DISEASE_ID
  std::regex regex_givecard("^give_card (.+) (.+)$"); // give_card CITY_ID HERO_ID
  std::regex regex_takecard("^take_card (.+) (.+)$"); // take_card CITY_ID HERO_ID
  std::regex regex_cure("^cure (.+) (.+) (.+) (.+) (.+) (.+)$"); // cure DISEASE_ID CITY_ID CITY_ID CITY_ID CITY_ID CITY_ID
  std::regex regex_event("^play_event_card (\\d{1}) (.+),(.+)$"); // ... HERO_ID EVENTNAME,ARGUMENTS
  std::regex regex_cpget("^get_special_eventcard (.+)$"); // get_special_eventcard EVENT_NAME
  std::regex regex_cpplay("^play_special_eventcard (.+)$"); // play_special_eventcard EVENT_NAME
  std::regex regex_dispatchc("^dispatch_control (.+) (.+)$"); // dispatch_control HERO_ID FUNCTION:CITY_ID
  std::regex regex_dispatchm("^dispatch_move (.+)$"); // dispatch_move HERO_ID HERO_ID(TO)
  std::regex regex_opex("^opex_flight (.+) (.+)$"); // opex_flight CITY_ID(TO) CITY_ID(CARD)
  std::regex regex_scientist("^scientist (.+) (.+) (.+) (.+) (.+)$"); // scientist DISEASE_ID CITY_ID CITY_ID CITY_ID CITY_ID
  std::smatch match_group;
  // Note: lots more inputs to be added.
  if (_input == "look") {
    render_world_ascii();
    return false;
  } else if (std::regex_match(_input, match_group, regex_viewcity)) {
    if (match_group.size() == 2) {
      std::cout << "Regex for input handling detected a command for display_city().\n";
      std::ssub_match submatch_viewcity = match_group[1];
      int cid = std::stoi(submatch_viewcity.str());
      display_city(cid);
      return false;
    }
  } else if (_input == "display_player_discard") {
    display_player_discard();
    return false;
  } else if (_input == "display_infection_discard") {
    display_infection_discard();
    return false;
  } else if (_input == "display_hands") {
    display_hands();
    return false;
  } else if (std::regex_match(_input, match_group, regex_move)) {
    if (match_group.size() == 2) {
      std::cout << "Regex for input handling detected command for Hero::move().\n";
      std::ssub_match submatch_move = match_group[1];
      int cid = std::stoi(submatch_move.str());
      if (heroes[players_turn].move(cities[cid], NULL)) {
	return true;
      }
    }
  } else if (std::regex_match(_input, match_group, regex_charter)) {
    if (match_group.size() == 2) {
      std::cout << "Regex for input handling detected command for Hero::charter_flight().\n";
      std::ssub_match submatch_charter = match_group[1];
      int cid = std::stoi(submatch_charter.str());
      if (heroes[players_turn].charter_flight(cities[cid], NULL)) {
	return true;
      }
    }
  } else if (std::regex_match(_input, match_group, regex_direct)) {
    if (match_group.size() == 2) {
      std::cout << "Regex for input handling detected command for Hero::direct_flight().\n";
      std::ssub_match submatch_direct = match_group[1];
      int cid = std::stoi(submatch_direct.str());
      if (heroes[players_turn].direct_flight(cities[cid], NULL)) {
	return true;
      }
    }
  } else if (std::regex_match(_input, match_group, regex_shuttle)) {
    if (match_group.size() == 2) {
      std::cout << "Regex for input handling detected command for Hero::shuttle_flight().\n";
      std::ssub_match submatch_shuttle = match_group[1];
      int cid = std::stoi(submatch_shuttle.str());
      if (heroes[players_turn].direct_flight(cities[cid], NULL)) {
	return true;
      }
    }
  } else if (std::regex_match(_input, match_group, regex_disinfect)) {
    if (match_group.size() == 2) {
      std::cout << "Regex for input handling detected command for Hero::disinfect().\n";
      std::ssub_match submatch_disinfect = match_group[1];
      int did = std::stoi(submatch_disinfect.str());
      if (heroes[players_turn].disinfect(did)) {
	return true;
      }
    }
  } else if (_input == "build_centre") {
    if (heroes[players_turn].build_centre(*heroes[players_turn].ptr_city)) {
      return true;
    }
  } else if (std::regex_match(_input, match_group, regex_givecard)) {
    if (match_group.size() == 3) {
      std::cout << "Regex for input handling detected command for Hero::give_card().\n";
      int cid = std::stoi(match_group[1].str());
      int hid = std::stoi(match_group[2].str());
      if (heroes[players_turn].give_card(cities[cid].name, heroes[hid])) {
	return true;
      }
    }
  } else if (std::regex_match(_input, match_group, regex_takecard)) {
    if (match_group.size() == 3) {
      std::cout << "Regex for input handling detected command for Hero::take_card().\n";
      int cid = std::stoi(match_group[1].str());
      int hid = std::stoi(match_group[2].str());
      if (heroes[players_turn].take_card(cities[cid].name, heroes[hid])) {
	return true;
      }
    }
  } else if (std::regex_match(_input, match_group, regex_event)) {
    if (match_group.size() == 4) {
      std::cout << "Regex for input handling detected command for World::play_event_card().\n";
      int hid = std::stoi(match_group[1].str());
      return (play_event_card(heroes[hid], match_group[2].str(), match_group[3].str()));
    }
  } else if (std::regex_match(_input, match_group, regex_cure)) {
    if (match_group.size() == 7) {
      std::cout << "Regex for input handling detected command for Hero::cure().\n";
      int did = std::stoi(match_group[1].str());
      int cid0 = std::stoi(match_group[2].str());
      int cid1 = std::stoi(match_group[3].str());
      int cid2 = std::stoi(match_group[4].str());
      int cid3 = std::stoi(match_group[5].str());
      int cid4 = std::stoi(match_group[6].str());
      return (heroes[players_turn].cure(did, cities[cid0].name, cities[cid1].name,
					cities[cid2].name, cities[cid3].name, cities[cid4].name));
    }
  } else if (std::regex_match(_input, match_group, regex_cpget)) {
    if (match_group.size() == 2) {
      std::cout << "Regex for input handling detected command for ContPlanner::get_special_eventcard().\n";
      if (heroes[players_turn].spec == "Contingency Planner") {
	return heroes[players_turn].get_special_eventcard(match_group[2].str());
      } else {
	std::cout << "Only the Contingency Planner can do this.\n";
      }
    }
  } else if (std::regex_match(_input, match_group, regex_cpplay)) {
    if (match_group.size() == 2) {
      std::cout << "Regex for input handling detected command for ContPlanner::play_special_eventcard().\n";
      if (heroes[players_turn].spec == "Contingency Planner") {
	return heroes[players_turn].play_special_eventcard(match_group[2].str());
      } else {
	std::cout << "Only the Contingency Planner can do this.\n";
      }
    }
  } else if (std::regex_match(_input, match_group, regex_dispatchc)) {
    if (match_group.size() == 3) {
      std::cout << "Regex for input handling detected command for Dispatcher::dispatch_control().\n";
      if (heroes[players_turn].spec == "Dispatcher") {
	int hid = std::stoi(match_group[1].str());
	return heroes[players_turn].dispatch_control(hid, match_group[2].str());
      } else {
	std::cout << "Only the Dispatcher can do this.\n";
      }
    }
  } else if (std::regex_match(_input, match_group, regex_dispatchm)) {
    if (match_group.size() == 3) {
      std::cout << "Regex for input handling detected command for Dispatcher::dispatch_move().\n";
      if (heroes[players_turn].spec == "Dispatcher") {
	int hidfrom = std::stoi(match_group[1].str());
	int hidto = std::stoi(match_group[2].str());
	return heroes[players_turn].dispatch_move(hidfrom, hidto);
      } else {
	std::cout << "Only the Dispatcher can do this.\n";
      }
    }
  } else if (std::regex_match(_input, match_group, regex_opex)) {
    if (match_group.size() == 3) {
      std::cout << "Regex for input handling detected command for OpExpert::opex_flight().\n";
      if (heroes[players_turn].spec == "Operations Expert") {
	int cidto = std::stoi(match_group[1].str());
	int cardcid = std::stoi(match_group[2].str());
	return heroes[players_turn].opex_flight(cities[cidto], cities[cardcid].name);
      } else {
	std::cout << "Only the Operations Expert can do this.\n";
      }
    }
  } else if (std::regex_match(_input, match_group, regex_scientist)) {
    if (match_group.size() == 6) {
      std::cout << "Regex for input handling detected command for Scientist::cure().\n";
      if (heroes[players_turn].spec == "Scientist") {
	int did = std::stoi(match_group[1].str());
	int cid0 = std::stoi(match_group[2].str());
	int cid1 = std::stoi(match_group[3].str());
	int cid2 = std::stoi(match_group[4].str());
	int cid3 = std::stoi(match_group[5].str());
	return (heroes[players_turn].scientist_cure(did, cities[cid0].name, cities[cid1].name,
					  cities[cid2].name, cities[cid3].name));
      } else {
	std::cout << "Only the Scientist can do this.\n";
      }
    }
  }
  std::cout << "I do not recognize that command.\n";
  return false;
}

void World::next_player_turn()
{
  std::cout << "Player " << players_turn << " has ended its turn, now for player ";
  players_turn++;
  if (players_turn == num_players) {
    players_turn = 0;
  }
  std::cout << players_turn << ".\n";
  heroes[players_turn].start_turn();
}

void World::display_city(int _cid)
{
  std::cout << "Calling World::display_city().\n";
  std::cout << "City number " << _cid << ": " << cities[_cid].name << "\n";
  std::cout << "Associated disease ID: " << cities[_cid].disease_id << "  ";
  std::cout << "Disease cubes for diseases 1 2 3 4:";
  for (int i = 0; i < 4; i++)
    std::cout << " " << cities[_cid].disease_counters[i];
  std::cout << "\nNeighbouring City IDs:";
  for (int i = 0; i < cities[_cid].neighbours.size(); i++)
    std::cout << " " << cities[_cid].neighbours[i];
  std::cout << "\n";
}

void World::display_player_discard()
{
  std::cout << "Calling World::display_player_discard().\n";
  int ncards = player_discard.size();
  if (ncards == 0) {
    std::cout << "The player discard pile is empty.\n";
    return;
  } else {
    std::cout << "Displaying cards from bottom to top:\n";
    for (int i = 0; i < ncards; i++) {
      std::cout << i << ") " << player_discard[i].name << "\n";
    }
  }
}

void World::display_infection_discard()
{
  std::cout << "Calling World::display_infection_discard().\n";
  int ncards = infection_discard.size();
  if (ncards == 0) {
    std::cout << "The infection discard pile is empty.\n";
    return;
  } else {
    std::cout << "Displaying cards from bottom to top:\n";
    for (int i = 0; i < ncards; i++) {
      std::cout << i << ") " << infection_discard[i].name << "\n";
    }
  }
}

void World::display_hands()
{
  std::cout << "Calling World::display_hands().\n";
  for (int i = 0; i < num_players; i++) {
    std::cout << "Player " << i << " " << heroes[i].spec << ": ";
    int ncards = heroes[i].hand.size();
    for (int j = 0; j < ncards; j++) {
      if (heroes[i].hand[j].event)
	std::cout << "EVENT ";
      std::cout << heroes[i].hand[j].name << " ";
    }
    std::cout << "\n";
  }
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
      for (int i = 0; i < calculate_infection_rate(); i++)
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
  std::cout << "Calling World::draw_player_deck().\n";
  for (int i = 0; i < 2; i++)
    {
      if (player_deck.empty()) death("Lost game because you ran out of player cards to draw!\n");
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
  while (infection_discard.size() > 0)
    {
      infection_deck.push_back(infection_discard.back());
      infection_discard.pop_back();
    }
}

bool World::check_eradication(int _did)
{
  if (disease_blocks[_did] == 24 && disease_status[_did] == CURED) {
    disease_status[_did] = ERADICATED;
    return true;
  }
  return false;
}

bool World::play_event_card(Hero& _hero, std::string _event, std::string _arguments)
{
  // Use iterator to find the relevant card in the player's hand, then pop it, then make the event happen.
  if (_event == "Government Grant")
    {
      // Check that hero's hand contains that card.
      PCard govgrant("Government Grant", -1, -1, true, false);
      std::vector<PCard>::iterator iter = std::find(_hero.hand.begin(), _hero.hand.end(), govgrant);
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
      PCard forecast("Forecast", -1, -1, true, false);
      std::vector<PCard>::iterator iter = std::find(_hero.hand.begin(), _hero.hand.end(), forecast);
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
      PCard resilpop("Resilient Population", -1, -1, true, false);
      std::vector<PCard>::iterator iter = std::find(_hero.hand.begin(), _hero.hand.end(), resilpop);
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
      PCard airlift("Airlift", -1, -1, true, false);
      std::vector<PCard>::iterator iter = std::find(_hero.hand.begin(), _hero.hand.end(), airlift);
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
  std::cout << "Calling World::event_forecast().\n";
  // Plan: make a GUI class that has an association link to World class. World will soon contain a pointer to GUI.
  std::vector<ICard> to_display;
  int decksize = std::min(static_cast<int>(infection_deck.size()), 6);
  for (int i = 0; i < decksize; i++)
    to_display.push_back(infection_deck[infection_deck.size()-decksize+i]);
  // Above code concisely expresses the different treatment if the deck contained less than 6 cards.
  for (int i = 0; i < decksize; i++) {
    std::cout << i << ": " << to_display[i].name << "\n";
  }
  std::cout << "Please enter the rearrangement mapping you desire.\n";
  std::vector<int> rearrange_mapping;
  int value;
  for (int i = 0; i < decksize; i++) {
    std::cin >> value;
    rearrange_mapping.push_back(value);
  }
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
  std::cout << "Calling World::event_resilient.\n";
  // Arguments should be a number referring to the city_id.
  int cid = std::stoi(_arguments);
  std::string cardname = cities[cid].name;
  // Make a copy of the infection card you want to destroy from infection discard pile.
  ICard to_remove(cardname, cid);
  // Note: since this event card rarely happens, happy to keep infection_discard a vector despite slow deletion.
  std::vector<ICard>::iterator iter = std::find(infection_discard.begin(), infection_discard.end(), to_remove);
  if (iter != infection_discard.end()) {
    int index_to_delete = iter - infection_discard.begin();
    std::cout << "Resilient Pop event card removed " << to_remove.name << " from play.\n";
    infection_discard.erase(infection_discard.begin() + index_to_delete);
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
  std::vector<std::string> elems;
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
  std::cout << _message;
  char dummy;
  std::cout << "The game is over. Press any key to end this game.\n";
  std::cin >> dummy;
  exit(1);
}

void World::init()
{
  ui_width = 180; ui_height = 60;
  centres_remaining = 5;
  outbreaks = 0;
  infection_rate_base = 0;
  skip_next_infect_cities = false;
  for (int i = 0; i < 4; i++) {
    disease_status[i] = UNCURED; // UNCURED is defined to be 0 by preprocessor directive.
    disease_blocks[i] = 24;
  }
}
