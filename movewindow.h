#ifndef MOVEWINDOW_H
#define MOVEWINDOW_H

#include <QWidget>
#include <QRadioButton>
#include <QPoint>
#include <QList>
#include <QButtonGroup>

#include <string>
#include <fstream>

class QRadioButton; //to add a radio button

class movewindow : public QWidget
{
    Q_OBJECT
public:
    explicit movewindow(QWidget *parent = 0,int height = 180, int width = 180);

private slots:
    //void slotButtonClicked(bool checked);

private:
    QRadioButton* city_button;
    QList<QRadioButton*> city_buttons; //list of radio buttons
    QButtonGroup* city_group;

    void createRadioButton(QRadioButton* button, int cid, std::string cname, int x, int y);
    void cityListSetup(std::string _filename);

signals:

public slots:
};

#endif // MOVEWINDOW_H
