#include "disinfectwindow.h"

#include <QDebug>

disinfectwindow::disinfectwindow(QWidget *parent,int height, int width) : QWidget(parent) {
    //Set the size of the window
    int win_wth=width;//256;
    int win_hth=height;//128;
    setFixedSize(win_wth, win_hth);

    int but_x=10;  // first button x-coord
    int but_y=20;  //button y-coord
    int but_gap=5; //gap between buttons
    int but_wth=(win_wth-2.0*but_x-6.0*but_gap)/7.0;
    int but_hth=but_wth*1.56; // playing card width/height ratio is 1:1.56
    int but_x_offset=but_wth+but_gap; //button x-offset
    int but_y_offset=(win_hth-but_y)/2.0; //button y-offset (2nd row)

    // Disease 0
    d0_button = new QPushButton("DISEASE 0", this);
    d0_button->setGeometry(but_x+3*but_x_offset, but_y+but_y_offset, but_wth*2, but_hth);
    d0_button->setToolTip("Selects disease 1 to be treated");

    connect(d0_button, SIGNAL (clicked()), this, SLOT (d0_buttonClicked()));

    // Disease 1
    d1_button = new QPushButton("DISEASE 1", this);
    d1_button->setGeometry(but_x+3*but_x_offset, but_y+but_y_offset, but_wth*2, but_hth);
    d1_button->setToolTip("Selects disease 1 to be treated");

    connect(d1_button, SIGNAL (clicked()), this, SLOT (d1_buttonClicked()));

    // Disease 2
    d2_button = new QPushButton("DISEASE 2", this);
    d2_button->setGeometry(but_x+3*but_x_offset, but_y+but_y_offset, but_wth*2, but_hth);
    d2_button->setToolTip("Selects disease 2 to be treated");

    connect(d2_button, SIGNAL (clicked()), this, SLOT (d2_buttonClicked()));

    // Disease 3
    d3_button = new QPushButton("DISEASE 3", this);
    d3_button->setGeometry(but_x+3*but_x_offset, but_y+but_y_offset, but_wth*2, but_hth);
    d3_button->setToolTip("Selects disease 3 to be treated");

    connect(d3_button, SIGNAL (clicked()), this, SLOT (d3_buttonClicked()));

}


void disinfectwindow::show(bool d0,bool d1,bool d2,bool d3) {
    if(!d0)
        d0_button->setDown(true);
    if(!d1)
        d1_button->setDown(true);
    if(!d2)
        d2_button->setDown(true);
    if(!d3)
        d3_button->setDown(true);

    this->QWidget::show();
}




void disinfectwindow::d0_buttonClicked() {
    qDebug() << "Treat disease 0. \n";

    // Emit the disinfect signal
    //emit treat_d0;
    emit treat(0);

    // Set the buttons up again
    buttonsUp();

    // Close the disinfect window
    this->close();
}

void disinfectwindow::d1_buttonClicked() {
    qDebug() << "Treat disease 1. \n";

    // Emit the disinfect signal
    //emit treat_d1;
    emit treat(1);

    // Set the buttons up again
    buttonsUp();

    // Close the disinfect window
    this->close();
}

void disinfectwindow::d2_buttonClicked() {
    qDebug() << "Treat disease 2. \n";

    // Emit the disinfect signal
    //emit treat_d2;
    emit treat(2);

    // Set the buttons up again
    buttonsUp();

    // Close the disinfect window
    this->close();
}

void disinfectwindow::d3_buttonClicked() {
    qDebug() << "Treat disease 3. \n";

    // Emit the disinfect signal
    //emit treat_d3;
    emit treat(3);

    // Set the buttons up again
    buttonsUp();

    // Close the disinfect window
    this->close();
}

void disinfectwindow::buttonsUp() {
    d0_button->setDown(false);
    d1_button->setDown(false);
    d2_button->setDown(false);
    d3_button->setDown(false);
}
