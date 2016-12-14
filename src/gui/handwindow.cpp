#include "handwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QDebug>
#include <QProgressBar>
#include <QSlider>
#include <QMenu>

#include "mainwindow.h"


HandWindow::HandWindow(QWidget *parent,int height, int width) : QWidget(parent) {
    //Set the size of the window
    int win_wth=width;//256;
    int win_hth=height;//128;
    setFixedSize(win_wth, win_hth);

    // Get the parent (to get the world)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());


    // Set up the card window
    int cw_hth=180;     int cw_wth=180;
    card_window = new cardwindow(par,cw_hth,cw_wth);
    card_window->move((par->win_w-cw_wth)/2,(par->win_h-cw_hth)/2);
    card_window->close();

    // =========================================================== //
    // Create and position the CARD buttons
    // =========================================================== //

    // Set up the QList of Buttons
    card_group = new QButtonGroup(this);
    setupCardbuttons(win_wth,win_hth);

    // Initialize the buttons to show the first player's cards
    int player = par->world->players_turn;
    update_window(par->world->heroes[player]);

    // =========================================================== //
    // SIGNAL HANDLING
    // =========================================================== //
    // Using group, as provides button ID as parameter
    connect(card_group,SIGNAL(buttonClicked(int)),this,SLOT(slotButtonClicked(int)));

}


void HandWindow::setupCardbuttons(int win_wth,int win_hth) {
    int but_x=10;  // first button x-coord
    int but_y=20;  //button y-coord
    int but_gap=5; //gap between buttons
    int but_wth=(win_wth-2.0*but_x-6.0*but_gap)/7.0;
    int but_hth=but_wth*1.56; // playing card width/height ratio is 1:1.56
    int but_x_offset=but_wth+but_gap; //button x-offset
    int but_y_offset=(win_hth-but_y)/2.0; //button y-offset (2nd row)

    int n_buttons=14; //number of buttons created
    int row_len=7;    // length of a button row

    qDebug() << "Setting up card buttons";

    for(int i=0; i<n_buttons; i++) {
        QPushButton* a_button = new QPushButton(this);
        if(i<row_len) {
            a_button->setGeometry(but_x+i*but_x_offset,but_y,but_wth,but_hth);
        } else {
            a_button->setGeometry(but_x+(i-row_len)*but_x_offset,but_y+but_y_offset,but_wth,but_hth);
        }
        a_button->setText("Button");
        card_buttons.append(a_button);

        // Add the button to the group, and set button ID
        card_group->addButton(a_button);
        card_group->setId(a_button, i);
    }
}

void HandWindow::update_window(Hero* hero) {

    // Update the current_hero pointer
    current_hero=hero;

    std::vector<PCard>::iterator it;
    int count=0;
    QString card_name;
    for(it=hero->hand.begin(); it != hero->hand.end(); it++) {
        card_name = QString::fromStdString(it->name);
        card_buttons[count]->setText(card_name);
        // ADD A CARD PICTURE (add from resources)
        if(!it->event) { //if not an event card, i.e. is a city card
            card_buttons[count]->setDown(true); //cities non-clickable
          //  it->city_id;
        }
        count++;
    }

    for(int i=count; i!=card_buttons.length();i++) {
        card_buttons[i]->setVisible(false);
    }

}

/*
// Overloaded close() function
// NOTE: The QWidget::close() version has to be used when card window opened!
//       This is because the hand limit would be checked again, before there
//       is a chance to discard any cards.
void HandWindow::close() {

    // Close the window
    this->QWidget::close();
    qDebug() << "Hand window closed. \n";

    // Check hand limit, and emit signal if too many cards
    qDebug() << "Checking hand limit. \n";
    if(current_hero->hand.size() > 7) {
        emit handLimit();
    }

    // Test
    emit handLimit();
}
// SOME BUGS REMAIN, with regard to the graphics view opening on top after
   handLimit() is emitted...
   -- REVIEW IF IT'S IMPORTANT TO CHECK HAND LIMIT AFTER CLOSE
*/

//void HandWindow::discardCard(PCard* card, Hero* hero) {
void HandWindow::discardCard(PCard* card) {
    qDebug() << QString::fromStdString(card->name) << " : Discard card function -- STUB \n";
}

//void HandWindow::useCard(PCard* card, Hero* hero) {
void HandWindow::useCard(PCard* card) {
    qDebug() << QString::fromStdString(card->name) << " : Use card function -- STUB \n";
}

//void HandWindow::giveCard(PCard *card, Hero *from, Hero *to) {
void HandWindow::giveCard(PCard *card, Hero *to) {
    qDebug() << QString::fromStdString(card->name) << " : Give card function -- STUB \n";
    //current_hero->give_card(card->name,*to);
}


void HandWindow::slotButtonClicked(int buttonID) {
    // Get the parent (to get the world)
    //mainWindow* parent = qobject_cast<mainWindow*>(this->parent());

    //Find out which card button was clicked, and set "a_card" pointer to it
    //QPushButton* a_button = card_buttons[buttonID];
    PCard a_card = current_hero->hand[buttonID];

    // Update the card window
    card_window->update_window(current_hero,&a_card);

    // Open the card window
    qDebug() << "Open the card selection window";
    card_window->show();

    // Emit signal to raise the HAND button again
    emit handButtonUp();
}

