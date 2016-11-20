#include "meeplesprite.h"
#include <string>

#include <QPainter>
#include <QRectF>
#include <QDebug>

meeplesprite::meeplesprite(Hero* hero){

    // Position and Dimensions
    x=295;      //Atlanta x
    y=309-20;   //Atlanta y=309, minus 20 (the menu bar)
    wth=25;
    hth=25;

    std::string type = hero->get_spec();

    // SET COLOUR
    if(!type.compare("Contingency Planner"))
        colour.setRgb(40,210,222);
    else if(!type.compare("Dispatcher"))
        colour.setRgb(222,40,198);
    else if(!type.compare("Medic"))
        colour.setRgb(222,137,40);
    else if(!type.compare("Operations Expert"))
        colour.setRgb(152,222,40);
    else if(!type.compare("Quarantine Specialist"))
        colour.setRgb(16,130,23);
    else if(!type.compare("Researcher"))
        colour.setRgb(140,96,77);
    else //if(!type.compare("Scientist"))
        colour.setRgb(255,255,255);

}

void meeplesprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (pixmap.isNull()) {
        painter->setBrush(colour);
        painter->drawEllipse(x,y,wth,hth);

        //qDebug () << "Trying to paint.\n";
        //qDebug () << "x is:" << x << " and y is:" << y << "./n";
    } else {
        painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
    }
}


QRectF meeplesprite::boundingRect() const {
    return QRectF(x,y,wth,hth);
}

void meeplesprite::setPosition(int x, int y) {
    this->setPos(x,y-20);
}
