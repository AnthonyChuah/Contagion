#ifndef ICARD_H
#define ICARD_H

/*
Header file for ICard class. An Infection Card has a city's name on it.
*/

class ICard
{
public:
  ICard();
  ICard(string card_name, int c_id);
  ~ICard();
  ICard& operator =(const ICard& assign_from);
  ICard(const ICard& copy_from);
  string name; // Name of the card: should be a city name.
  int city_id;
};

#endif
