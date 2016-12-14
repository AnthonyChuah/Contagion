#include "specialwindow.h"
#include <QApplication>
#include <QPushButton>

#include <QProgressBar>
#include <QSlider>
#include <QMenu>
#include <QDebug>

#include "mainwindow.h"
#include "macros.h"

specialwindow::specialwindow(QWidget *parent,int height, int width) : QWidget(parent)
{
    //Set the size of the window
    int win_wth=width;//256;
    int win_hth=height;//128;
    setFixedSize(win_wth, win_hth);


    // =========================================================== //
    // Create and position the CARD buttons
    // NOTE: should they be buttons? If so, would need to dynamically
    // determine the potential actions, so dynamically assign slots!
    int but_x=10;  // first button x-coord
    int but_y=20;  //button y-coord
    int but_hth=(win_hth-2.0*but_y);
    int but_wth=but_hth*1.0/1.56;
    int but_gap=win_wth-2*but_wth-2*but_x; //gap between buttons
    int but_x_offset=but_wth+but_gap; //button x-offset

    // First button
    // Dispatcher: Move any pawn to any city containing other pawn
    // Op Exp: build research station for free (not discarding a card)
    // Cont Planner: take event card from discard pile (to separate "slot", not hand)
    button1 = new QPushButton("SPEC 1", this);
    button1->setGeometry(but_x, but_y, but_wth, but_hth);
    button1->setToolTip("Opens a menu for special actions");

    // Connection (signal to slot)
    connect(button1, SIGNAL (clicked()), this, SLOT (slotSpec1Clicked()));


    // Second button
    // Dispatcher: Move another pawn as if its own
    // Op Exp: move from research station to any city by discarding any City card
    button2 = new QPushButton("SPEC 2", this);
    button2->setGeometry(but_x+but_x_offset, but_y, but_wth, but_hth);
    button2->setToolTip("Opens a menu to select which pawn to move.");

    // Connection (signal to slot)
    connect(button2, SIGNAL (clicked()), this, SLOT (slotSpec2Clicked()));
}

void specialwindow::update()
{
    // Get the parent (to get the world)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    int player = par->world->players_turn;
    Hero* hero = par->world->heroes[player];
    std::string type = hero->get_spec();

    // SET BUTTON TEXT
    if(!type.compare("Contingency Planner")) {
        button1->setText("TAKE EVENT CARD\nFROM DISCARD PILE");
        button1->setToolTip("Opens a menu to select cards from discard pile.");
        button2->setText("NOT\nAPPLICABLE FOR\nCONTINGENCY PLANNER");
        button2->setToolTip("No action available.");
    }
    else if(!type.compare("Dispatcher")) {
        button1->setText("MOVE ANY MEEPLE\nTO A CITY CONTAINING\nANOTHER MEEPLE");
        button1->setToolTip("Opens a menu to select a meeple to move.");

        button2->setText("MOVE ANOTHER\nMEEPLE");
        button2->setToolTip("Opens a menu to select which meeple to move.");
    }
    else if(!type.compare("Operations Expert")) {
        button1->setText("BUILD RESEARCH\nSTATION FOR FREE");
        button1->setToolTip("Builds a research station to current city.");

        button2->setText("MOVE FROM RESEARCH\nSTATION TO ANY CITY");
        button2->setToolTip("Opens a menu to select city to move to, and card to discard.");
    } else {
        button1->setText("NOT\nAPPLICABLE FOR\n"+QString::fromStdString(type));
        button1->setToolTip("No action available.");
        button2->setText("NOT\nAPPLICABLE FOR\n"+QString::fromStdString(type));
        button2->setToolTip("No action available.");
    }
}


void specialwindow::slotSpec1Clicked() {
    // Get the parent (to get the world)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    int player = par->world->players_turn;
    Hero* hero = par->world->heroes[player];
    std::string type = hero->get_spec();

    // SET ACTIONS
    if(!type.compare("Contingency Planner")) {
        qDebug() << "Cont Planner Spec 1 -- STUB\n";
    }
    else if(!type.compare("Dispatcher")) {
        qDebug() << "Dispatcher Spec 1 -- STUB\n";
    }
    else if(!type.compare("Operations Expert")) {
        qDebug() << "Op Exp Spec 1 -- STUB\n";
        // HAVE TO OPEN A SELECTION WINDOW that allows:
        // + selecting a place to fly to,
        // + what card to discard
        // After this, the function hero->opex_flight(city,card) is called
    }
}

void specialwindow::slotSpec2Clicked() {

    // Get the parent (to get the world)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    int player = par->world->players_turn;
    Hero* hero = par->world->heroes[player];
    std::string type = hero->get_spec();

    // SET ACTIONS
    if(!type.compare("Dispatcher")) {
        qDebug() << "Dispatcher Spec 2 -- STUB\n";
    }
    else if(!type.compare("Operations Expert")) {
        qDebug() << "Op Exp Spec 2 -- STUB\n";
    }
}
