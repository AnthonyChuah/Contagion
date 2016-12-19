#ifndef FLYWINDOW_H
#define FLYWINDOW_H

#include <QWidget>
//#include "mainwindow.h"
#include "movewindow.h"

class mainWindow;
//class movewindow;

class flywindow : public movewindow {
    Q_OBJECT
public:
    explicit flywindow(QWidget *parent = 0,int height = 180, int width = 180);
    //explicit flywindow(movewindow *parent = 0,int height = 180, int width = 180);
    void update_cities();

private:
    World *world;
    mainWindow* main_window;

private slots:
    void confirmHandler(bool confirm);

signals:
    void flightSuccess();

public slots:
};

#endif // FLYWINDOW_H
