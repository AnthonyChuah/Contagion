#include <QtWidgets>
#include <iostream>
#include "mainwindow.h"
#include "handwindow.h"
#include "movewindow.h"
#include "transpbutton.h"
#include "actioncounter.h"

#include "meeplesprite.h"
#include "diseasecube.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <QPen>
#include <QBrush>

#include "macros.h"

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
    //setMinimumSize(160, 160);
    resize(win_w, win_h);

    // Background picture
    QPixmap bkgnd(":/images/World_map_concept_coloured.png");
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
    // Turn label
    // =========================================================== //
    turnLabel = new QLabel(this);
    turnLabel->setGeometry(1900/2-250,20,250,50);
    turnPicture = new QPixmap();
    this->setTurnPicture();
    //turnLabel->setPixmap(*turnPicture);

    // =========================================================== //
    // Load the style sheet
    // =========================================================== //
    QFile file(":/resources/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    this->setStyleSheet(styleSheet);

    // =========================================================== //
    // INFECTION RATE progress bar
    // =========================================================== //
    QProgressBar *iprogBar = new QProgressBar(this);
    int iprb_wth=300;
    int iprb_hth=40;
    iprogBar->setRange(1,7); //ranges from 1 to 7
    //iprogBar->setRange(0,4); //ranges from 0 to 4
    iprogBar->setValue(this->world->calculate_infection_rate());
    iprogBar->setGeometry(win_w-iprb_wth-20,20,iprb_wth,iprb_hth);

    // Better as a number! - NEED TO FIGURE OUT IF CAN SET THE NUMBER IN THE BAR

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
    action_lcd = new actioncounter(this);
    action_lcd->show();

    // =========================================================== //
    // DISEASES progress bars
    // =========================================================== //
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

    // Build-research-centre button
    build_rc_button = new QPushButton("BUILD A\nRESEARCH\nCENTRE", this);
    build_rc_button->setGeometry(b_xcoord-1.4*b_xoffs,b_ycoord+0.4*b_hth,b_wth*0.6,b_hth*0.6);
    build_rc_button->setToolTip("Build a research centre in current city.");
    connect(build_rc_button, SIGNAL (clicked()), this, SLOT (buildRcButtonClicked()));

    // Move button
    move_button = new QPushButton("MOVE", this);
    move_button->setGeometry(b_xcoord,b_ycoord,b_wth,b_hth);
    move_button->setToolTip("Move along the map");
    move_button->setCheckable(true);
    connect(move_button, SIGNAL (clicked(bool)), this, SLOT (moveButtonClicked(bool)));

    // Fly
    fly_button = new QPushButton("FLY", this);
    fly_button->setGeometry(b_xcoord+1*b_xoffs,b_ycoord,b_wth,b_hth);
    fly_button->setToolTip("Fly along the map");
    fly_button->setCheckable(true);
    connect(fly_button, SIGNAL (clicked(bool)), this, SLOT (flyButtonClicked(bool)));

    // Special action
    spec_button = new QPushButton("SPECIAL", this);
    spec_button->setGeometry(b_xcoord+2*b_xoffs,b_ycoord,b_wth,b_hth);
    spec_button->setToolTip("Hero's special action");
    spec_button->setCheckable(true);
    connect(spec_button, SIGNAL (clicked(bool)), this, SLOT (specButtonClicked(bool)));

    // Disinfect button
    disinfect_button = new QPushButton("DISINFECT", this);
    disinfect_button->setGeometry(b_xcoord+3*b_xoffs,b_ycoord,b_wth,b_hth);
    disinfect_button->setToolTip("Disinfect");
    connect(disinfect_button, SIGNAL (clicked()), this, SLOT (disinfectButtonClicked()));

    // Cure button (find cure)
    cure_button = new QPushButton("FIND\nA CURE", this);
    cure_button->setGeometry(b_xcoord-2*b_xoffs,b_ycoord+0.4*b_hth,b_wth*0.6,b_hth*0.6);
    cure_button->setToolTip("Find a cure");

    // CURE BUTTON FUNCTIONALITY TO BE ADDED
    // Alternatively, CURE could be done via the hand window
    //connect(cure_button, SIGNAL (clicked()), this, SLOT (cureButtonClicked()));


    // =========================================================== //
    // WINDOW OVERLAYS
    // =========================================================== //

    // MOVE WINDOW
    move_window = new movewindow(this,win_h-150,win_w);
    move_window->close(); //for some reason the window is automatically open o/w
    connect(move_window,SIGNAL (closeOverlay()), this, SLOT (overlayClosed()));

    // FLIGHT SELECTOR AND FLY WINDOW
    flight_selector = new flightselector(this);
    flight_selector->setGeometry(b_xcoord+b_xoffs-16,b_ycoord-60,220,50);
    flight_selector->updateSelection();
    flight_selector->close();
    connect(flight_selector,SIGNAL (flightSelection(std::string)), this, SLOT (flightSelection(std::string)));

    fly_window = new flywindow(this,win_h-150,win_w);
    fly_window->close(); //for some reason this is automatically open o/w
    connect(fly_window,SIGNAL (closeOverlay()), this, SLOT (overlayClosed()));

    // SPECIAL WINDOW
    int spec_win_w = 600;
    int spec_win_h = spec_win_w*1.0/1.56;
    spec_window = new specialwindow(this,spec_win_h,spec_win_w);
    spec_window->move((win_w-spec_win_w)/2,(win_h-spec_win_h)/2);
    spec_window->close(); //for some reason this is automatically open o/w

    // DISINFECT WINDOW
    int disn_win_w = 600;
    int disn_win_h = disn_win_w*1.0/1.56;
    disinfect_window = new disinfectwindow(this,disn_win_h,disn_win_w);
    disinfect_window->move((win_w-disn_win_w)/2,(win_h-disn_win_h)/2);
    disinfect_window->close();


    // =========================================================== //
    // PLAYER HAND WINDOW
    // =========================================================== //
    int hand_win_w = 600;
    int hand_win_h = hand_win_w*1.0/1.56; // playing card x/y ratio is 1:1.56
    hand_window = new HandWindow(this,hand_win_h,hand_win_w);
    hand_window->move((win_w-hand_win_w)/2,(win_h-hand_win_h)/2);
    hand_window->close(); //for some reason the hand is automatically open o/w

    connect(hand_window,SIGNAL (handButtonUp()), this, SLOT (handOverlayClosed()));
    connect(hand_window->card_window,SIGNAL (cardOverlayClosed()), this, SLOT (cardOverlayClosed()));
    connect(fly_window, SIGNAL (flightSuccess()), this, SLOT (flightHandUpdate()));

    // Button to show the hand window
    hand_button = new QPushButton("SHOW HAND", this);
    hand_button->setGeometry(b_xcoord+4.7*b_xoffs,b_ycoord+0.4*b_hth,b_wth+50,b_hth*0.6);
    hand_button->setToolTip("Show the cards in hand");

    hand_button->setCheckable(true);

    connect(hand_button, SIGNAL (clicked(bool)), this, SLOT (handButtonClicked(bool)));
    // Shortcut
    //new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_H), hand_window, SLOT(show()));
    //SOME BUG EXISTS IN THE ABOVE SHORTCUT!

    // need to also view other players' hands, so can plan trades
    // there could e.g. be a quick-view pane that shows colours reflecting
    // the disease-ares of the cities etc., and a button to open a window
    // where you see the full cards

    // =========================================================== //
    // MESSAGE BOX TO TELL A PLAYER TO DISCARD
    // =========================================================== //
    discard_message = new QMessageBox(this);
    discard_message->setText("Too many cards in hand.");
    discard_message->setInformativeText("Please discard cards until the hand contains seven cards.");
    discard_message->setStandardButtons(QMessageBox::Ok);

    // Hand limit signals: action_lcd checks when updating if limit exceeded
    //                     hand_window checks when the window is closed
    connect(action_lcd,SIGNAL (handLimit()), discard_message, SLOT (exec()));
    connect(hand_window,SIGNAL (handLimit()), discard_message, SLOT (exec()));
    connect(discard_message->button(QMessageBox::Ok), SIGNAL (clicked()), this, SLOT (discardCards()));

    // =========================================================== //
    // GRAPHICS SCENE AND VIEW
    // =========================================================== //

    // Create a scene, 5px smaller than graphics_view to both dirs (no scroll bars)
    scene = new QGraphicsScene(0,0,win_w-5,win_h-220-5,this);

    // Create graphics_view to hold the scene
    graphics_view = new QGraphicsView(scene,this);
    graphics_view->setGeometry(0,20,win_w,win_h-220);
    graphics_view->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    graphics_view->show();

    // =========================================================== //
    // MEEPLES
    // =========================================================== //
    create_meeples(&meeples);

    // =========================================================== //
    // DISEASE CUBES
    // =========================================================== //
    // Draw disease cubes
    setup_diseasecubes();

    // =========================================================== //
    // RESEARCH CENTRES
    // =========================================================== //
    // Draw research centres
    setup_research_centres();

    // =========================================================== //
    // END-TURN WINDOW OVERLAY
    // =========================================================== //

    // Overlay Window size
    int endturn_win_w = 600;
    int endturn_win_h = endturn_win_w*1.0/1.56; // playing card x/y ratio is 1:1.56

    endturn_window = new endturnwindow(this,endturn_win_h,endturn_win_w);
    endturn_window->move((win_w-endturn_win_w)/2,(win_h-endturn_win_h)/2);
    endturn_window->close(); //for some reason the hand is automatically open o/w

    connect(action_lcd,SIGNAL (noActions()), this, SLOT (openEndturn()));

    connect(endturn_window,SIGNAL(outbreaksProgress(int)),oprogBar,SLOT(setValue(int)));
    connect(endturn_window,SIGNAL(infectionProgress(int)),iprogBar,SLOT(setValue(int)));
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
    qDebug() << "New game function - STUB. \n";
}

