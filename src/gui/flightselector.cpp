#include "flightselector.h"
#include "mainwindow.h"

flightselector::flightselector(QWidget *parent) : QWidget(parent)
{
    int but_x=0;
    int but_y=0;
    int but_wth=50;
    int but_hth=but_wth;
    int x_off=5+but_wth;

    // Charter flight button
    charter_button = new QPushButton("Charter\nflight", this);
    charter_button->setGeometry(but_x, but_y, but_wth, but_hth);
    charter_button->setToolTip("Charter flight: discard the city card matching\n"
                               "your current city to fly anywhere.");
    connect(charter_button, SIGNAL (clicked()), this, SLOT (charterClicked()));

    // Direct flight button
    direct_button = new QPushButton("Direct\nflight", this);
    direct_button->setGeometry(but_x+x_off, but_y, but_wth, but_hth);
    direct_button->setToolTip("Direct flight: fly to a city matching a card in your\n"
                              "hand, discarding that city card in the process.");
    connect(direct_button, SIGNAL (clicked()), this, SLOT (directClicked()));

    // Shuttle flight button
    shuttle_button = new QPushButton("Shuttle\nflight", this);
    shuttle_button->setGeometry(but_x+2*x_off, but_y, but_wth, but_hth);
    shuttle_button->setToolTip("Shuttle flight: fly between cities with research centres.");
    connect(shuttle_button, SIGNAL (clicked()), this, SLOT (shuttleClicked()));

    // Operations Expert flight button
    opexflight_button = new QPushButton("OpEx\nflight", this);
    opexflight_button->setGeometry(but_x+2*x_off, but_y, but_wth, but_hth);
    opexflight_button->setToolTip("OpEx flight: once per turn, fly from a research centre\n"
                                  "to any destination by discarding any City card.");
    opexflight_button->setVisible(false);
    connect(opexflight_button, SIGNAL (clicked()), this, SLOT (opexflightClicked()));
}


void flightselector::charterClicked()
{
    emit flightSelection("charter");
}


void flightselector::directClicked()
{
    emit flightSelection("direct");
}


void flightselector::shuttleClicked()
{
    emit flightSelection("shuttle");
}


void flightselector::opexflightClicked()
{
    emit flightSelection("opexflight");
}


void flightselector::updateSelection()
{
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());
    int player = par->world->players_turn;
    std::string type = par->world->heroes[player]->get_spec();

    if(!type.compare("Operations Expert")) {
        opexflight_button->setVisible(true);
        shuttle_button->setVisible(false);
    } else {
        opexflight_button->setVisible(false);
        shuttle_button->setVisible(true);
    }
}
