#include "macros.h"

#include <string>

ICard::ICard() : city_id(-1)
{
  name = "Empty Constructor";
}

ICard::ICard(std::string _name, int _cid) : city_id(_cid)
{
  name = _name;
}

ICard::ICard(const ICard& _copy_from)
{
  name = _copy_from.name;
  city_id = _copy_from.city_id;
}

ICard& ICard::operator =(const ICard& _assign_from)
{
  name = _assign_from.name;
  city_id = _assign_from.city_id;
  return *this;
}

bool ICard::operator ==(const ICard& _compare)
{
  return (city_id == _compare.city_id);
}
