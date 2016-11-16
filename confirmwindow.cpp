#include "confirmwindow.h"

confirmwindow::confirmwindow(QWidget *parent,QString info,int height, int width) : QWidget(parent) {
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
    info_text->setText(info);
    info_text->setWordWrap(true);
    //info_text->setText("first line\nsecond line");
    info_text->setAlignment(Qt::AlignTop | Qt::AlignCenter);


    // =========================================================== //
    // Create and position the buttons
    // =========================================================== //
    int but_gap=20; // gap between buttons
    int but_wth=(label_wth-but_gap)/2.0;
    int but_hth=but_wth/1.56; // playing card width/height ratio is 1:1.56

    int but_x=(win_wth-but_gap)/2.0-but_wth;  // first button x-coord
    //int but_y=(win_hth-but_hth)/2.0;  // button y-coord
    int but_y = label_y+label_hth+but_gap;
    int but_x_offset=but_wth+but_gap; //button x-offset

    // =========================================================== //
    // Confirm button
    // =========================================================== //
    confirm_button = new QPushButton("CONFIRM", this);
    confirm_button->setGeometry(but_x, but_y, but_wth, but_hth);
    confirm_button->setToolTip("Confirm your choice");

    // Connection (signal to slot)
    connect(confirm_button, SIGNAL (clicked()), this, SLOT (slotConfirmClicked()));


    // =========================================================== //
    // Cancel button
    // =========================================================== //
    cancel_button = new QPushButton("CANCEL", this);
    cancel_button->setGeometry(but_x+but_x_offset, but_y, but_wth, but_hth);
    cancel_button->setToolTip("Cancel your choice");

    // Connection (signal to slot)
    connect(cancel_button, SIGNAL (clicked()), this, SLOT (slotCancelClicked()));


}


void confirmwindow::slotConfirmClicked() {

    // Emit the confirm signal
    emit confirmSignal(true);

    // Close the Confirm window
    this->close();
}

void confirmwindow::slotCancelClicked() {

    // Emit the cancel signal (false confirm signal)
    emit confirmSignal(false);

    // Close the Confirm window
    this->close();
}
