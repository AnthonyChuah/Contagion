#ifndef PCARD_H
#define PCARD_H

/*
Header file for PCard class. A Player Card can be:
1. A city card.
2. An event card.
3. An epidemic card.
Note: leave everything public, it is not complicated enough to need the distinction.
*/

class PCard
{
public:
  PCard();
  PCard(string card_name, int c_id, bool is_event, bool is_epidemic);
  ~PCard();
  PCard(const PCard& copy_from);
  PCard& operator =(const PCard& assign_from);
  string name; // Name of the card.
  int city_id; // ID number of the city if it is a player card with a city on it: else, city_id = -1.
  bool event; // Flag to show if card is an event card.
  bool epidemic; // Flag to show if card is an epidemic card.
};

#endif
