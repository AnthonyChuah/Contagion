This is a game shadowing the Pandemic board game in terms of mechanics.

Pandemic's rules are found here: http://www.zmangames.com/uploads/4/7/1/7/47170931/pandemic.pdf

This repository contains a .jpg file which shows the Pandemic board. It is useful to refer to it when programming this game.


Design of the objects in this program:

**World**

* World represents a single on-going game, similar to the board in Pandemic, and contains:
    * A list of Hero objects, which will be generated from a text data file
    * A list of City objects, which will be generated from a text data file
    * 2 stacks of PCard objects, one is the player card pile and one is the discard pile
    * 2 stacks of ICard objects, one is the infection card pile and one is the discard pile
    * A counter showing how many more research centres (RCs) can be built
    * The statuses of the four diseases in the world
    * The number of disease blocks not yet placed upon cities
    * Number of outbreaks that have happened so far
    * The infection rate at the moment
* The World can take as a parameter the number of epidemics in the PCard deck: this sets the difficulty
* World also has many functions to enable gameplay, there are too many to enumerate here

**City**

* City represents a node on the board (see PandemicMap.jpg), and contains:
    * A list of neighbouring cities by their unique ID
    * Array representing how many disease cubes are on the city at the moment
    * Boolean showing if RC has been built here
    * Integer representing which disease (colour) the city produces
* City has various functions to enable gameplay that are not enumerated here
* Remember that World::cities is a list of City objects

** Hero **

* Hero represents the player character moving around saving the world, and Hero has functions that correspond to what players can do in Pandemic:
    * Move to adjacent cities
    * Disinfect current city
    * Fly to cities
    * Build RCs
* Hero also contains a list of Cards in their hand, representing the player cards in a player's hand
* Remember that World::heroes is a list of Hero objects

** Player Card **

* PCard represents player cards, and are found in the two stack of PCards data structures in World
* PCard can also be taken into a player's hands
* PCard can also be an Epidemic Card, which triggers the World::epidemic function and then disappears from the game

** Infection Card **

* ICard represents infection cards, and are found in the two stack of ICards data structures in World
