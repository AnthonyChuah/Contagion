#ifndef WORLD_H
#define WORLD_H

/*
Header file for World class.
The World object should contain everything we need:
1. All cities.
2. All heroes (players).
3. All cards on the board in the four piles.
4. How many research centres still available to be built.
Thus, all objects contained in the world can easily refer to other objects in the same world.
Note: for now everything to be public, but later we can move them and use accessor functions instead.
*/

class World
{
public:
  World();
  void load_city_data(char filename[]); // Loads the initial city data from a data file.
  void load_cards_data(char filename[]); // Loads the initial cards data from a data file.
  void load_hero_data(char filename[]); // Loads the initial hero data from a data file.
  // CHECK if we need to initialize the cards by providing a starting hand to players.
  void render_world_ascii(); // Renders the world in ASCII, for debugging.
  void render_world_gui(); // Renders the world graphically.
  City& get_city(int city_id); // Returns City object corresponding to city_id.
  void infect_city(int city_id); // Calls City.infect(d_id).
  void shuffle_deck(stack<Card>& deck); // Shuffles a deck of cards (stack data structure).
  list<Hero> heroes; // List containing objects of class Hero, generated at the start of the game.
  stack<Card> infection_deck; // Stack containing cards, populated at the start of the game.
  stack<Card> infection_discard; // Stack containing the infection discard pile, initially empty.
  stack<Card> player_deck; // Stack containing the player cards, populated at the start of the game.
  stack<Card> player_discard; // Player discard pile, initially empty.
  list<City> cities; // List of cities in the world.
  int centres_remaining; // How many more research centres can be built.
};

#endif
