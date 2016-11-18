#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "handwindow.h"
#include "specialwindow.h"
#include "movewindow.h"
#include "movebuttons.h"
#include "world.h"

#include <QPushButton>
#include <QLCDNumber>


class QMenu;
class QLabel;

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    //explicit mainWindow(QWidget *parent = 0); //if parent needed
    explicit mainWindow(World* wrld);

    World* world;

    QLCDNumber* action_lcd;


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
    movebuttons *move_buttons;

    QMenu *fileMenu;
    QMenu *viewMenu;

    QAction *newAct;
    QAction *loadAct;
    QAction *saveAct;
    QAction *quitAct;

    QAction *statusAct;

    QLabel *infoLabel;

    QPushButton *hand_button;
    QPushButton *spec_button;
    QPushButton *move_button;
    QPushButton *fly_button;

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

    void overlayClosed(); //for closing move overlay correctly

};

#endif // MAINWINDOW_H
