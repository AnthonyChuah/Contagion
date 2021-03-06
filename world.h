#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include <deque>

#include "macros.h"
#include "city.h"
#include "world.h"
#include "hero.h"
#include "pcard.h"
#include "icard.h"

// --------------------------- MACROS ----------------------------------- //
// Disease status
//#define UNCURED 0
//#define CURED 1
//#define ERADICATED 2
// ---------------------------------------------------------------------- //

/*
Header file for World class.
The World object should contain everything we need:
1. All cities.
2. All heroes (players).
3. All cards on the board in the four piles.
4. How many research centres still available to be built.
Thus, all objects contained in the world can easily refer to other objects in the same world.
Note: for now everything to be public, but later we can move them and use accessor functions instead.

World initialization rules:
0. The constructor will automatically set the disease statuses, number of disease cubes, etc.
1. Load all the cities and populate their data EXCEPT for which Heroes are in which city.
   Generate all the neighbours of all the cities.
   Atlanta should always be the first city in the data file.
1. Together with the city loading, the infection cards should all be loaded too (since they correspond to cities).
2. Load all the player cards from data file (the data file will NOT include epidemics).
3. Load all the heroes from the data file, and initialize their locations to Atlanta.
3. Update also Atlanta so that it contains the Heroes.
4. Draw player cards for the heroes depending on the number of players:
   2 cards each for 4 players, 3 for 3, 4 for 2 players.
5. Do the initial infections of the 9 cities: 3 counters each for 3, 2 for the next 3, 1 for next 3.
*/

class World;

class World
{
public:
  World();
  World(int _epidemics);
  ~World();
  void load_city_data(std::string _filename); // Loads the initial city data from a data file.
  // Note: Atlanta should be the first city in the list, and Atlanta must start with a research centre.
  // Note: infection card data is drawn from the city data file.
  void load_eventcards_data(std::string _filename); // Loads the event cards.
  void load_hero_data(std::string _filename); // Loads the initial hero data from a data file.
  void setup(); // Set up the world according to the rules.
  // CHECK if we need to initialize the cards by providing a starting hand to players.
  void draw_infection_deck(); // Draws 2 to 4 cards from the infection deck.
  void draw_player_deck(Hero& hero); // Deals to player card from the player deck: discard cards above 7.
  void epidemic(); // An epidemic occurs: see game rules.
  bool check_eradication(int _did);
  bool play_event_card(Hero& _hero, std::string _event, std::string _arguments);
  bool event_grant(std::string _arguments); // Playing the Government Grant event card.
  void event_forecast(); // Forecast Event card, allows players to re-arrange infection deck.
  bool event_resilient(std::string _arguments);
  void event_airlift(std::string _arguments);
  void clear_outbreak_flags(); // Outbreak flags are meant to prevent infinite chains of outbreak between cities.
  // The flags immunize a city from further infection, but must be cleared ASAP.
  void game_loop(); // MAIN GAME LOOP.
  bool victory();
  void death(std::string _message);
  // These functions require interaction with the User Interface (.gui and .tui).
  void render_world_ascii(); // Renders the world in ASCII, for debugging.
  void next_player_turn();
  void display_city(int _cid);
  void display_player_discard();
  void display_infection_discard();
  void display_hands(); // Displays all players' hands.
  void render_world_gui(); // Renders the world graphically.
  bool handle_input(std::string _input);
  std::vector<Hero*> heroes; // Vector containing pointers of class Hero, generated at the start of the game.
  std::deque<ICard> infection_deck; // Vector containing cards, populated at the start of the game.
  std::vector<ICard> infection_discard; // Vector containing the infection discard pile, initially empty.
  std::vector<PCard> player_deck; // Vector containing the player cards, populated at the start of the game.
  std::vector<PCard> player_discard; // Player discard pile, initially empty.
  std::vector<City> cities; // Vector of cities in the world.
  void init(); // Helper function for constructors.
  bool skip_next_infect_cities;
  int centres_remaining; // How many more research centres can be built.
  int outbreaks; // Counts the number of outbreaks: you lose once outbreaks >= 8.
  int disease_status[4]; // Shows each disease's status: 0 for uncured, 1 for cured, 2 for eradicated.
  int disease_blocks[4]; // Shows how many disease blocks of each colour remain on the board.
  int players_turn; // The index of the player whose turn it is.
  int num_cities;
  int num_players; // Number of players in the world.
  int calculate_infection_rate(); // Calculate infection rate.
  int infection_rate_base; // A base value for infection rate, used to calculate the infection rate.
  int num_epidemics; // Number of epidemics to be inserted into player card deck.
  int ui_width;
  int ui_height;

  //void game_loop_gui(); // game loop for GUI
};

#endif
