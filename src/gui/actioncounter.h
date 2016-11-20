#ifndef ACTIONCOUNTER_H
#define ACTIONCOUNTER_H

#include <QWidget>
#include <QLCDNumber>

class actioncounter : public QLCDNumber {
    Q_OBJECT
public:
    explicit actioncounter(QWidget *parent = 0);

signals:
    void noActions();

public slots:
    void check_actions();
};

#endif // ACTIONCOUNTER_H
