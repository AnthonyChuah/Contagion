#ifndef MOVEBUTTONS_H
#define MOVEBUTTONS_H

#include <QWidget>
#include <QPushButton>

class movebuttons : public QWidget
{
    Q_OBJECT
public:
    explicit movebuttons(QWidget *parent = 0);

private:
    QPushButton *move_button;
    QPushButton *fly_button;
    QPushButton *spec_button;

signals:

private slots:
    void moveButtonClicked(bool checked);
    void flyButtonClicked(bool checked);
    void specButtonClicked(bool checked);

public slots:
};

#endif // MOVEBUTTONS_H
