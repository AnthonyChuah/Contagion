#ifndef MOVEWINDOW_H
#define MOVEWINDOW_H

#include <QWidget>
#include <QRadioButton>
#include <QPoint>
#include <QList>
#include <QButtonGroup>

#include <string>
#include <fstream>

#include "city.h"

class QRadioButton; //to add a radio button

class movewindow : public QWidget
{
    Q_OBJECT
public:
    explicit movewindow(QWidget *parent = 0,int height = 180, int width = 180);

private slots:
    void slotButtonClicked(int buttonID);
    void confirmHandler(bool confirm);

private:
    int win_wth;
    int win_hth;

    QRadioButton* city_button;
    QList<QRadioButton*> city_buttons; //list of radio buttons
    QButtonGroup* city_group;

    void createRadioButton(QRadioButton* button, int cid, std::string cname, int x, int y);
    void cityListSetup(std::string _filename,QButtonGroup* group);

    City* city_to = NULL;

signals:
    void closeOverlay();

public slots:
};

#endif // MOVEWINDOW_H
