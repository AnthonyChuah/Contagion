#include "endturnwindow.h"
#include <QPushButton>
#include <QDebug>

#include "mainwindow.h"

endturnwindow::endturnwindow(QWidget *parent,int height, int width) : QWidget(parent) {
    //Set the size of the window
    int win_wth=width;//256;
    int win_hth=height;//128;
    setFixedSize(win_wth, win_hth);

    // =========================================================== //
    // Create an information message
    // =========================================================== //
    int label_wth = 150; int label_hth = 50;
    int label_x = (win_wth-label_wth)/2.0;
    int label_y = (win_hth-label_hth)/2.0;
    info_text = new QLabel(this);
    info_text->setGeometry(label_x,label_y,label_wth,label_hth);

    // Setting the colour of the label
    QPalette palette = info_text->palette();
    palette.setColor( backgroundRole(), QColor( 255, 255, 255 ) );
    info_text->setPalette( palette );
    info_text->setAutoFillBackground( true );

    // Frame style settings for the label
    info_text->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    info_text->setText("All four actions taken.\nEnd turn.");
    info_text->setWordWrap(true);
    info_text->setAlignment(Qt::AlignTop | Qt::AlignCenter);


    // =========================================================== //
    // END OF TURN BUTTON
    // =========================================================== //
    int but_wth=label_wth;
    int but_hth=but_wth/1.56; // playing card width/height ratio is 1:1.56
    int but_x=(win_wth-but_wth)/2.0;  // button x-coord
    int but_y=label_y+label_hth+20;  //button y-coord


    endturn_button = new QPushButton("END TURN", this);
    endturn_button->setGeometry(but_x, but_y, but_wth, but_hth);
    endturn_button->setToolTip("Ends the turn");

    connect(endturn_button, SIGNAL (clicked()), this, SLOT (endturnClicked()));

}

void endturnwindow::endturnClicked() {
    // Get the parent (to get the world)
    mainWindow* parent = qobject_cast<mainWindow*>(this->parent());

    qDebug() << "Turn ended. \n";

    // Close end-turn window
    this->close();

    // Draw cards and infect
    int player = parent->world->players_turn;
    parent->world->draw_player_deck(*parent->world->heroes[player]);
    /*
     * HAND LIMIT CHECK - should be done, but then would need to be
     * careful that we don't exit this function and end-up drawing
     * extra cards -- would need to exit to allow for the selection --
     * otherwise the turn will change and the hand window is for the
     * wrong player!
    if(parent->world->heroes[player]->hand.size() > 7) {
        emit handLimit();
        return;
    }
    */
    parent->world->draw_infection_deck();

    // Change turn
    parent->world->next_player_turn();

    // Update the turn indicator picture
    parent->setTurnPicture();

    // Update the disease cubes
    parent->updateDiseases();

    // Update the progress bars
    int inf_rate = parent->world->calculate_infection_rate();
    emit infectionProgress(inf_rate);
    int outbreaks = parent->world->outbreaks;
    emit outbreaksProgress(outbreaks);

    // Update the action LCD
    parent->action_lcd->check_actions();

    // Update the hand window
    player = parent->world->players_turn;
    parent->getHandWindow()->update_window(parent->world->heroes[player]);

    // Update the flight selection
    parent->updateFlightSelection();
}
