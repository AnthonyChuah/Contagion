// Implementation file for the Dispatcher class

#include "macros.h"

#include <iostream>
#include <vector>

Dispatcher::Dispatcher() : Hero()
{}

Dispatcher::Dispatcher(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(_ptr_city, _ptr_world, _hid, _spec)
{}

void Dispatcher::dispatch_control(int _hid, std::string _arguments)
{
  // The Dispatcher's special power can be used only to MOVE (geographically) other players. He cannot make them
  // cure diseases, treat diseases, build centres, share research, etc.
  // The Dispatcher is also a shithead to code.
  std::cout << "Dispatcher::dispatch_control.\n";
}

void Dispatcher::dispatch_move(int _hidfrom, int _hidto)
{
  std::cout << "Dispatcher::dispatch_move.\n";
}
