#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "window.h"

class QMenu;
class QLabel;

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = 0);

protected:
//#ifndef QT_NO_CONTEXTMENU
//    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
//#endif // QT_NO_CONTEXTMENU

signals:

private slots:
    void new_game();
    void load_game();
    void save_game();
    void status_view();
    void handButtonClicked(bool checked);


private:
    void createActions();
    void createMenus();

    Window *hand_window;

    QMenu *fileMenu;
    QMenu *viewMenu;

    QAction *newAct;
    QAction *loadAct;
    QAction *saveAct;
    QAction *quitAct;

    QAction *statusAct;

    QLabel *infoLabel;
};

#endif // MAINWINDOW_H
