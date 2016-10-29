#ifndef ICARD_H
#define ICARD_H

/*
Header file for ICard class. An Infection Card has a city's name on it.
*/

#include <string>

class ICard
{
public:
  ICard();
  ICard(string _name, int _cid);
  void operator =(const ICard& _assign_from);
  ICard(const ICard& _copy_from);
  std::string name; // Name of the card: should be a city name.
  int city_id;
};

#endif
