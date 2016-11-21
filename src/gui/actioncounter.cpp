#include "actioncounter.h"
#include "mainwindow.h"

#include <QDebug>

actioncounter::actioncounter(QWidget *parent) : QLCDNumber(parent) {
    // Get the parent (to get the world)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    // =========================================================== //
    // ACTIONS remaining LCD number
    // =========================================================== //
    this->display(par->world->heroes[par->world->players_turn]->moves);
    this->setGeometry(1900/2-25,20,100,50);
    //this->setSegmentStyle(QLCDNumber::Flat);
    //this->setAutoFillBackground(true);
    this->setPalette(Qt::transparent);

}


void actioncounter::check_actions() {
    // Get the parent (to get the world)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    this->display(par->world->heroes[par->world->players_turn]->moves);

    if(this->intValue()==0) {
        qDebug() << "Emitting 'noActions'.\n";
        emit noActions();
    }
}
