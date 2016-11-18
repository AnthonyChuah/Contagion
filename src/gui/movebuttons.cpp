#include "movebuttons.h"
#include "mainwindow.h"

movebuttons::movebuttons(QWidget *parent) : QWidget(parent) {


    // =========================================================== //
    // Control/action buttons
    // =========================================================== //
    int b_wth = 128; //button width
    int b_hth = 128; //button width
    int b_xcoord = 500; //button starting x-coordinage
    int b_xoffs = b_wth+20; //button x offset
    int b_ycoord = 750; //button y-coordinate


    // Move button
    //QPushButton *move_button = new QPushButton("MOVE", this);
    move_button = new QPushButton("MOVE", this);
    move_button->setGeometry(b_xcoord,b_ycoord,b_wth,b_hth);
    move_button->setToolTip("Move along the map");
    //move_button->setStyleSheet("border-image:url(../Contagion/images/pcard.jpg);");

    move_button->setCheckable(true);

    connect(move_button, SIGNAL (clicked(bool)), this, SLOT (moveButtonClicked(bool)));

    // Fly
    fly_button = new QPushButton("FLY", this);
    fly_button->setGeometry(b_xcoord+1*b_xoffs,b_ycoord,b_wth,b_hth);
    fly_button->setToolTip("Fly along the map");

    // Connection (signal to slot)
    connect(fly_button, SIGNAL (clicked(bool)), this, SLOT (flyButtonClicked(bool)));


    // Special action
    int spec_win_w = 600;
    int spec_win_h = spec_win_w*1.0/1.56;

    spec_window = new specialwindow(this,spec_win_h,spec_win_w);
    spec_window->move((win_w-spec_win_w)/2,(win_h-spec_win_h)/2);
    spec_window->close(); //for some reason the hand is automatically open o/w

    spec_button = new QPushButton("SPECIAL", this);
    spec_button->setGeometry(b_xcoord+2*b_xoffs,b_ycoord,b_wth,b_hth);
    spec_button->setToolTip("Hero's special action");

    spec_button->setCheckable(true);

    // Connection (signal to slot)
    connect(spec_button, SIGNAL (clicked(bool)), this, SLOT (specButtonClicked(bool)));

}


void movebuttons::moveButtonClicked(bool checked) {
 if (checked) {
 move_window->show();
 move_button->setText("CLOSE\nMOVE\nWINDOW");
 } else {
 move_window->close();
 move_button->setText("MOVE");
 }
}

void movebuttons::flyButtonClicked(bool checked) {
 if (checked) {
 move_window->show();
 fly_button->setText("CLOSE\nFLY\nWINDOW");
 } else {
 move_window->close();
 fly_button->setText("FLY");
 }
}


void movebuttons::specButtonClicked(bool checked) {
 if (checked) {
 spec_window->show();
 spec_button->setText("CLOSE\nSPECIAL");
 } else {
 spec_window->close();
 spec_button->setText("SPECIAL");
 }
}


