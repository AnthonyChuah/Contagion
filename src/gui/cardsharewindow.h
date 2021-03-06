#ifndef CARDSHAREWINDOW_H
#define CARDSHAREWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QPixmap>
#include <QString>

#include "macros.h"

class cardsharewindow : public QWidget
{
    Q_OBJECT
public:
    explicit cardsharewindow(QWidget *parent = 0,int wth=640, int hth=480);
    ~cardsharewindow();

    void updateCards(Hero* hero);
    void updateHeroes(Hero* hero);
    void hideCards();

private:
    Hero* selected_hero;

    QList<QPushButton*> hero_buttons;
    QButtonGroup* hero_group;

    QList<QPushButton*> card_buttons;
    QButtonGroup* card_group;

    void setupHeroButtons();
    void setupCardButtons();

    QString setHeroPicture(Hero* hero);

private slots:
    void heroButtonSlot(int buttonID);
    void cardButtonSlot(int buttonID);

signals:
    void cardshareOverlayClosed();
    void takeButtonSignal(PCard* card, Hero* from);
    void heroClickedSignal(Hero* hero);

public slots:
    void closeWindow();
};

#endif // CARDSHAREWINDOW_H
