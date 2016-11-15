#include <QtWidgets>
#include <iostream>
#include "mainwindow.h"
#include "handwindow.h"
#include "transpbutton.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{

    QDir::setCurrent(QCoreApplication::applicationDirPath());


    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


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
    // Style sheet
    // =========================================================== //
    QFile file("../Contagion/resources/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    this->setStyleSheet(styleSheet);



    // =========================================================== //
    // BUTTONS
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
    //PCard_button->setAttribute(Qt::WA_TranslucentBackground);
    PCard_button->setToolTip("Draws a player card");
    //PCard_button->setStyleSheet("border-image:url(../Contagion/images/pcard.jpg);");

    // Push button for infection card
    QPushButton *ICard_button = new QPushButton("INFECTION", this);
    //TranspButton *ICard_button = new TranspButton(this); // Transparent button
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

    // Move
    QPushButton *move_button = new QPushButton("MOVE", this);
    move_button->setGeometry(b_xcoord,b_ycoord,b_wth,b_hth);
    move_button->setToolTip("Move along the map");
    //move_button->setStyleSheet("border-image:url(../Contagion/images/pcard.jpg);");


    // Fly
    QPushButton *fly_button = new QPushButton("FLY", this);
    fly_button->setGeometry(b_xcoord+1*b_xoffs,b_ycoord,b_wth,b_hth);
    fly_button->setToolTip("Fly along the map");


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


    // =========================================================== //
    // PLAYER HAND WINDOW
    // =========================================================== //

    // Sub-Window size
    int hand_win_w = 600;
    int hand_win_h = hand_win_w*1.0/1.56;

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


    // =========================================================== //
    // CITY BUTTONS - SHOULD BE CREATED USING AN EXTERNAL FILE!!!
    // =========================================================== //

    // Radio button rectangle (background) size
    int radio_wth=30;
    int radio_hth=radio_wth;

    QRadioButton* cityButton = new QRadioButton(this);
    cityButton->setGeometry(110,270,radio_wth,radio_hth); //sets location and size of rectangle
    cityButton->setText("San Francisco");


    //OTHER BUTTONS, FOR TESTING PURPOSES - NEED TO GEN FROM FILE!
    QRadioButton* cityButton2 = new QRadioButton(this);
    cityButton2->setGeometry(120,300,radio_wth,radio_hth);
    cityButton2->setText("LA");

    QRadioButton* cityButton3 = new QRadioButton(this);
    cityButton3->setGeometry(250,230,radio_wth,radio_hth);
    cityButton3->setText("Chicago");

    QRadioButton* cityButton4 = new QRadioButton(this);
    cityButton4->setGeometry(330,225,radio_wth,radio_hth);
    cityButton4->setText("Montreal");

    QRadioButton* cityButton5 = new QRadioButton(this);
    cityButton5->setGeometry(340,255,radio_wth,radio_hth);
    cityButton5->setText("NY");

    QRadioButton* cityButton6 = new QRadioButton(this);
    cityButton6->setGeometry(320,280,radio_wth,radio_hth);
    cityButton6->setText("DC");

    QRadioButton* cityButton7 = new QRadioButton(this);
    cityButton7->setGeometry(270,300,radio_wth,radio_hth);
    cityButton7->setText("Atlanta");

    QRadioButton* cityButton8 = new QRadioButton(this);
    cityButton8->setGeometry(285,340,radio_wth,radio_hth);
    cityButton8->setText("Miami");


    //NEED A FUNCTION THAT GENERATES THESE FROM AN INPUT FILE!

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

void mainWindow::specButtonClicked(bool checked) {
 if (checked) {
 spec_window->show();
 spec_button->setText("CLOSE\nSPECIAL");
 } else {
 spec_window->close();
 spec_button->setText("SPECIAL");
     //QApplication::instance()->quit();
 }
}
