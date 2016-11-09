// Implementation file for the Contingency Planner class

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "pcard.h"
#include "hero.h"
#include "contplanner.h"

class ContPlanner: public Hero
{
public:
  // Constructors are not automatically inherited from Hero, but these will call Hero's constructors.
  ContPlanner();
  ContPlanner(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec);
  bool play_special_eventcard();
  bool get_special_eventcard(std::string _eventname);
private:
  virtual bool spec_action();
  PCard eventcard; // Contingency Planner has a special slot for an event card that does not occupy the hand.
};

ContPlanner::ContPlanner() : Hero()
{}

ContPlanner::ContPlanner(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec) :
  Hero(City* _ptr_city, World* _ptr_world, int _hid, std::string _spec)
{}

bool ContPlanner::play_special_eventcard(std::string _arguments)
{
  if (ptr_world->play_eventcard(*this, eventcard.name, _arguments)) {
    return true;
  } else {
    return false;
  }
}

bool ContPlanner::get_special_eventcard(std::string _eventname)
{
  std::vector<PCard>::iterator it;
  for (it = ptr_world->player_discard.begin(); it != ptr_world->player_discard.end(); it++) {
    if (it->name == _eventname) {
      eventcard = *it;
      ptr_world->player_discard.erase(it);
      std::cout << "Contingency Planner has taken event card " << _eventname << " into its hand.\n";
      return true;
    }
  }
  return false;
}

bool ContPlanner::spec_action()
{
  std::cout << "Presently no ContPlanner action implemented, instead we have two separate functions.\n";
  return false;
}
/* Function to implement the Contingency Planner specialist action - take event 
   card in discard pile
void ContPlanner::spec_action() {
  // a list containing the cards in the player discard pile
  std::list<PCard> disc_list(ptr_world->player_discard.begin(),ptr_world->player_discard.end()); 
  std::list<PCard>::iterator it;
  
  // remove all non-event cards
  for(it=disc_list.begin();it!=disc_list.end(); it++) {
    if(it->event==false) //if the card is not an event card
      disc_list.erase(it);
  }

  // Display all cards in the list
  view_discarded_events(disc_list);

  // Interface for picking a card

  cout<<"STUB - FINISH THIS - NEED TO BE ABLE TO TAKE INPUT TO PICK A CARD, ADD TO HAND (AS EXTRA), AND ERASE FROM DISCARD PILE"<<endl;
  
  
}

*/

// has to be able to view all the cards, but also decide against taking a card (presumably)


/*----------------------------------------------------------------------------*/
/* Helper function for viewing the cards on the list                          */
/*----------------------------------------------------------------------------*/
/*
void ContPlanner::view_discarded_events(std::list<PCard>& list) {
  std::list<Testclass>::iterator it; //list iterator
  std::cout << "The discard pile contains the following event cards: ";
  for (it=list.begin(); it!=list.end(); it++)
    std::cout << " " << it->name;
  std::cout << "\n";
}
*/
