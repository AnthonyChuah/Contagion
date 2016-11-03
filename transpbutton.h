#ifndef TRANSPBUTTON_H
#define TRANSPBUTTON_H

#include<QAbstractButton>

class TranspButton : public QAbstractButton
{
public:
    TranspButton( QWidget *parent = 0) : QAbstractButton( parent ) {}
protected:
    void paintEvent( QPaintEvent * ) {}
};

#endif // TRANSPBUTTON_H
