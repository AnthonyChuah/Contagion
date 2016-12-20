#include "diseasecube.h"
#include "movewindow.h"
#include <string>

#include <QPainter>
#include <QRectF>
#include <QDebug>

diseasecube::diseasecube(City* a_city,int d_id,int x_coord,int y_coord,int side){
    city = a_city;

    // Position and Dimensions
    x=x_coord;
    y=y_coord;
    wth=side;
    hth=wth;

    // SET COLOUR
    if(d_id==0) {
        colour.setRgb(242,236,51);
    }
    else if(d_id==1) {
        colour.setRgb(242,51,51);
    }
    else if(d_id==2) {
        colour.setRgb(51,73,242);
    }
    else if(d_id==3) {
        colour.setRgb(0,0,0);
    } else {
        colour.setRgb(244,244,244);
    }

}

void diseasecube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (pixmap.isNull()) {
        painter->setBrush(colour);
        painter->drawRect(x,y,wth,hth);
    } else {
        painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
    }
}


QRectF diseasecube::boundingRect() const {
    return QRectF(x,y,wth,hth);
}

void diseasecube::setPosition(int x_coo, int y_coo) {

    // Move coords are relative to original position, so have to rebase
    x_coo = x_coo-x;
    y_coo = y_coo-y-20;  // -20 correction for menu bar position

    this->setPos(x_coo,y_coo);
}
