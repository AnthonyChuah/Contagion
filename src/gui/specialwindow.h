#ifndef SPECIALWINDOW_H
#define SPECIALWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QPoint>

class specialwindow : public QWidget {
    Q_OBJECT
public:
    explicit specialwindow(QWidget *parent = 0,int height = 180, int width = 180);

private slots:
    void slotSpec1Clicked(bool checked);
    void slotSpec2Clicked(bool checked);

private:
    QPushButton *button1; //action button 1 (placeholders for cards)
    QPushButton *button2; //action button 2 (only for Dispatcher)

signals:

public slots:
};

#endif // SPECIALWINDOW_H
