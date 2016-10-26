#ifndef CITY_H
#define CITY_H

/*
Header file for City class.
*/
class City
{
public:
  City();
  // Default constructor.
  City(int city_id, string city_name, int d_id, int x_coord, int y_coord, const vector<int>& neighbour);
  // Constructor with arguments.
  ~City();
  // Destructor.
  City(const City& copy_from);
  // Copy constructor to ensure good behaviour with STL datastructures.
  void infect(int d_id);
  // Attempts to infect the city with this disease.
  // If corresponding disease counter == 3, trigger contagion() method.
  // Else increment disease counter by 1.
  // Exceptions: disease has been ERADICATED: do nothing, or hero has QUARANTINE attribute: do nothing.
  void contagion(int d_id);
  // Contagion is triggered, infecting neighbouring cities. This can trigger contagions in neighbours.
  void disinfect(int d_id);
  // Decrement corresponding counter by 1.
  // If disease has been CURED, set to 0.
  // If hero has MEDIC attribute, set all disease_counters to 0.
  bool has_research_centre(); // Returns true if the City has a research centre.
  int get_disease_id(); // Returns the disease_id of this city.
private:
  int city_id; // Identifier for the city.
  int disease_id; // Disease 1 is blue, 2 is yellow, 3 is black, 4 is red.
  int disease_counters[4];
  // Counts the number of disease counters for each disease: min 0 counters, max 3 counters.
  bool research_centre;
  // Indicates if a research centre exists in that city.
  list<int> neighbours;
  // List containing the IDs of neighbouring cities.
  list<int> heroes;
  // List containing the IDs of Heroes (players) present in the City.
};

#endif
