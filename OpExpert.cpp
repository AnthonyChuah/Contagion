// Implementation file for the Operations Expert class

#include <iostream>
#include <vector>
#include <list>
#include "pcard.h"
#include "hero.h"
#include "OpExpert.h"

/* -- Build centre: adds a research centre to the city specified.          -- */
// build research centre WITHOUT DISCARDING a city card, redefines build_centre
void OpExpert::build_centre(City& city) {
  std::list<PCard>::iterator it; //list iterator

  // If remaining centres, and no centre exists in the city
  if(ptr_world->centres_remaining>0 && city.research_centre==false) {
      city.research_centre==true;
      ptr_world->centres_remaining--;
  }
  else {
    cout<<"Unable to build a research centre (existing centre in the city or no "; 
    cout<< "centres remaining)!" << endl;
    // NOTE: SHOULD TECHNICALLY ALLOW FOR MOVING CENTRES FROM THE BOARD!
  }
}

  
// Function to implement the Operations Expert specialist action:
// - fly from a research station to any city by discarding any city card
void OpExpert::spec_action() {
  //If the current city has a research station

  // Choose a card to spend, and fly to that city

     // prompt the player to provide a card to spend

     // move the character to the new city

  
}
