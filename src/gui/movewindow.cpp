#include "movewindow.h"
#include <QApplication>
#include <QRadioButton>
#include <QFile>
#include <QList>
#include <QButtonGroup>
#include <QDebug>
#include "mainwindow.h"

#include "confirmwindow.h"


#include "city.h"
#include "world.h"

#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

movewindow::movewindow(QWidget *parent, int height, int width) : QWidget(parent) {
    //Set the size of the window
    win_wth=width;
    win_hth=height;
    setFixedSize(win_wth, win_hth);

    // =========================================================== //
    // Load the style sheet
    // =========================================================== //
    QFile file("../Contagion/resources/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    this->setStyleSheet(styleSheet);

    // =========================================================== //
    // BUTTON CREATION FROM DATA FILE
    // =========================================================== //
    // Set up the QList of Radio Buttons
    city_group = new QButtonGroup(this);
    cityListSetup("../Contagion/cities.dat",city_group);
    //cityListSetup("../Contagion/cities.dat");
    qDebug() << "City list setup done.\n";


    // =========================================================== //
    // SIGNAL HANDLING
    // =========================================================== //
    // Using group
    connect(city_group,SIGNAL(buttonClicked(int)),this,SLOT(slotButtonClicked(int)));

}


void movewindow::cityListSetup(std::string _filename,QButtonGroup* city_group) {
    //Multipliers for x and y coordinates
    int x_multip=1500;//1600; //1600 is correct size, but projection off
    int y_multip=900;
    int x_conv,y_conv; //converted x and y coords

    std::ifstream ins;
    ins.open(_filename);
    if (ins.fail()) {
    qDebug() << "Failed to open city input file.\n";
    //  std::cerr << "Failed to open city input file.\n";
    //  exit(1);
    }

    std::string rowdata;

    // First line of data file is just headers, drop them.
    std::getline(ins, rowdata);

    while(ins.good()) {
      std::getline(ins, rowdata);

      // If rowdata is simply empty (last line) then continue.
      if (rowdata.empty()) continue;

      // Split by comma delimiter to get data, split neighbours by colon delimiter.
      std::stringstream ss(rowdata);
      std::string item;
      std::vector<std::string> elems;
      while (std::getline(ss, item, ','))
        elems.push_back(item);

      // CityID,CityName,XCoordinate,YCoordinate,DiseaseID,Neighbours
      // 0,Atlanta,0.196666666666667,0.617196702002356,2,4:8:10
      int cityid;
      std::string cityname;
      double xcoord, ycoord;
      cityid = std::stoi(elems[0]);  cityname = elems[1];
      xcoord = std::stod(elems[2]);  ycoord = std::stod(elems[3]);
      x_conv = x_multip*xcoord;      y_conv = y_multip*(1-ycoord)-35;

      // Create the QList of RadioButtons
      QRadioButton* a_city_button = new QRadioButton(this);
      createRadioButton(a_city_button,cityid,cityname,x_conv,y_conv);
      city_buttons.append(a_city_button);

      // Add the city to the group
      city_group->addButton(a_city_button);
      city_group->setId(a_city_button, cityid);
    }
    ins.close();
    qDebug() << "Button list creation finished.\n";

}

void movewindow::createRadioButton(QRadioButton* button, int cid, std::string cname, int x, int y) {
    // Radio button rectangle (background) size
    int radio_wth=100;
    int radio_hth=30;//radio_wth;
    const char * city = cname.c_str();

    qDebug() << "Creating city:" << city << ", id:" << cid << ", x:" << x << ", y:" << y << "\n";
    button->setGeometry(x,y,radio_wth,radio_hth); //sets location and size of rectangle
    button->setText(city);
}


void movewindow::slotButtonClicked(int buttonID) {
    // Get the parent (to get the world)
    mainWindow* parent = qobject_cast<mainWindow*>(this->parent());

    //Find out which city button was clicked, and set "city_to" pointer to it
    //qDebug() << "City button for city " << buttonID << " was clicked.\n";
    city_to = new City();

    std::vector<City>::iterator it;
    for(it=parent->world->cities.begin();it != parent->world->cities.end();it++) {
        if(it->city_id==buttonID) {
            city_to = &(*it);
            break;
        }
        //else {
            //qDebug() << "No city" << buttonID << " found.\n";
        //}
    }

    //Make a check if move valid
    // if not valid, exit the function
    // NOTE: THE Hero::move() function does a check!

    //Open a confirmation window asking to confirm move
    int conf_win_w = win_wth; int conf_win_h = win_hth;
    //QString infotext = "Confirm move to city "+QString::number(buttonID)+"?";
    QString cityname = QString::fromStdString(city_to->name);
    QString infotext = "Confirm move to "+cityname+"?";
    confirmwindow* confirm_window = new confirmwindow(this,infotext,conf_win_h,conf_win_w);
    confirm_window->move((win_wth-conf_win_w)/2,(win_hth-conf_win_h)/2);
    confirm_window->show();
    connect(confirm_window,SIGNAL(confirmSignal(bool)),this,SLOT(confirmHandler(bool)));

}

void movewindow::confirmHandler(bool confirm) {
    // Get the parent (to get the world)
    mainWindow* parent = qobject_cast<mainWindow*>(this->parent());

    if(confirm) {
      qDebug() << "Move confirmed.\n";

      // move the Hero to the new city (if valid)
      int player = parent->world->players_turn;
      parent->world->heroes[player]->move(*city_to,parent->world->heroes[player]);

      //DEBUG PART
      QString at_city = QString::fromStdString(parent->world->heroes[player]->ptr_city->name);
      qDebug() << "Hero is now at city" << at_city << ".\n";

      // Update the action display
      //parent->action_lcd->display(parent->world->heroes[parent->world->players_turn]->moves);
      parent->action_lcd->check_actions();

      // Emit signal to close the overlay
      emit closeOverlay();

    } else {
      qDebug() << "Move cancelled.\n";
      // Emit signal to close to overlay
      //emit closeOverlay();
    }
    // Uncheck the selected city button
    city_group->setExclusive(false);
    city_group->checkedButton()->setChecked(false);
    city_group->setExclusive(true);

    // Return city_to to point to null
    city_to=NULL;
}
