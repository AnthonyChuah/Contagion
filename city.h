#ifndef CITY_H
#define CITY_H

/*
Header file for City class.
*/


#include <vector>
#include <string>

using namespace std;

// --------------------------- MACROS ----------------------------------- //
// Disease ID (type)
//#define YELLOW 0
//#define RED 1
//#define BLUE 2
//#define BLACK 3
// ---------------------------------------------------------------------- //


class City
{
public:
  City();
  City(int city_id, string city_name, int d_id, int x_coord, int y_coord, const vector<int>& neighbour);
  ~City();
  City(const City& copy_from); // Copy constructor to ensure good behaviour with STL data structures.
  City& operator =(const City& assign_from); // Overloaded assignment operator needed to make the Big 3.
  void infect(City& city, int d_id, int num_cubes);
  // Attempts to infect the city with this disease.
  // If corresponding disease counter == 3, trigger contagion() method.
  // Else increment disease counter by 1. Some exceptions: see game rules.
  // num_cubes should be 1 except during world initialization and epidemics.
  void contagion(int d_id);
  // Contagion is triggered, infecting neighbouring cities. This can trigger contagions in neighbours.
  bool has_research_centre(); // Returns true if the City has a research centre.
  int get_disease_id(); // Returns the disease_id of this city.
  void arrive_hero(int hero_id); // Adds hero to the list of heroes in this city.
  void depart_hero(int hero_id); // Removes hero from the list of heroes in this city.
private:
  World* world_ptr; // Pointer to the world the city is in.
  int city_id; // Identifier for the city.
  int x_coord; // X and Y coordinates for where the city is on the map (for rendering purposes).
  int y_coord;
  char shortname[4]; // 4-letter short name for the city to use in ASCII rendering of the world.
  int disease_id; // Disease 0 is yellow, 1 is red, 2 is blue, 3 is black.
  int disease_counters[4]; // Counts the number of disease counters for each disease: from 0 to 3.
  bool research_centre; // Indicates if a research centre exists in that city.
  vector<int> neighbours; // Vector containing the IDs of neighbouring cities.
  vector<int> heroes; // Vector containing the IDs of Heroes (players) present in the City.
};

#endif
