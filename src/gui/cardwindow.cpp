#include "cardwindow.h"
#include <QDebug>

cardwindow::cardwindow(QWidget *parent,int height, int width) : QWidget(parent) {
    //Set the size of the window
    int win_wth=width;//256;
    int win_hth=height;//128;
    setFixedSize(win_wth, win_hth);

    // DESIGN -- a window with a large picture of the card shown, and
    //           buttons for "use", "give" and "discard" below the picture

    // =========================================================== //
    // CARD PICTURE
    // =========================================================== //

    qDebug() << "CARD PICTURE TO BE ADDED \n";


    // =========================================================== //
    // BUTTONS
    // =========================================================== //
    int b_xcoord=10;  // first button x-coord
    int b_ycoord=40;  //button y-coord
    int b_gap=5; //gap between buttons
    int b_wth=(win_wth-2.0*b_xcoord-2.0*b_gap)/3.0;
    int b_hth=b_wth*1.56; // playing card width/height ratio is 1:1.56
    int b_xoffs=b_wth+b_gap; //button x-offset

    // Use button
    use_button = new QPushButton("USE", this);
    use_button->setGeometry(b_xcoord,b_ycoord,b_wth,b_hth);
    use_button->setToolTip("Use the card");
    connect(use_button, SIGNAL (clicked()), this, SLOT (useButtonSlot()));

    // Give button
    give_button = new QPushButton("GIVE", this);
    give_button->setGeometry(b_xcoord+1*b_xoffs,b_ycoord,b_wth,b_hth);
    give_button->setToolTip("Give the card to another player");
    connect(give_button, SIGNAL (clicked()), this, SLOT (giveButtonSlot()));

    // Discard button
    discard_button = new QPushButton("DISCARD", this);
    discard_button->setGeometry(b_xcoord+2*b_xoffs,b_ycoord,b_wth,b_hth);
    discard_button->setToolTip("Discard the card");
    connect(discard_button, SIGNAL (clicked()), this, SLOT (discardButtonSlot()));


    // Close window button
    QPushButton* close_window = new QPushButton("X",this);
    close_window->setGeometry(win_wth-30,10,20,20);
    connect(close_window, SIGNAL (clicked()), this, SLOT (close()));

}


void cardwindow::discardButtonSlot() {
    emit discardButtonSignal(current_card);
    qDebug() << "Discard button signal emitted \n";

    emit cardOverlayClosed();
    this->close();
}

void cardwindow::giveButtonSlot() {
    qDebug() << "Give button pressed -- STUB \n";

    // Need to implement a selection of players to give it to

    //emit giveButtonSignal(current_card, hero_to);

    emit cardOverlayClosed();
    this->close();
}

void cardwindow::useButtonSlot() {
    emit useButtonSignal(current_card);
    qDebug() << "Use button signal emitted \n";

    emit cardOverlayClosed();
    this->close();
}

void cardwindow::update_window(Hero *hero, PCard *card) {
    current_hero = hero;
    current_card = card;

    // Use button only usable if card is an event card
    if(card->event==false) {
        //use_button->setDown(true);
        use_button->setVisible(false);
    } else {
        //use_button->setDown(false);
        use_button->setVisible(true);
    }

    // Give button only clickable if more than one hero in city
    if(hero->ptr_city->heroes.size()==1) {
        //give_button->setDown(true);
        give_button->setVisible(false);
    } else {
        //give_button->setDown(false);
        give_button->setVisible(true);
    }

    qDebug() << "Card window updated \n";

}
