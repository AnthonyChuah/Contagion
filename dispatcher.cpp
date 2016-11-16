// Implementation file for the Dispatcher class

#include "macros.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

Dispatcher::Dispatcher() : Hero()
{}

Dispatcher::Dispatcher(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(_ptr_city, _ptr_world, _hid, _spec)
{}

bool Dispatcher::dispatch_control(int _hid, std::string _arguments)
{
  // Dispatcher can make another hero do a BASIC ACTION (geographical movement).
  std::cout << "Dispatcher::dispatch_control with arguments " << _hid << " " << _arguments << "\n";
  if (_hid == hero_id) {
    std::cout << "You cannot use the Dispatcher's power to control the Dispatcher himself!\n";
    return false;
  } else if (_hid >= ptr_world->num_players) {
    std::cout << "You cannot use the Dispatcher's power to control a hero who does not exist!\n";
    return false;
  }
  // _arguments should be formatted like this: function_name:cityid, e.g. direct_flight:47.
  std::stringstream ss(_arguments);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, ':'))
    elems.push_back(item);
  std::string function_name = elems[0];
  int city_to = std::stoi(elems[1]);
  if (city_to < 0 || city_to >= ptr_world->num_cities) {
    std::cout << "The city_id specified must be an integer from 0 to 47 inclusive.\n";
    return false;
  } else {
    if (function_name == "move") {
      if (ptr_world->heroes[_hid].move(ptr_world->cities[city_to], this)) {
	moves--;
	return true;
      } else
	return false;
    } else if (function_name == "charter_flight") {
      if (ptr_world->heroes[_hid].charter_flight(ptr_world->cities[city_to], this)) {
	moves--;
	return true;
      } else
	return false;
    } else if (function_name == "direct_flight") {
      if (ptr_world->heroes[_hid].direct_flight(ptr_world->cities[city_to], this)) {
	moves--;
	return true;
      } else
	return false;
    } else if (function_name == "shuttle_flight") {
      if (ptr_world->heroes[_hid].shuttle_flight(ptr_world->cities[city_to], this)) {
	moves--;
	return true;
      } else
	return false;
    } else {
      std::cout << "Dispatcher may make another hero do only the 4 basic movement-related actions.\n";
      return false;
    }
  }
}

bool Dispatcher::dispatch_move(int _hidfrom, int _hidto)
{
  std::cout << "Dispatcher::dispatch_move with arguments " << _hidfrom << " " << _hidto << "\n";
  if (_hidfrom == _hidto) {
    std::cout << "You cannot move a hero to itself.\n";
    return false;
  } else if (_hidfrom < 0 || _hidto < 0 || _hidfrom>=ptr_world->num_players || _hidto>=ptr_world->num_players) {
    std::cout << "You must select hero_ids as integers between 0 to (num_players-1) inclusive.\n";
    return false;
  }
  // Find the hero who you are moving, grab its city, and remove that hero from its city.
  ptr_world->heroes[_hidfrom].ptr_city->depart_hero(_hidfrom);
  // For the hero you are moving, re-point its city pointer to the new city.
  ptr_world->heroes[_hidfrom].ptr_city = ptr_world->heroes[_hidto].ptr_city;
  // Find the hero to whom you are moving, grab its city, and add the moved hero to that city.
  ptr_world->heroes[_hidto].ptr_city->arrive_hero(_hidfrom);
  moves--;
  return true;
}
