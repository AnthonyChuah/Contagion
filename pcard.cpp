#include <string>

#include "pcard.h"

PCard::PCard() : city_id(-1), event(false), epidemic(false)
{
  name = "Empty Constructor";
}

PCard::PCard(string _name, int _cid, bool _is_event, bool _is_epidemic) : city_id(_cid), event(_is_event), epidemic(_is_epidemic)
{
  name = _name;
}

PCard::PCard(const PCard& _copy_from)
{
  name = _copy_from.name;
  city_id = _copy_from.city_id;
  event = _copy_from.event;
  epidemic = _copy_from.epidemic;
}

void PCard::operator =(const PCard& _assign_from)
{
  name = _assign_from.name;
  city_id = _assign_from.city_id;
  event = _assign_from.event;
  epidemic = _assign_from.epidemic;
}
