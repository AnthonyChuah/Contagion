#include <QDebug>
#include <QString>

#include "flywindow.h"
#include "mainwindow.h"

//flywindow::flywindow(QWidget *parent, int height, int width) : QWidget(parent), movewindow(parent,height,width)
flywindow::flywindow(QWidget *parent, int height, int width) : movewindow(parent,height,width)
{
    // Get the parent (to get the main window ptr)
    main_window = qobject_cast<mainWindow*>(this->flywindow::parent());
    world = main_window->world;
}


void flywindow::update_cities(std::string flight_type)
{
    Hero *hero = world->heroes[world->players_turn];
    std::vector<PCard>::iterator it;

    if(!flight_type.compare("charter")) {
        current_flight_type="charter";
        // Check if hand contains the current city, for charter flight
        bool charter=false;
        for(it=hero->hand.begin(); it!=hero->hand.end(); it++) {
            if(it->city_id==hero->ptr_city->city_id)
                charter=true;
        }
        if(charter) {
            for(int i=0; i<=47; i++) {
                city_group->button(i)->setVisible(true);
            }
        } else {
            for(int i=0; i<=47; i++) {
                city_group->button(i)->setVisible(false);
            }
            qDebug() <<"Charter flight selected, but not applicable.\n";
        }
    } else if(!flight_type.compare("direct")) {
        current_flight_type="direct";
        for(int i=0; i<=47; i++) {
            city_group->button(i)->setVisible(false);
        }
        // Direct flight: cities where the player has cards for
        for(it=hero->hand.begin(); it!=hero->hand.end(); it++) {
            if(it->city_id!=-1)
                city_group->button(it->city_id)->setVisible(true);
        }
    } else if(!flight_type.compare("shuttle")) {
        current_flight_type="shuttle";
        // Shuttle flight: cities with research centres, if applicable
        for(int i=0; i<=47; i++) {
            city_group->button(i)->setVisible(false);
        }
        if(hero->ptr_city->has_rc()) {
            for(it=hero->hand.begin(); it!=hero->hand.end(); it++) {
                qDebug() << "BUG!! City " << world->cities[it->city_id].city_id <<"\n";
                //if(world->cities[it->city_id].has_rc()) {
                //    city_group->button(it->city_id)->setVisible(true);
                //}
            }
        }
    } else if(!flight_type.compare("opexflight")) {
        current_flight_type="opexflight";
        // OpEx flight: all cities, if in a city with a research centre
        if(hero->ptr_city->has_rc()) {
            for(int i=0; i<=47; i++) {
                city_group->button(i)->setVisible(true);
            }
        } else {
            for(int i=0; i<=47; i++) {
                city_group->button(i)->setVisible(false);
            }
        }
    }
}


void flywindow::confirmHandler(bool confirm)
{
    if(confirm) {
      qDebug() << "Flight confirmed.\n";

      // Fly the Hero to the new city (if valid)
      int player = world->players_turn;
      if(!current_flight_type.compare("charter")) {
        if(world->heroes[player]->charter_flight(*city_to,world->heroes[player])) {
            main_window->meeples[player]->moveCity(city_to);
            qDebug() << "Charter flight\n";
            emit flightSuccess();
        }
      } else if(!current_flight_type.compare("direct")) {
        if(world->heroes[player]->direct_flight(*city_to,world->heroes[player])) {
            main_window->meeples[player]->moveCity(city_to);
            qDebug() << "Direct flight\n";
            emit flightSuccess();
        }
      } else if(!current_flight_type.compare("shuttle")) {
          if(world->heroes[player]->shuttle_flight(*city_to,world->heroes[player])) {
            main_window->meeples[player]->moveCity(city_to);
            qDebug() << "Shuttle flight \n";
            emit flightSuccess();
          }
      } else if(!current_flight_type.compare("opexflight")) {
          // TO DO: Must implement a selection window allowing to select a card to
          //        discard
          //if(world->heroes[player]->opex_flight(*city_to,world->heroes[player])) {
          //  main_window->meeples[player]->moveCity(city_to);
            qDebug() << "Opex flight -- WIP, implement card selection!\n";
          //  emit flightSuccess();
          //}
      } else {
        qDebug() << "Flight failed\n";
      }

      // Emit signal to close the overlay
      emit closeOverlay();

      // Update the action display
      main_window->action_lcd->check_actions();
    } else {
      qDebug() << "Move cancelled.\n";
    }
    // Uncheck the selected city button
    city_group->setExclusive(false);
    city_group->checkedButton()->setChecked(false);
    city_group->setExclusive(true);

    // Return city_to to point to null
    city_to=NULL;
}
