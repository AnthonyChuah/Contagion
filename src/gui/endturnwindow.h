#ifndef ENDTURNWINDOW_H
#define ENDTURNWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class endturnwindow : public QWidget {
    Q_OBJECT
public:
    explicit endturnwindow(QWidget *parent = 0,int height = 180, int width = 180);

signals:
    void handLimit();

public slots:

private:
    //QPushButton *card_button1; //card button 1 (placeholders for cards)
    //QPushButton *card_button7; //card button 7 (placeholders for cards)
    QLabel *info_text;
    QPushButton *endturn_button;

private slots:
    void endturnClicked();


};

#endif // ENDTURNWINDOW_H
