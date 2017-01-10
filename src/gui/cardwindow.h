#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "macros.h"

#include "cardsharewindow.h"

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
    std::string curr_card;

    cardsharewindow* cardshare_window;

signals:
    void discardButtonSignal(std::string str);

    void giveButtonSignal(std::string card_name, Hero* to);
    void useButtonSignal(PCard* card);

    void cardOverlayClosed();

private slots:
    void discardButtonSlot();
    void giveButtonSlot();
    void useButtonSlot();
    void closeWindow();
    void giveHeroSlot(Hero* hero);
};

#endif // CARDWINDOW_H