void mainWindow::load_game()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
    qDebug() << "Load game function - STUB. \n";
}

void mainWindow::save_game()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
    qDebug() << "Save game function - STUB. \n";
}

void mainWindow::status_view()
{
    infoLabel->setText(tr("Invoked <b>Edit|Status_view</b>"));
    qDebug() << "Status view function - STUB. \n";
}

/* Function that sets the turn indicator picture */
void mainWindow::setTurnPicture()
{
    int player = this->world->players_turn;
    Hero* hero = this->world->heroes[player];
    std::string type = hero->get_spec();

    // SET PICTURE
    if(!type.compare("Contingency Planner"))
        turnPicture->load(":/images/cont_planner_turn_bevel.png");
    else if(!type.compare("Dispatcher"))
        turnPicture->load(":/images/dispatcher_turn_bevel.png");
    else if(!type.compare("Medic"))
        turnPicture->load(":/images/medic_turn_bevel.png");
    else if(!type.compare("Operations Expert"))
        turnPicture->load(":/images/op_exp_turn_bevel.png");
    else if(!type.compare("Quarantine Specialist"))
        turnPicture->load(":/images/quar_spec_turn_bevel.png");
    else if(!type.compare("Researcher"))
        turnPicture->load(":/images/researcher_turn_bevel.png");
    else //if(!type.compare("Scientist"))
        turnPicture->load(":/images/scientist_turn_bevel.png");

    this->turnLabel->setPixmap(*turnPicture);
}


