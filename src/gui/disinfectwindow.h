#ifndef DISINFECTWINDOW_H
#define DISINFECTWINDOW_H

#include <QWidget>
#include <QPushButton>

class disinfectwindow : public QWidget
{
    Q_OBJECT
public:
    explicit disinfectwindow(QWidget *parent = 0,int height = 180, int width = 180);

    void show(bool d0,bool d1,bool d2,bool d3);

private:
    QPushButton* d0_button;
    QPushButton* d1_button;
    QPushButton* d2_button;
    QPushButton* d3_button;

    void buttonsUp();

signals:
    //void treat_d0();
    //void treat_d1();
    //void treat_d2();
    //void treat_d3();

    void treat(int d);

public slots:
    void d0_buttonClicked();
    void d1_buttonClicked();
    void d2_buttonClicked();
    void d3_buttonClicked();
};

#endif // DISINFECTWINDOW_H
