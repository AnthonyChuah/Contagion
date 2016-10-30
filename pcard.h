#ifndef PCARD_H
#define PCARD_H

/*
Header file for PCard class. A Player Card can be:
1. A city card.
2. An event card.
3. An epidemic card.
Note: leave everything public, it is not complicated enough to need the distinction.
*/

#include <string>

class PCard
{
public:
  PCard();
  PCard(std::string _name, int _cid, bool _is_event, bool _is_epidemic);
  PCard(const PCard& _copy_from);
  PCard& operator =(const PCard& _assign_from);
  bool operator ==(const PCard& _compare);
  std::string name; // Name of the card.
  int city_id; // ID number of the city if it is a player card with a city on it: else, city_id = -1.
  bool event; // Flag to show if card is an event card.
  bool epidemic; // Flag to show if card is an epidemic card.
};

#endif