void mainWindow::create_meeples(QList<meeplesprite*> *meeps)
{
    // ---- Setting up the QList, meeps ----
    Hero* a_hero = new Hero();

    for(size_t i=0;i<world->heroes.size();i++) {
        a_hero = world->heroes[i];
        meeplesprite* a_meeple = new meeplesprite(a_hero);
        a_meeple->moveBy(3*i,0);
        meeps->append(a_meeple);
    }


    // ---- Drawing the meeples ----
    QPixmap pixmap(30, 30);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    for(int i=0; i<meeps->size(); i++) {
        scene->addItem((*meeps)[i]);
        (*meeps)[i]->paint(&painter,0,0);
    }
    painter.end();

}


void mainWindow::setup_diseasecubes()
{
    // For each city, add cubes
    std::vector<City>::iterator it;
    for(it=world->cities.begin();it != world->cities.end();it++) {
        draw_citydiseases(&(*it));
    }
}


void mainWindow::draw_citydiseases(City* a_city)
{
    int side = 10;

    // City coordinates
    double x = a_city->x_coord;
    double y = a_city->y_coord;
    convertXY(x,y);
    x = x+15;
    y = y-15;

    // Remove existing cubes
    QGraphicsItem* removable;
    int mult = 0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            removable = scene->itemAt(x+j*(2+side),y+mult*(2+side),QTransform());
            if(removable->data(0)=="d_cube") {
                scene->removeItem(removable);
                delete(removable);
            }
        }
        mult++;
    }

    // Draw the cubes
    diseasecube* a_cube;
    mult = 0;
    int x_coord; int y_coord;
    for (int i=0; i<4; i++) {
        if(a_city->get_ncubes(i)>0) {
            qDebug() << "Disease " << i << "counter is" << a_city->get_ncubes(i) << "\n.";
            for (int j=0; j<a_city->get_ncubes(i); j++) {
                x_coord = x+j*(2+side);
                y_coord = y+mult*(2+side);
                a_cube = new diseasecube(a_city,i,x_coord,y_coord,side);
                a_cube->setData(0,"d_cube");
                scene->addItem(a_cube);
            }
            mult++;
        }
    }
}


