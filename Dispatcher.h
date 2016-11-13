#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <string>

class Dispatcher : public Hero
{
public:
  Dispatcher();
  Dispatcher(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
  void dispatch_control(int _hid, std::string _arguments);
  void dispatch_move(int _hidfrom, int _hidto);
};

#endif
