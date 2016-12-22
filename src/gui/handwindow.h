#ifndef HANDWINDOW_H
#define HANDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QPoint>
#include <QList>

#include "cardwindow.h"
#include "cardsharewindow.h"
#include "macros.h"

class QPushButton; //to add a push button

class HandWindow : public QWidget {
    Q_OBJECT
public:
    explicit HandWindow(QWidget *parent = 0,int height = 180, int width = 180);

    // Function to update the hand to show the situation for a particular hero
    void update_window(Hero* hero);

    cardwindow* card_window;
    cardsharewindow* cardshare_window;

    void closeOverlays();
    //void close(); //overloaded close function

private slots:
    void slotButtonClicked(int buttonID);
    void shareClicked();

    void discardCard(std::string cardname);

    void useCard(PCard* card);
    void giveCard(PCard* card, Hero* to);

private:

    QList<QPushButton*> card_buttons;
    QButtonGroup* card_group;

    QPushButton* share_button;

    Hero* current_hero; //currently selected hero (may differ from current turn)

    void setupCardbuttons(int win_wth,int win_hth);

    //void discardCard(PCard* card, Hero* hero);
    //void useCard(PCard* card, Hero* hero);
    //void giveCard(PCard* card, Hero* from, Hero* to);

signals:
    void handButtonUp();
    void handLimit();

};

#endif // HANDWINDOW_H
