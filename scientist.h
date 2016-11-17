#ifndef SCIENTIST_H
#define SCIENTIST_H

/*
Scientist exceptions:
1. Scientist requires only 4 player cards of the same colour to cure a disease.
*/

#include <string>

class Scientist : public Hero
{
public:
  Scientist();
  Scientist(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
  bool scientist_cure(int _did, std::string _one, std::string _two, std::string _three, std::string _four);
};

#endif
