#ifndef MOVEWINDOW_H
#define MOVEWINDOW_H

#include <QWidget>
#include <QRadioButton>
#include <QPoint>
#include <QList>
#include <QFile>
#include <QButtonGroup>

#include <string>
#include <fstream>

#include "city.h"

class QRadioButton; //to add a radio button

class movewindow : public QWidget {
    Q_OBJECT
public:
    explicit movewindow(QWidget *parent = 0,int height = 180, int width = 180);

private slots:
    void slotButtonClicked(int buttonID);
    void confirmHandler(bool confirm);

protected:
    int win_wth;
    int win_hth;

    QRadioButton* city_button;
    QList<QRadioButton*> city_buttons; //list of radio buttons
    QButtonGroup* city_group;

    void createRadioButton(QRadioButton* button, int cid, std::string cname, int x, int y);

    void cityListSetup(QButtonGroup* city_group);

    City* city_to = NULL;

signals:
    void closeOverlay();

};


// =========================================================== //
// HELPER FUNCTION FOR CONVERTING COORDINATES
// =========================================================== //
void convertXY(double& x_coord, double& y_coord);


#endif // MOVEWINDOW_H
