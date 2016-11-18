#include <QtWidgets>
#include <iostream>
#include "mainwindow.h"
#include "handwindow.h"
#include "movewindow.h"
#include "transpbutton.h"
#include "world.h"

//mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {
mainWindow::mainWindow(World* wrld) : world(wrld) { //with no parent
    /*
    // =========================================================== //
    // WORLD Setup - TO BE CHANGED TO USE A SETUP WINDOW!!!
    // =========================================================== //
    int number_of_epidemics = 4;
    world = new World(number_of_epidemics);
    world->load_city_data("../Contagion/cities.dat");
    world->load_eventcards_data("../Contagion/eventcards.dat");
    world->load_hero_data("../Contagion/heroes.dat");
    world->setup();
    // =========================================================== //
    */

    QDir::setCurrent(QCoreApplication::applicationDirPath());


    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    //REMOVE infoLabel? WILL NEED TO CHECK WHEN TIME, BUT SEEMS UNNECESSARY
    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);



    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("Menus"));
    int win_w = 1600;
    int win_h =900;
    //setMinimumSize(160, 160);
    resize(win_w, win_h);

    // Background picture
    QPixmap bkgnd("../Contagion/images/World_map_concept_coloured.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    // =========================================================== //
    // STATUS BAR
    // =========================================================== //
    QMainWindow::statusBar()->showMessage(tr("Ready"));

    // The status bar should be made to have permanent widgets
    // and text boxes that track:
    //  - whose turn it is (player name/number)
    //  - what hero class the player is
    //  - how many actions the player has left
    //  - etc



    // =========================================================== //
    // Load the style sheet
    // =========================================================== //
    QFile file("../Contagion/resources/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    this->setStyleSheet(styleSheet);


    // =========================================================== //
    // CARD DECK BUTTONS
    // =========================================================== //

    // Button size and placement
    int card_wth = 128;
    int card_hth = 176;
    int card_xcoord = 975;
    int card_xoffset = card_wth+20;
    int card_ycoord = 700;

    // Push button for player card
    QPushButton *PCard_button = new QPushButton("PLAYER", this);
    PCard_button->setGeometry(card_xcoord,card_ycoord,card_wth,card_hth);
    PCard_button->setToolTip("Draws a player card");
    //PCard_button->setStyleSheet("border-image:url(../Contagion/images/pcard.jpg);");

    // Push button for infection card
    QPushButton *ICard_button = new QPushButton("INFECTION", this);
    ICard_button->setGeometry(card_xcoord+1*card_xoffset,card_ycoord,card_wth,card_hth);
    ICard_button->setToolTip("Draws an Infection card");

    // Connection (signal to slot)
    //connect(ICard_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));


    // =========================================================== //
    // INFECTION RATE progress bar
    // =========================================================== //
    QProgressBar *iprogBar = new QProgressBar(this);
    int iprb_wth=300;
    int iprb_hth=40;
    iprogBar->setRange(1,7); //ranges from 1 to 7
    iprogBar->setValue(1);
    iprogBar->setGeometry(win_w-iprb_wth-20,20,iprb_wth,iprb_hth);
    //NEED TO ADD THE THING THAT TAKES THE INFECTION RATE IN...


    // =========================================================== //
    // OUTBREAKS progress bar
    // =========================================================== //
    QProgressBar *oprogBar = new QProgressBar(this);
    int oprb_wth=40;
    int oprb_hth=300;
    int oprb_xcoord = 40;
    int oprb_ycoord = win_h-oprb_hth-20;
    oprogBar->setOrientation(Qt::Vertical);
    oprogBar->setTextDirection(QProgressBar::BottomToTop);
    oprogBar->setRange(0,8); //step values range: 0-8
    oprogBar->setValue(0);
    oprogBar->setGeometry(oprb_xcoord,oprb_ycoord,oprb_wth,oprb_hth);

    // =========================================================== //
    // ACTIONS remaining LCD number
    // =========================================================== //
    action_lcd = new QLCDNumber(this);
    action_lcd->display(world->heroes[world->players_turn]->moves);
    action_lcd->setGeometry(win_w/2-25,20,100,50);
    //action_lcd->setSegmentStyle(QLCDNumber::Flat);
    //action_lcd->setAutoFillBackground(true);
    action_lcd->setPalette(Qt::transparent);
    action_lcd->show();


    // =========================================================== //
    // DISEASES progress bars
    int dis_prb_wth=50;
    int dis_prb_hth=50;
    int dis_prb_xcoord = oprb_xcoord + oprb_wth + 40;
    int dis_prb_ycoord = oprb_ycoord;
    int dis_offset = (oprb_hth - 4.0*dis_prb_hth)/3.0 + dis_prb_hth;

    QProgressBar *disProg1 = new QProgressBar(this);
    disProg1->setRange(0,2); //step values range: 0-2
    disProg1->setValue(0);
    disProg1->setGeometry(dis_prb_xcoord,dis_prb_ycoord,dis_prb_wth,dis_prb_hth);

    QProgressBar *disProg2 = new QProgressBar(this);
    disProg2->setRange(0,2); //step values range: 0-2
    disProg2->setValue(0);
    disProg2->setGeometry(dis_prb_xcoord,dis_prb_ycoord+dis_offset,dis_prb_wth,dis_prb_hth);

    QProgressBar *disProg3 = new QProgressBar(this);
    disProg3->setRange(0,2); //step values range: 0-2
    disProg3->setValue(0);
    disProg3->setGeometry(dis_prb_xcoord,dis_prb_ycoord+2*dis_offset,dis_prb_wth,dis_prb_hth);

    QProgressBar *disProg4 = new QProgressBar(this);
    disProg4->setRange(0,2); //step values range: 0-2
    disProg4->setValue(0);
    disProg4->setGeometry(dis_prb_xcoord,dis_prb_ycoord+3*dis_offset,dis_prb_wth,dis_prb_hth);

    // =========================================================== //
    // Control/action buttons
    // =========================================================== //

    int b_wth = 128; //button width
    int b_hth = 128; //button width
    int b_xcoord = 500; //button starting x-coordinage
    int b_xoffs = b_wth+20; //button x offset
    int b_ycoord = 750; //button y-coordinate

    // Fly
    fly_button = new QPushButton("FLY", this);
    fly_button->setGeometry(b_xcoord+1*b_xoffs,b_ycoord,b_wth,b_hth);
    fly_button->setToolTip("Fly along the map");
    fly_button->setCheckable(true);

    // Connection (signal to slot)
    connect(fly_button, SIGNAL (clicked(bool)), this, SLOT (flyButtonClicked(bool)));

    // Special action
    int spec_win_w = 600;
    int spec_win_h = spec_win_w*1.0/1.56;

    spec_window = new specialwindow(this,spec_win_h,spec_win_w);
    spec_window->move((win_w-spec_win_w)/2,(win_h-spec_win_h)/2);
    spec_window->close(); //for some reason the hand is automatically open o/w

    spec_button = new QPushButton("SPECIAL", this);
    spec_button->setGeometry(b_xcoord+2*b_xoffs,b_ycoord,b_wth,b_hth);
    spec_button->setToolTip("Hero's special action");
    spec_button->setCheckable(true);

    // Connection (signal to slot)
    connect(spec_button, SIGNAL (clicked(bool)), this, SLOT (specButtonClicked(bool)));

    // Move button
    //QPushButton *move_button = new QPushButton("MOVE", this);
    move_button = new QPushButton("MOVE", this);
    move_button->setGeometry(b_xcoord,b_ycoord,b_wth,b_hth);
    move_button->setToolTip("Move along the map");
    //move_button->setStyleSheet("border-image:url(../Contagion/images/pcard.jpg);");
    move_button->setCheckable(true);

    // Connection (signal to slot)
    connect(move_button, SIGNAL (clicked(bool)), this, SLOT (moveButtonClicked(bool)));

    // =========================================================== //
    // MOVE WINDOW OVERLAY
    // =========================================================== //

    move_window = new movewindow(this,win_h-150,win_w);
    move_window->close(); //for some reason the hand is automatically open o/w

    connect(move_window,SIGNAL (closeOverlay()), this, SLOT (overlayClosed()));


    // =========================================================== //
    // PLAYER HAND WINDOW
    // =========================================================== //

    // Sub-Window size
    int hand_win_w = 600;
    int hand_win_h = hand_win_w*1.0/1.56; // playing card x/y ratio is 1:1.56

    hand_window = new HandWindow(this,hand_win_h,hand_win_w);
    hand_window->move((win_w-hand_win_w)/2,(win_h-hand_win_h)/2);
    hand_window->close(); //for some reason the hand is automatically open o/w

    // Button to show the hand window
    hand_button = new QPushButton("SHOW HAND", this);
    hand_button->setGeometry(b_xcoord+5*b_xoffs+30,b_ycoord,b_wth+100,b_hth);
    //hand_button->setGeometry(200,200,100,100);
    hand_button->setToolTip("Show the cards in hand");

    hand_button->setCheckable(true);


    // Connection (signal to slot)
    connect(hand_button, SIGNAL (clicked(bool)), this, SLOT (handButtonClicked(bool)));


    // need to also view other players' hands, so can plan trades
    // there could e.g. be a quick-view pane that shows colours reflecting
    // the disease-ares of the cities etc., and a button to open a window
    // where you see the full cards


}

void mainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Start a new game"));
    connect(newAct, &QAction::triggered, this, &mainWindow::new_game);

    loadAct = new QAction(tr("&Load..."), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Load a previous game"));
    connect(loadAct, &QAction::triggered, this, &mainWindow::load_game);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the game"));
    connect(saveAct, &QAction::triggered, this, &mainWindow::save_game);

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the game"));
    connect(quitAct, &QAction::triggered, this, &QWidget::close);

    statusAct = new QAction(tr("&Status view"), this);
    statusAct->setStatusTip(tr("Show status view"));
    connect(saveAct, &QAction::triggered, this, &mainWindow::status_view);


}


void mainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(loadAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);


    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(statusAct);
}


