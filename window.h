#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QPoint>

class QPushButton; //to add a push button

class Window : public QWidget {
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

private slots:
    void slotButtonClicked(bool checked);

    //void showContextMenu(const QPoint& pos);

private:
    QPushButton *spec_button; //special action
    QPushButton *exit_button; //exit

//signals:

//public slots:
};

#endif // WINDOW_H
