#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "macros.h"

class cardwindow : public QWidget {
    Q_OBJECT
public:
    explicit cardwindow(QWidget *parent = 0,int height = 180, int width = 180);

    void update_window(Hero* hero, PCard* card);

private:
    QPushButton* discard_button;
    QPushButton* give_button;
    QPushButton* use_button;

    Hero *current_hero;
    PCard *current_card;

signals:
    void discardButtonSignal(PCard* card);
    void giveButtonSignal(PCard* card, Hero* to);
    void useButtonSignal(PCard* card);

    void cardOverlayClosed();

private slots:
    void discardButtonSlot();
    void giveButtonSlot();
    void useButtonSlot();

};

#endif // CARDWINDOW_H
