// Implementation file for the Medic class

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "hero.h"

using namespace std;

/* -- Fly function: fly to the city "to_city" if viable, and return true.
      If the flight is not viable, return false.                           -- */
bool Hero::fly(City& to_city) {
  std::vector<PCard>::iterator it; //vector iterator

  // Direct flight: if there is a city card matching "to_city"
  for(it=hand.begin(); it<hand.end(); it++) {
    if(it->city_id==to_city.city_id) {
      // Move ptr_city to new city
      ptr_city=&to_city;
      // Erase the card from hand
      hand.erase(it);
      return true;
    }
  }

  
  // Charter flight: if there is a city card matching current city (*ptr_city)
  for(it=hand.begin(); it<hand.end(); it++) {
    if(it->city_id==ptr_city->city_id) {
      // Move ptr_city to new city
      ptr_city=&to_city;
      // Erase the card from hand
      hand.erase(it);
      return true;
    }
  }

  //OTHERWISE
  return false;
}



/* -- Move function: move to the city "to_city" if viable, and return true.
      If the move is not viable, return false.                             -- */
bool Hero::move(City& to_city) {
  cout<<"STUB - add the 'move' functionality." << endl;
  return true;
}



/* -- Disinfect: removes one "disease cube" of the "d_id" colour.          -- */
void Hero::disinfect(int d_id) {
  // Decrementing the disease counter for the disease "d_id"
  if(ptr_city->disease_counters[d_id] > 0)
    ptr_city->disease_counters[d_id]--;   
}



/* -- Build centre: adds a research centre to the city specified.          -- */
void Hero::build_centre(City& city) {
  std::vector<PCard>::iterator it; //vector iterator

  // If remaining centres, and no centre exists in the city
  if(ptr_world->centres_remaining>0 && city.research_centre==false) {
    //Check if a city in hand matches city to build in
    for(it=hand.begin(); it<hand.end(); it++) {
      if(it->city_id==to_city.city_id) {
	hand.erase(it); //remove the card from hand
	city.research_centre==true;
	ptr_world->centres_remaining--;
        break;
      }
    }
    cout<<"Unable to build a research centre, as no matching card!" << endl;
  }
  else {
    cout<<"Unable to build a research centre (existing centre in the city or no "; 
    cout<< "centres remaining)!" << endl;
    // NOTE: SHOULD TECHNICALLY ALLOW FOR MOVING CENTRES FROM THE BOARD!
  }
}



/* -- Cure: if five cards of same colour in hand, cure that disease.       -- */
void Hero::cure(int disease_id) {
  //std::vector<PCard>::iterator it; //vector iterator

  //for(it=hand.begin(); it<hand.end(); it++) {
    //for(  //for all cities with d_id==disease_id ?
    //if(it->city_id==ptr_city->city_id) {
	  //}  
  cout<<"STUB - add the 'cure' functionality." << endl;
}
