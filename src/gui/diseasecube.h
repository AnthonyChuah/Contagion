#ifndef DISEASECUBE_H
#define DISEASECUBE_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsItem>

#include <QGraphicsView>

#include "macros.h"

class diseasecube : public QGraphicsObject {
    //Q_OBJECT
public:
    explicit diseasecube(City *a_city,int d_id,int x_coord,int y_coord,int side);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void setPosition(int x,int y);

    //void moveCity(City* city); //moves the meeple sprite to the city "city"


protected:
    QColor colour;

    City* city;

    QRectF boundingRect() const Q_DECL_OVERRIDE;

private:
    QPixmap pixmap;
    int x=295; //Atlanta x
    int y=309-20; //Atlanta y=309, minus 20 (the menu bar)
    int wth=30;
    int hth=30;

signals:

public slots:
};

#endif // DISEASECUBE_H
