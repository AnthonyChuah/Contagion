#ifndef HANDWINDOW_H
#define HANDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QPoint>

class QPushButton; //to add a push button

class HandWindow : public QWidget {
    Q_OBJECT
public:
    explicit HandWindow(QWidget *parent = 0,int height = 180, int width = 180);

private slots:
    void slotButtonClicked(bool checked);

    //void showContextMenu(const QPoint& pos);

private:
    QPushButton *card_button1; //card button 1 (placeholders for cards)
    QPushButton *card_button7; //card button 7 (placeholders for cards)
    QPushButton *exit_button; //exit

//signals:

//public slots:
};

#endif // HANDWINDOW_H
