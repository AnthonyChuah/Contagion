#include "handwindow.h"
#include <QApplication>
#include <QPushButton>


#include <QProgressBar>
#include <QSlider>
#include <QMenu>


HandWindow::HandWindow(QWidget *parent,int height, int width) : QWidget(parent) {
    //Set the size of the window
    int win_wth=width;//256;
    int win_hth=height;//128;
    setFixedSize(win_wth, win_hth);


    // =========================================================== //
    // Create and position the CARD buttons
    // =========================================================== //

    // NOTE: should they be buttons? If so, would need to dynamically
    // determine the potential actions, so dynamically assign slots!
    int but_x=10;  // first button x-coord
    int but_y=20;  //button y-coord
    int but_gap=5; //gap between buttons
    int but_wth=(win_wth-2.0*but_x-6.0*but_gap)/7.0;
    int but_hth=but_wth*1.56; // playing card width/height ratio is 1:1.56
    int but_x_offset=but_wth+but_gap; //button x-offset
    int but_y_offset=(win_hth-but_y)/2.0; //button y-offset (2nd row)

    // PLACEHOLDER "CARDS"

    // First card
    card_button1 = new QPushButton("CARD 1", this);
    card_button1->setGeometry(but_x, but_y, but_wth, but_hth);
    card_button1->setToolTip("Opens a menu for special actions");
    card_button1->setCheckable(true);

    // Connection (signal to slot)
    connect(card_button1, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));


    // Seventh card
    card_button7 = new QPushButton("CARD 7", this);
    card_button7->setGeometry(but_x+6*but_x_offset, but_y, but_wth, but_hth);
    card_button7->setToolTip("Opens a menu for special actions");
    card_button7->setCheckable(true);

    // Connection (signal to slot)
    connect(card_button7, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));


    // Eighth card (new row)
    QPushButton *card_button8 = new QPushButton("CARD 8", this);
    card_button8->setGeometry(but_x, but_y+but_y_offset, but_wth, but_hth);
    card_button8->setToolTip("Opens a menu for special actions");
    card_button8->setCheckable(true);

    /*
    // =========================================================== //
    // Create and position the Exit button
    // =========================================================== //

    exit_button = new QPushButton("X", this);
    QFont font ("Courier");
    exit_button->setFont(font);
    //exit_button->setGeometry(win_wth/2-but_wth/2, win_hth/2+but_hth, but_wth, but_hth);
    exit_button->setGeometry(win_wth-22, 2, 18, 12);
    exit_button->setToolTip("Exits the application");

    // Connection (signal to slot)
    //connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
    connect(exit_button, SIGNAL (clicked()), this, SLOT (close()));
    */
}

void HandWindow::slotButtonClicked(bool checked) {
 if (checked) {
 card_button1->setText("Checked");
 } else {
 card_button1->setText("CARD 1");
 }
}

