#ifndef CITY_H
#define CITY_H

/*
Header file for City class.
*/

#include <vector>
#include <string>

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
  City(int _id, std::string _name, int _did, int _xcoord, int _ycoord, const std::vector<int>& _neighbour, World* _worldptr, bool _has_rc);
  City(const City& _copy_from); // Copy constructor to ensure good behaviour with STL data structures.
  City& operator =(const City& _assign_from); // Overloaded assignment operator needed to make the Big 3.

  void outbreak(int _did);
  void infect(int _did, int _numcubes);
  // Outbreak is triggered, infecting neighbouring cities. This can trigger outbreaks in neighbours.
  bool has_rc(); // Returns true if the City has a research centre.
  void build_rc();
  int get_disease_id(); // Returns the disease_id of this city.
  void arrive_hero(int _hid); // Adds hero to the list of heroes in this city.
  void depart_hero(int _hid); // Removes hero from the list of heroes in this city.
  std::string name;
private:
  World* world_ptr; // Pointer to the world the city is in.
  bool skip_next_infect_cities;
  int city_id; // Identifier for the city.
  int x_coord; // X and Y coordinates for where the city is on the map (for rendering purposes).
  int y_coord;
  char shortname[4]; // 4-letter short name for the city to use in ASCII rendering of the world.
  int disease_id; // Disease 0 is yellow, 1 is red, 2 is blue, 3 is black.
  int disease_counters[4]; // Counts the number of disease counters for each disease: from 0 to 3.
  bool research_centre; // Indicates if a research centre exists in that city.
  std::vector<int> neighbours; // Vector containing the IDs of neighbouring cities.
  std::vector<int> heroes; // Vector containing the IDs of Heroes (players) present in the City.
};

#endif
