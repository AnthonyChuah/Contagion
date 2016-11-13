#include "specialwindow.h"
#include <QApplication>
#include <QPushButton>


#include <QProgressBar>
#include <QSlider>
#include <QMenu>

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
    //int but_y_offset=(win_hth-but_y)/2.0; //button y-offset (2nd row)

    // PLACEHOLDER "CARDS"

    // First card
    button1 = new QPushButton("SPEC 1", this);
    button1->setGeometry(but_x, but_y, but_wth, but_hth);
    button1->setToolTip("Opens a menu for special actions");
    button1->setCheckable(true);

    // Connection (signal to slot)
    connect(button1, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));


    // Seventh card
    button2 = new QPushButton("SPEC 2", this);
    button2->setGeometry(but_x+but_x_offset, but_y, but_wth, but_hth);
    button2->setToolTip("Opens a menu for special actions");
    button2->setCheckable(true);

    // Connection (signal to slot)
    connect(button2, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));


}

void specialwindow::slotButtonClicked(bool checked) {
 if (checked) {
 button1->setText("Checked");
 } else {
 button1->setText("CARD 1");
 }
}