void mainWindow::setup_research_centres()
{
    // For each city, add RC if applicable
    std::vector<City>::iterator it;
    for(it=world->cities.begin();it != world->cities.end();it++) {
        if(it->has_rc())
            draw_cityRC(&(*it));
    }
}


void mainWindow::draw_cityRC(City *a_city)
{
    qDebug() << "Draw city RC -- Temporarily using diseasecube class.\n";
    int side = 15;

    // City coordinates
    double x = a_city->x_coord;
    double y = a_city->y_coord;
    convertXY(x,y);
    x = x-20;
    y = y-15;

    // Draw the RC cubes
    diseasecube* a_cube = new diseasecube(a_city,-1,x,y,side);
    scene->addItem(a_cube);
    // TEMPORARILY using the diseasecube class -- change to a
    // specific implementation when decide what the RCs should
    // look like.
}


void mainWindow::handButtonClicked(bool checked)
{
    if (checked) {
        graphics_view->close();
        hand_window->show();
        hand_button->setText("CLOSE HAND");
    } else {
        hand_window->close();
        hand_button->setText("SHOW HAND");
        // Show the graphics view
        graphics_view->show();

        // CHECK END TURN: Check number of actions - check LCD, and open end-turn window if needed
        action_lcd->check_actions();
    }
}


void mainWindow::overlayClosed()
{
    move_window->close();
    move_button->setChecked(false);
    move_button->setText("MOVE");

    // TEMPORARY - to handle fly-button (as it also connects to move_window)
    fly_window->close();
    fly_button->setChecked(false);
    fly_button->setText("FLY");

    // Show the graphics view
    graphics_view->show();
}


void mainWindow::handOverlayClosed()
{
 hand_window->QWidget::close(); //must use the QWidget version
 hand_button->setChecked(false);
 hand_button->setText("SHOW HAND");
 // Set the button down, as card overlay is open
 hand_button->setDown(true);

 // CHECK END TURN: Check number of actions - update LCD, and open end-turn window if needed
 action_lcd->check_actions();
}


void mainWindow::cardOverlayClosed()
{
    graphics_view->show();
    hand_button->setDown(false);
}


