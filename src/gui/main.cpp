#include <QApplication>
#include <QFont>
#include <QGraphicsView>
#include "handwindow.h"
#include "mainwindow.h"
#include <iostream>

#include <macros.h>

int main(int argc, char **argv) {
 QApplication app (argc, argv);


 // =========================================================== //
 // Setup - TO BE CHANGED TO USE A SETUP WINDOW!!!
 // =========================================================== //

 int number_of_epidemics = 4;
 World new_world(number_of_epidemics);
 new_world.load_city_data("../Contagion/cities.dat");
 new_world.load_eventcards_data("../Contagion/eventcards.dat");
 new_world.load_hero_data("../Contagion/heroes.dat");
 new_world.setup();


 // =========================================================== //
 // Main window
 // =========================================================== //
 //mainWindow mainWind();
 mainWindow mainWind(&new_world);
 mainWind.show();
 //mainWindow* mainWind = new mainWindow();
 //mainWind->show();


 return app.exec();

}

