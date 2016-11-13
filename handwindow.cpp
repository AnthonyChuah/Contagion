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

    /*
    // Background picture
    QPixmap bkgnd("../Contagion/images/World_map_concept_coloured.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
*/

    // =========================================================== //
    // Create and position the CARD buttons
    // NOTE: should they be buttons? If so, would need to dynamically
    // determine the potential actions, so dynamically assign slots!
    int but_x=10;  // first button x-coord
    int but_y=20;  //button y-coord
    int but_gap=5; //gap between buttons
    int but_wth=(win_wth-2.0*but_x-6.0*but_gap)/7.0;
    int but_hth=but_wth*1.56/1.0;
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



    // =========================================================== //
    // Context menu
    //setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));
    //connect(spec_button, SIGNAL (clicked(bool)), this, SLOT(showContextMenu(const QPoint&)));


    // =========================================================== //
    // Create and position the Exit button
    exit_button = new QPushButton("X", this);
    QFont font ("Courier");
    exit_button->setFont(font);
    //exit_button->setGeometry(win_wth/2-but_wth/2, win_hth/2+but_hth, but_wth, but_hth);
    exit_button->setGeometry(win_wth-22, 2, 18, 12);
    exit_button->setToolTip("Exits the application");

    // Connection (signal to slot)
    //connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
    connect(exit_button, SIGNAL (clicked()), this, SLOT (close()));


    /*
    // =========================================================== //
    // Create a progress bar
    QProgressBar *progressBar = new QProgressBar(this);
    int prb_wth=180;
    int prb_hth=30;
    progressBar->setRange(0,100); //ranges from 0 to 100
    progressBar->setValue(0);
    progressBar->setGeometry((win_wth-prb_wth)/2,win_hth/2-prb_hth,prb_wth,prb_hth);

    // Create a horizontal slider
    QSlider *slider = new QSlider(this);
    int sli_wth=180;
    int sli_hth=30;
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0,100);
    slider->setValue(0);
    slider->setGeometry((win_wth-sli_wth)/2,win_hth/2,sli_wth,sli_hth);

    // Connection: progress bar and slider
    QObject::connect(slider, SIGNAL (valueChanged(int)), progressBar, SLOT (setValue(int)));
*/
}

void HandWindow::slotButtonClicked(bool checked) {
 if (checked) {
 card_button1->setText("Checked");
 } else {
 card_button1->setText("CARD 1");
 }
}

/*
void HandWindow::showContextMenu(const QPoint& pos) // this is a slot
{
    // for most widgets
    //QPoint globalPos = window->mapToGlobal(pos);
    QPoint globalPos = this->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("Menu Item 1");
    // ...

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        // something was chosen, do stuff
    }
    else
    {
        // nothing was chosen
    }
}
*/
