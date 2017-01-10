#include <QDebug>

#include "cardsharewindow.h"
#include "mainwindow.h"

cardsharewindow::cardsharewindow(QWidget *parent,int height, int width) : QWidget(parent)
{
    //Set the size of the window
    int win_wth=height;
    int win_hth=width;
    setFixedSize(win_wth,win_hth);

    // Get the parent (to get the world object)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    /* Hero buttons */
    // Set up the QList of Buttons for heroes
    hero_group = new QButtonGroup(this);
    setupHeroButtons();
    connect(hero_group,SIGNAL(buttonClicked(int)),this,SLOT(heroButtonSlot(int)));

    /* Card buttons */
    // Set up the QList of Buttons for cards
    card_group = new QButtonGroup(this);
    setupCardButtons();

    // Initialize the buttons to show the current player's cards
    int player = par->world->players_turn;
    updateCards(par->world->heroes[player]);

    // Connect signals -- using group, as provides button ID as parameter
    connect(card_group,SIGNAL(buttonClicked(int)),this,SLOT(cardButtonSlot(int)));


    /* Close window button */
    QPushButton* close_window = new QPushButton("X",this);
    close_window->setGeometry(win_wth-30,10,20,20);
    connect(close_window, SIGNAL (clicked()), this, SLOT (closeWindow()));
}


cardsharewindow::~cardsharewindow() {
    delete card_group;
    delete hero_group;
}


void cardsharewindow::setupHeroButtons()
{
    // Get the parent (to get the world object)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    int n_buttons=par->world->heroes.size();  //number of buttons created
    int but_x=10;  // first button x-coord
    int but_y=20;  //button y-coord
    int but_wth=250;
    int but_hth=50;
    int but_gap=(this->height()-2.0*but_x-n_buttons*(but_hth))/(n_buttons-1.0); //gap between buttons
    int but_y_offset=but_hth+but_gap;

    for(int i=0; i<n_buttons; i++) {
        QPushButton* a_button = new QPushButton(this);
        a_button->setGeometry(but_x,but_y+i*but_y_offset,but_wth,but_hth);
        a_button->setText("A hero");
        hero_buttons.append(a_button);

        // Add the button to the group, and set button ID
        hero_group->addButton(a_button);
        hero_group->setId(a_button, i);
    }
}


void cardsharewindow::setupCardButtons()
{
    int win_wth = this->width();
    int win_hth = this->height();
    int but_x=275;  // first button x-coord
    int but_y=20;  //button y-coord
    int but_gap=5; //gap between buttons
    //int but_hth=(win_hth-but_gap-2.0*but_y)/2.0;
    //int but_wth=but_hth/1.56;
    int but_wth=(win_wth-3.0*but_gap-275)/4.0;
    int but_hth=but_wth*1.56; // playing card width/height ratio is 1:1.56
    int but_x_offset=but_wth+but_gap; //button x-offset
    int but_y_offset=(win_hth-but_y)/2.0; //button y-offset (2nd row)

    int n_buttons=7;  //number of buttons created
    int row_len=4;    // length of a button row

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


void cardsharewindow::updateCards(Hero* hero)
{
    std::vector<PCard>::iterator card;
    int count=0;
    QString card_name;
    for(card=hero->hand.begin(); card != hero->hand.end(); card++) {
        card_name = QString::fromStdString(card->name);
        card_buttons[count]->setText(card_name);
        // ADD A CARD PICTURE (add from resources)

        // Card button only visible if the card is the same as the city,
        // OR the player is the Researcher
        if(card->city_id == hero->ptr_city->city_id) {
            card_buttons[count]->setVisible(true);
        } else if (hero->get_spec()=="Researcher" && card->event==false) {
            card_buttons[count]->setVisible(true);
        } else {
            card_buttons[count]->setVisible(false);
        }
        count++;
    }

    for(int i=count; i!=card_buttons.length();i++) {
        card_buttons[i]->setVisible(false);
    }

}


void cardsharewindow::updateHeroes(Hero* hero)
{
    qDebug() << "Updating heroes in same city for hero" << QString::fromStdString(hero->get_spec()) <<"\n";

    mainWindow* par = qobject_cast<mainWindow*>(this->parent());
    City *city = hero->ptr_city;
    std::vector<int>::iterator it_hero = city->heroes.begin();
    int n_heroes = par->world->heroes.size();//city->heroes.size();
    int unresolved_idx=0; //next unresolved button
    while(it_hero!=city->heroes.end()) {
        for(int i=unresolved_idx; i<n_heroes; i++) {
            if(par->world->heroes[i]->hero_id == *it_hero) {
                hero_buttons[i]->setText("");
                hero_buttons[i]->setIcon(QIcon(setHeroPicture(par->world->heroes[i])));
                hero_buttons[i]->setIconSize(QSize(250,50));
                hero_buttons[i]->setContentsMargins(0,0,0,0);
                if(hero==par->world->heroes[i]) {
                    hero_buttons[i]->setVisible(false);
                    qDebug() << "Hiding hero button " << i << "(1)\n";
                } else {
                    hero_buttons[i]->setVisible(true);
                    qDebug() << "Showing hero button " << i << "\n";
                }
                unresolved_idx=i+1;
            } else {
                hero_buttons[i]->setVisible(false);
                qDebug() << "Hiding hero button " << i << "(2)\n";
            }
        }
        it_hero++;
    }
}


QString cardsharewindow::setHeroPicture(Hero* hero)
{
    std::string type = hero->get_spec();

    // SET PICTURE
    if(!type.compare("Contingency Planner"))
        return ":/images/cont_planner_turn_bevel.png";
    else if(!type.compare("Dispatcher"))
        return ":/images/dispatcher_turn_bevel.png";
    else if(!type.compare("Medic"))
        return ":/images/medic_turn_bevel.png";
    else if(!type.compare("Operations Expert"))
        return ":/images/op_exp_turn_bevel.png";
    else if(!type.compare("Quarantine Specialist"))
        return ":/images/quar_spec_turn_bevel.png";
    else if(!type.compare("Researcher"))
        return ":/images/researcher_turn_bevel.png";
    else //if(!type.compare("Scientist"))
        return ":/images/scientist_turn_bevel.png";
}


void cardsharewindow::hideCards()
{
    for(int i=0; i!=card_buttons.length();i++) {
        card_buttons[i]->setVisible(false);
    }
}


void cardsharewindow::closeWindow()
{
    emit cardshareOverlayClosed();
    this->close();
}


void cardsharewindow::heroButtonSlot(int buttonID)
{
    // Get the parent (to get the world object)
    mainWindow* par = qobject_cast<mainWindow*>(this->parent());

    //Find out which hero button was clicked, and set "a_card" pointer to it
    selected_hero = par->world->heroes[buttonID];

    updateCards(selected_hero);

    emit heroClickedSignal(selected_hero);
}


void cardsharewindow::cardButtonSlot(int buttonID)
{
    //Find out which card button was clicked, and set "a_card" pointer to it
    PCard a_card = selected_hero->hand[buttonID];

    //Emit a signal to take the card
    emit takeButtonSignal(&a_card, selected_hero);
    this->closeWindow();
}
