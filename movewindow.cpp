#include "movewindow.h"
#include <QApplication>
#include <QRadioButton>
#include <QFile>
#include <QList>
#include <QButtonGroup>
#include <QDebug>
#include "confirmwindow.h"

#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

movewindow::movewindow(QWidget *parent,int height, int width) : QWidget(parent) {
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
    // BUTTONS
    // =========================================================== //

    // Sample, for debugging
    /*
    // Radio button rectangle (background) size
    int radio_wth=30;
    int radio_hth=radio_wth;

    QRadioButton* cityButton = new QRadioButton(this);
    cityButton->setGeometry(500,500,radio_wth,radio_hth); //sets location and size of rectangle
    cityButton->setText("San Francisco");
    */

    // =========================================================== //
    // BUTTON CREATION FROM LIST
    // =========================================================== //

    // Set up the QList of Radio Buttons
    city_group = new QButtonGroup(this);
    cityListSetup("../Contagion/cities.dat",city_group);
    //cityListSetup("../Contagion/cities.dat");
    qDebug() << "City list setup done.\n";

/*
    // Add the buttons to a group (NOTE - NOT NECESSARILY NEEDED!)
    city_group = new QButtonGroup(this);
    foreach(QRadioButton* button, city_buttons) {
      city_group->addButton(button);
    }
*/

    // =========================================================== //
    // SIGNAL HANDLING
    // =========================================================== //
    // Using group
    connect(city_group,SIGNAL(buttonClicked(int)),this,SLOT(slotButtonClicked(int)));

    // Using the QList
    //foreach(QRadioButton* button, city_buttons) {
    //    connect(button,SIGNAL(clicked()),this,SLOT(slotButtonClicked()));
    //}
    // The list approach has a problem - in theory you can get a pointer to
    // the signalling button using "sender()", but it gives a pointer of the
    // wrong type (QObject), which cannot be converted correctly.
}


//void movewindow::cityListSetup(std::string _filename) {
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
    //find out which city button clicked
    qDebug() << "City button for city " << buttonID << " was clicked.\n";

    //when city button clicked, make a check if move valid
    // if not valid, exit the function

    //open a confirmation window asking to confirm move
    int conf_win_w = win_wth; int conf_win_h = win_hth;
    QString infotext = "Confirm move to city "+QString::number(buttonID)+"?";
    confirmwindow* confirm_window = new confirmwindow(this,infotext,conf_win_h,conf_win_w);
    confirm_window->move((win_wth-conf_win_w)/2,(win_hth-conf_win_h)/2);
    confirm_window->show();
    connect(confirm_window,SIGNAL(confirmSignal(bool)),this,SLOT(confirmHandler(bool)));


    // move the Hero to the new city (if valid)


}

void movewindow::confirmHandler(bool confirm) {
    if(confirm) {
      qDebug() << "Move confirmed.\n";

      // Emit signal to close to overlay
      emit closeOverlay();
      // (normal "this->close()" does not inform the move mainwindow correctly)
      //this->close();
    } else {
      qDebug() << "Move cancelled.\n";

      // Emit signal to close to overlay
      //emit closeOverlay();
    }
    // Uncheck the selected city button
    city_group->setExclusive(false);
    city_group->checkedButton()->setChecked(false);
    city_group->setExclusive(true);
}
