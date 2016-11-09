#include <string>

#include "icard.h"

ICard::Icard() : city_id(-1) { name = "Empty Constructor"; }

ICard::ICard(string _name, int _cid) : city_id(_cid) { name = _name; }

void ICard::operator =(const ICard& _assign_from)
{
  name = _assign_from.name;
  city_id = _assign_from.city_id;
}

ICard::ICard(const ICard& _copy_from)
{
  name = _copy_from.name;
  city_id = _copy_from.city_id;
}
