#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "handwindow.h"
#include "specialwindow.h"
#include "movewindow.h"
#include "flywindow.h"
#include "disinfectwindow.h"
#include "endturnwindow.h"
#include "actioncounter.h"
#include "movebuttons.h"
#include "meeplesprite.h"
#include "flightselector.h"

#include "macros.h"

#include <QPushButton>
#include <QLCDNumber>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <vector>

class QMenu;
class QLabel;

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(World* wrld);

    World* world;

    actioncounter* action_lcd;

    QList<meeplesprite*> meeples;

    void openGraphics();
    void closeGraphics();

    void updateDiseases() { setup_diseasecubes(); }
    HandWindow* getHandWindow() { return hand_window; }

    // Window width and height
    int win_w = 1600;
    int win_h =900;

    // Message box telling a player to discard cards
    QMessageBox* discard_message;

    // Set the turn picture
    void setTurnPicture();

    // Update flight selection
    void updateFlightSelection() { flight_selector->updateSelection(); }

protected:
//#ifndef QT_NO_CONTEXTMENU
//    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
//#endif // QT_NO_CONTEXTMENU

private:
    void createActions();
    void createMenus();

    HandWindow *hand_window;
    specialwindow *spec_window;
    movewindow *move_window;
    flightselector* flight_selector;
    flywindow *fly_window;
    endturnwindow *endturn_window;
    disinfectwindow *disinfect_window;

    QMenu *fileMenu;
    QMenu *viewMenu;

    QAction *newAct;
    QAction *loadAct;
    QAction *saveAct;
    QAction *quitAct;
    QAction *statusAct;

    QLabel *infoLabel;

    QLabel *turnLabel; //graphic label indicating whose turn it is
    QPixmap* turnPicture;

    // ---------------------------------------------- //
    // Buttons
    // ---------------------------------------------- //
    QPushButton *hand_button;
    QPushButton *spec_button;
    QPushButton *move_button;
    QPushButton *fly_button;
    QPushButton *disinfect_button;
    QPushButton *build_rc_button;
    QPushButton *cure_button;

    // ---------------------------------------------- //
    // Graphics
    // ---------------------------------------------- //
    QGraphicsScene *scene;
    QGraphicsView* graphics_view;

    // Meeple creation function
    void create_meeples(QList<meeplesprite*> *meeps);
    // Disease cube creation functions
    QList<QColor> dis_colours;
    void setup_diseasecubes();
    void draw_citydiseases(City* a_city);
    // Research centres
    void setup_research_centres();
    void draw_cityRC(City* a_city);

signals:

private slots:
    void new_game();
    void load_game();
    void save_game();
    void status_view();

    void handButtonClicked(bool checked);
    void specButtonClicked(bool checked);
    void moveButtonClicked(bool checked);
    void flyButtonClicked(bool checked);
    void flightSelection(std::string);
    void disinfectButtonClicked();
    void buildRcButtonClicked();

    void overlayClosed(); //for closing move overlay correctly
    void handOverlayClosed(); // for closing hand overlay correctly
    void cardOverlayClosed();

    void discardCards();
    void flightHandUpdate();

    void openEndturn();

    void treatDisease(int d_id);

};

#endif // MAINWINDOW_H