void mainWindow::new_game()
{
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void mainWindow::load_game()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void mainWindow::save_game()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void mainWindow::status_view()
{
    infoLabel->setText(tr("Invoked <b>Edit|Status_view</b>"));
}

void mainWindow::handButtonClicked(bool checked) {
 if (checked) {
 hand_window->show();
 hand_button->setText("CLOSE HAND");
 } else {
 hand_window->close();
 hand_button->setText("SHOW HAND");
     //QApplication::instance()->quit();
 }
}

void mainWindow::overlayClosed() {
 move_window->close();
 move_button->setChecked(false);
 move_button->setText("MOVE");

 // TEMPORARY - to handle fly-button (as it also connects to move_window)
 fly_button->setChecked(false);
 fly_button->setText("FLY");
}



void mainWindow::specButtonClicked(bool checked) {
 if (checked) {
 spec_window->show();
 spec_button->setText("CLOSE\nSPECIAL");
 } else {
 spec_window->close();
 spec_button->setText("SPECIAL");
 }
}

void mainWindow::moveButtonClicked(bool checked) {
 if (checked) {
 move_window->show();
 move_button->setText("CLOSE\nMOVE\nWINDOW");
 } else {
 move_window->close();
 move_button->setText("MOVE");
 }
}

void mainWindow::flyButtonClicked(bool checked) {
 if (checked) {
 move_window->show();
 fly_button->setText("CLOSE\nFLY\nWINDOW");
 } else {
 move_window->close();
 fly_button->setText("FLY");
 }
}


