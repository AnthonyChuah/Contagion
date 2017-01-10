#include <QApplication>
#include <QPushButton>
#include <QDebug>
#include <QShortcut>

#include "handwindow.h"
#include "mainwindow.h"

HandWindow::HandWindow(QWidget *parent,int height, int width) : QWidget(parent)
{
    //Set the size of the window
    int win_wth=width; //256;
    int win_hth=height;//128;
    setFixedSize(win_wth, win_hth);

    // Get the parent (to get the world object)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    // =========================================================== //
    // Card window and card buttons
    // =========================================================== //
    // Set up the card window
    int cw_hth=180;     int cw_wth=180;
    card_window = new cardwindow(par,cw_hth,cw_wth);
    card_window->move((par->win_w-cw_wth)/2,(par->win_h-cw_hth)/2);
    card_window->close();

    // Set up the QList of Buttons for cards
    card_group = new QButtonGroup(this);
    setupCardbuttons(win_wth,win_hth);

    // Initialize the buttons to show the first player's cards
    int player = par->world->players_turn;
    update_window(par->world->heroes[player]);

    // TODO: Add contingency planner's special card slot here?

    // SIGNAL HANDLING
    // Using group, as provides button ID as parameter
    connect(card_group,SIGNAL(buttonClicked(int)),this,SLOT(slotButtonClicked(int)));
    connect(card_window,SIGNAL(discardButtonSignal(std::string)),this,SLOT(discardCard(std::string)));
    connect(card_window,SIGNAL(giveButtonSignal(std::string,Hero*)),this,SLOT(giveCard(std::string,Hero*)));

    // =========================================================== //
    // Card share window and share cards - button
    // =========================================================== //
    int cs_wth=640; int cs_hth=300;
    cardshare_window = new cardsharewindow(par,cs_wth,cs_hth);
    cardshare_window->move((par->win_w-cs_wth)/2,(par->win_h-cs_hth)/2);
    cardshare_window->close();

    int but_wth = 150;
    share_button = new QPushButton("TAKE CARDS",this);
    share_button->setGeometry((win_wth-but_wth)/2,win_hth-50,but_wth,40);
    share_button->setToolTip("Take cards from another player in the same city.");
    connect(share_button,SIGNAL(clicked()),this,SLOT(shareClicked()));
    connect(cardshare_window,SIGNAL(takeButtonSignal(PCard*, Hero*)),this,SLOT(takeCardSlot(PCard*,Hero*)));


    QShortcut *closeshortcut = new QShortcut(QKeySequence("x"),this);
    connect(closeshortcut,SIGNAL(activated()),this,SLOT(closeShortcut()));
}


void HandWindow::setupCardbuttons(int win_wth,int win_hth)
{
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


void HandWindow::update_window(Hero* hero)
{
    // Update the current_hero pointer
    current_hero=hero;

    std::vector<PCard>::iterator it;
    int count=0;
    QString card_name;
    for(it=hero->hand.begin(); it != hero->hand.end(); it++) {
        card_name = QString::fromStdString(it->name);
        card_buttons[count]->setText(card_name);
        // ADD A CARD PICTURE (add from resources)
        card_buttons[count]->setVisible(true);
        count++;
    }

    for(int i=count; i!=card_buttons.length();i++) {
        card_buttons[i]->setVisible(false);
    }
}


void HandWindow::discardCard(std::string cardname)
{
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());
    int player = par->world->players_turn;

    // Push the card to discard pile, and remove from hand
    std::vector<PCard>::iterator it = par->world->heroes[player]->hand.begin();
    while(it != par->world->heroes[player]->hand.end()) {
        if(!cardname.compare(it->name)) {
            par->world->player_discard.push_back(*it);
            par->world->heroes[player]->hand.erase(it);
            break;
        }
        it++;
    }
    update_window(par->world->heroes[player]);
}


void HandWindow::useCard(PCard* card)
{
    qDebug() << QString::fromStdString(card->name) << " : Use card function -- STUB \n";
}


void HandWindow::giveCard(std::string card_name, Hero *to)
{
    qDebug() << QString::fromStdString(card_name) << " : Give card function -- STUB \n";
    current_hero->give_card(card_name,*to);
    update_window(current_hero);
}


void HandWindow::closeOverlays()
{
    card_window->close();
    cardshare_window->close();
}


void HandWindow::slotButtonClicked(int buttonID)
{
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


void HandWindow::shareClicked()
{
    // Update the card share window
    cardshare_window->updateHeroes(current_hero);
    cardshare_window->hideCards();

    // Open the card window
    qDebug() << "Open the card share window";
    cardshare_window->show();

    // Emit signal to raise the HAND button again
    emit handButtonUp();
}


void HandWindow::takeCardSlot(PCard* card,Hero* from)
{
    current_hero->take_card(card->name,*from);
    update_window(current_hero);
}


void HandWindow::closeShortcut()
{
    this->close();
    emit handShortcutClose();
}
