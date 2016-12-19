#ifndef FLIGHTSELECTOR_H
#define FLIGHTSELECTOR_H

#include <QWidget>
#include <QPushButton>

class flightselector : public QWidget
{
    Q_OBJECT
public:
    explicit flightselector(QWidget *parent = 0);
    void updateSelection();

private:
    QPushButton* charter_button;
    QPushButton* direct_button;
    QPushButton* shuttle_button;
    QPushButton* opexflight_button;

signals:
    void flightSelection(std::string);

private slots:
    void charterClicked();
    void directClicked();
    void shuttleClicked();
    void opexflightClicked();
};

#endif // FLIGHTSELECTOR_H
