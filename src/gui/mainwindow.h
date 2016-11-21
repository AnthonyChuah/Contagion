#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "handwindow.h"
#include "specialwindow.h"
#include "movewindow.h"
#include "endturnwindow.h"
#include "actioncounter.h"
#include "movebuttons.h"
#include "meeplesprite.h"

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
    //explicit mainWindow(QWidget *parent = 0); //if parent needed
    explicit mainWindow(World* wrld);

    World* world;

    //QLCDNumber* action_lcd;
    actioncounter* action_lcd;

    QList<meeplesprite*> meeples;

    void openGraphics();
    void closeGraphics();

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
    endturnwindow *endturn_window;

    QMenu *fileMenu;
    QMenu *viewMenu;

    QAction *newAct;
    QAction *loadAct;
    QAction *saveAct;
    QAction *quitAct;
    QAction *statusAct;

    QLabel *infoLabel;

    // ---------------------------------------------- //
    // Buttons
    // ---------------------------------------------- //
    QPushButton *hand_button;
    QPushButton *spec_button;
    QPushButton *move_button;
    QPushButton *fly_button;
    QPushButton *disinfect_button;

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
    void disinfectButtonClicked();

    void overlayClosed(); //for closing move overlay correctly

    void openEndturn();

};

#endif // MAINWINDOW_H
