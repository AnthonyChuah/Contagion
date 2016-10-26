#ifndef WORLD_H
#define WORLD_H

/*
Header file for World class.
The World object should contain everything we need:
1. All cities.
2. All heroes (players).
3. All cards on the board.
4. How many research centres still available to be built.
Thus, all objects contained in the world can easily refer to other objects in the world.
*/

class World
{
public:
  World(); // Default constructor.
  void load_city_data(char filename[]); // Loads the initial city data from a data file.
  void load_cards_data(char filename[]); // Loads the initial cards data from a data file.
  void load_hero_data(char filename[]); // Loads the initial hero data from a data file.
  // CHECK if we need to initialize the cards by providing a starting hand to players.
  void render_world_ascii(); // Renders the world in ASCII, for debugging.
  void render_world_gui(); // Renders the world graphically.
  City& get_city(int city_id); // Returns City object corresponding to city_id.
  void infect_city(int city_id); // Calls City.infect(d_id).
  void shuffle_deck(stack<Card>& deck);
private:
  list<Hero> heroes;
  stack<Card> infection_deck;
  stack<Card> infection_discard;
  stack<Card> player_deck;
  stack<Card> player_discard;
  list<City> world_cities; // List of cities in the world.
  map<int, int> hero_locations;
  // Maps city_ids to hero_ids: tells you which cities has which heroes. No hero may be in more than one city.
  list<int> research_centres;
  // Which cities (by id) have research centres.
  int centres_remaining; // How many more research centres can be built.
};

#endif
