#include "window.h"
#include <QApplication>
#include <QPushButton>


#include <QProgressBar>
#include <QSlider>
#include <QMenu>


Window::Window(QWidget *parent) : QWidget(parent) {
    //Set the size of the window
    int win_wth=256;
    int win_hth=128;
    setFixedSize(win_wth, win_hth);

    setStyleSheet("background-image:url(\"PandemicMap.jpg\"); background-position:center; ");

    // =========================================================== //
    // Create and position the Special action button
    int but_wth=100;
    int but_hth=30;
    spec_button = new QPushButton("Special action", this);
    spec_button->setGeometry(win_wth/2-but_wth/2, win_hth/2+but_hth, but_wth, but_hth);
    spec_button->setToolTip("Opens a menu for special actions");

    spec_button->setCheckable(true);

    // Connection (signal to slot)
    connect(spec_button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));


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
    connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));


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

}

void Window::slotButtonClicked(bool checked) {
 if (checked) {
 spec_button->setText("Checked");
 } else {
 spec_button->setText("Spec action");
 }
}

/*
void Window::showContextMenu(const QPoint& pos) // this is a slot
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
