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
  World(int epidemics);
  void load_city_data(char filename[]); // Loads the initial city data from a data file.
  // Note: Atlanta should be the first city in the list, and Atlanta must start with a research centre.
  void load_icards_data(char filename[]); // Loads the initial infection cards data from a data file.
  void load_pcards_data(char filename[]); // Loads the initial player cards data from a data file.
  void load_hero_data(char filename[]); // Loads the initial hero data from a data file.
  // CHECK if we need to initialize the cards by providing a starting hand to players.
  void render_world_ascii(); // Renders the world in ASCII, for debugging.
  void render_world_gui(); // Renders the world graphically.
  City& get_city(int city_id); // Returns City object corresponding to city_id.
  void infect_city(int city_id); // Calls City.infect(d_id).
  void shuffle_deck(stack<ICard>& deck); // Shuffles a deck of cards (stack data structure).
  void draw_infection_deck(Hero& hero); // Draws a card from the infection deck.
  void draw_player_deck(Hero& hero); // Draws cards from the player deck: discard cards above 7.
  void epidemic(); // An epidemic occurs.
  list<Hero> heroes; // List containing objects of class Hero, generated at the start of the game.
  stack<ICard> infection_deck; // Stack containing cards, populated at the start of the game.
  stack<ICard> infection_discard; // Stack containing the infection discard pile, initially empty.
  stack<PCard> player_deck; // Stack containing the player cards, populated at the start of the game.
  stack<PCard> player_discard; // Player discard pile, initially empty.
  list<City> cities; // List of cities in the world.
  int centres_remaining; // How many more research centres can be built.
  int outbreaks; // Counts the number of outbreaks: you lose once outbreaks >= 8.
  int disease_status[4]; // Shows each disease's status: 0 for uncured, 1 for cured, 2 for eradicated.
  int disease_blocks[4]; // Shows how many disease blocks of each colour remain on the board.
  int players_turn; // The index of the player whose turn it is.
  int num_players; // Number of players in the world.
  int calculate_infection_rate(); // Calculate infection rate.
  int infection_rate_base; // A base value for infection rate, used to calculate the infection rate.
  int num_epidemics; // Number of epidemics in the world.
};

#endif
