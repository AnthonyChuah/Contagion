#include <string>

#include "pcard.h"

PCard::PCard() : name("Empty Constructor"), disease_id(-1), city_id(-1), event(false), epidemic(false)
{}

PCard::PCard(string _name, int _cid, int _did, bool _is_event, bool _is_epidemic) :
  name(_name), city_id(_cid), disease_id(_did), event(_is_event), epidemic(_is_epidemic)
{}

PCard::PCard(const PCard& _copy_from)
{
  name = _copy_from.name;
  city_id = _copy_from.city_id;
  disease_id = _copy_from.disease_id;
  event = _copy_from.event;
  epidemic = _copy_from.epidemic;
}

void PCard::operator =(const PCard& _assign_from)
{
  name = _assign_from.name;
  city_id = _assign_from.city_id;
  disease_id = _assign_from.disease_id;
  event = _assign_from.event;
  epidemic = _assign_from.epidemic;
}

bool PCard::operator ==(const PCard& _compare)
{
  if (name == _compare.name && city_id == _compare.city_id &&
      event == _compare.event && epidemic == _compare.epidemic)
    return true;
  else
    return false;
}
