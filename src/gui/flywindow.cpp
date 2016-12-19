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


void flywindow::update_cities()
{
    Hero *hero = world->heroes[world->players_turn];

    qDebug() << "Flight -- WIP, have to allow choice of charter vs direct flight!\n";

    // Check if hand contains the current city, for charter flight
    std::vector<PCard>::iterator it;
    bool charter=false;
    for(it=hero->hand.begin(); it!=hero->hand.end(); it++) {
        if(it->city_id==hero->ptr_city->city_id)
            charter=true;
    }

    // Set visible city buttons -- all if charter==true, otherwise only
    // those matching a card in the player's hand
    if(charter) {
        for(int i=0; i<=47; i++) {
            city_group->button(i)->setVisible(true);
        }
    } else {
        for(int i=0; i<=47; i++) {
            city_group->button(i)->setVisible(false);
        }
        // Direct flight: cities where the player has cards for
        for(it=hero->hand.begin(); it!=hero->hand.end(); it++) {
            if(it->city_id!=-1)
                city_group->button(it->city_id)->setVisible(true);
        }
        // Shuttle flight: cities with research centres, if applicable
        if(hero->ptr_city->has_rc()) {
            for(it=hero->hand.begin(); it!=hero->hand.end(); it++) {
                if(world->cities[it->city_id].has_rc())
                    city_group->button(it->city_id)->setVisible(true);
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
      if(world->heroes[player]->charter_flight(*city_to,world->heroes[player])) {
        main_window->meeples[player]->moveCity(city_to);
        qDebug() << "Charter flight \n";
        emit flightSuccess();
      }
      else if(world->heroes[player]->direct_flight(*city_to,world->heroes[player])) {
        main_window->meeples[player]->moveCity(city_to);
        qDebug() << "Direct flight \n";
        emit flightSuccess();
      }
      else if(world->heroes[player]->shuttle_flight(*city_to,world->heroes[player])) {
        main_window->meeples[player]->moveCity(city_to);
        qDebug() << "Shuttle flight \n";
        emit flightSuccess();
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
