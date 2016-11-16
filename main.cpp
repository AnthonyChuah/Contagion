#include <QApplication>
#include <QFont>
#include <QGraphicsView>
#include "handwindow.h"
#include "mainwindow.h"
#include <iostream>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 mainWindow mainWind;

 mainWind.show();


 return app.exec();

}

