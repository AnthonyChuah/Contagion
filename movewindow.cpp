#include "movewindow.h"
#include <QApplication>
#include <QRadioButton>
#include <QFile>
#include <QList>
#include <QButtonGroup>
#include <QDebug>

#include <string>
#include <sstream>
#include <fstream>

movewindow::movewindow(QWidget *parent,int height, int width) : QWidget(parent) {
    //Set the size of the window
    int win_wth=width;//256;
    int win_hth=height;//128;
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
    cityListSetup("../Contagion/cities.dat");
    qDebug() << "City list setup done.\n";

    // Add the buttons to a group (NOTE - NOT NECESSARILY NEEDED!)
    city_group = new QButtonGroup(this);
    foreach(QRadioButton* button, city_buttons) {
      city_group->addButton(button);
    }


}


void movewindow::cityListSetup(std::string _filename) {
    //Multipliers for x and y coordinates
    int x_multip=1600;
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
      x_conv = x_multip*xcoord;      y_conv = y_multip*ycoord-100;

      // Create the QList of RadioButtons
      QRadioButton* a_city_button = new QRadioButton(this);
      createRadioButton(a_city_button,cityid,cityname,x_conv,y_conv);
      city_buttons.append(a_city_button);
    }
    ins.close();
    qDebug() << "Button list creation finished.\n";

}

void movewindow::createRadioButton(QRadioButton* button, int cid, std::string cname, int x, int y) {
    // Radio button rectangle (background) size
    int radio_wth=30;
    int radio_hth=radio_wth;
    const char * city = cname.c_str();

    qDebug() << "Creating city:" << city << ", id:" << cid << ", x:" << x << ", y:" << y << "\n";
    button->setGeometry(x,y,radio_wth,radio_hth); //sets location and size of rectangle
    //button->setText(cname);
}