void mainWindow::specButtonClicked(bool checked)
{
 if (checked) {
     spec_window->update();
     graphics_view->close();
     spec_window->show();
     spec_button->setText("CLOSE\nSPECIAL");
 } else {
    spec_window->close();
    spec_button->setText("SPECIAL");
    graphics_view->show();
 } 
}


void mainWindow::moveButtonClicked(bool checked)
{
 if (checked) {
    graphics_view->close();
    move_window->show();
    move_button->setText("CLOSE\nMOVE\nWINDOW");
 } else {
    move_window->close();
    move_button->setText("MOVE");
    graphics_view->show();
 }
}


void mainWindow::flyButtonClicked(bool checked)
{
    if(checked) {
        flight_selector->show();
        fly_button->setText("CLOSE\nFLY\nWINDOW");
    } else {
        fly_window->close();
        flight_selector->close();
        fly_button->setText("FLY");
        graphics_view->show();
    }
}


void mainWindow::flightSelection(std::string flight_type)
{
    fly_window->update_cities(flight_type);
    graphics_view->close();
    flight_selector->close();
    fly_window->show();
}


void mainWindow::flightHandUpdate()
{
    hand_window->update_window(this->world->heroes[this->world->players_turn]);
}


void mainWindow::disinfectButtonClicked()
{
    int player = world->players_turn;
    City* d_city = world->heroes[player]->ptr_city;

    // COUNT DISEASES currently in the city
    std::vector<bool> d_exs; //booleans of wheter disease exists
    int d_types=0;
    int last_d=0; //last disease that exists - used in one disease case below
    for (int i=0; i<4; i++) {
      if (d_city->get_ncubes(i)>0) {
          d_exs.push_back(true);
          d_types++;
          last_d=i;
      } else {
          d_exs.push_back(false);
      }
    }

    // CHOOSE WHICH DISEASE COLOUR TO REMOVE
    if(d_types>1) {
        // open disease select window
        disinfect_window->show(d_exs.at(0),d_exs.at(1),d_exs.at(2),d_exs.at(3));
    } else if (d_types==1) {
        qDebug() << "Only one disease exists in the city -- treating that. \n";
        treatDisease(last_d);
    }

    // Update the action LCD
    action_lcd->check_actions();
}


void mainWindow::buildRcButtonClicked()
{
    int player = world->players_turn;
    City* rc_city = world->heroes[player]->ptr_city;

    if(world->heroes[player]->build_centre(*rc_city)) {
        qDebug() << "Successfully built a research centre.\n";
        setup_research_centres();
        action_lcd->check_actions();
    } else {
        qDebug() << "Research centre build unsuccessful.\n";
    }
}


void mainWindow::discardCards()
{
    graphics_view->close();
    qDebug() << "Showing hand window for discarding cards \n";
    hand_window->update_window(this->world->heroes[this->world->players_turn]);
    hand_button->setChecked(true);
    handButtonClicked(true);
}


void mainWindow::openEndturn()
{
    // Checking hand limit, and pop-up discard message if too many cards
    if(this->world->heroes[this->world->players_turn]->hand.size() > 7) {
        discard_message->exec();
        // End-turn window is not showed here yet, as it would interfere with
        // the discard message and hand window. The end-turn check is
        // done again after cards discarded
    } else {
        qDebug() << "Opening EndTurn window.\n";
        endturn_window->show();
    }
}


void mainWindow::treatDisease(int d_id)
{
    int player = world->players_turn;
    City* d_city = world->heroes[player]->ptr_city;

    // Disinfect action
    qDebug() << "Disinfect action attempted! \n";
    world->heroes[player]->disinfect(d_id);
    qDebug() << "The number of disease cubes is " << d_city->get_ncubes(d_id)<<"\n";
    draw_citydiseases(d_city);
    graphics_view->show();
}


// PUBLIC FUNCTIONS
void mainWindow::openGraphics()
{
    graphics_view->show();
}


void mainWindow::closeGraphics()
{
    qDebug() << "Closing graphics view.\n";
    graphics_view->close();
}

