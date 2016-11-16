#ifndef CONFIRMWINDOW_H
#define CONFIRMWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class QPushButton;

class confirmwindow : public QWidget
{
    Q_OBJECT
public:
    explicit confirmwindow(QWidget *parent = 0, QString info = "Text missing", int height = 180, int width = 180);

private:
    QPushButton *confirm_button;
    QPushButton *cancel_button;
    QLabel *info_text;

private slots:
    void slotConfirmClicked();
    void slotCancelClicked();

signals:
    void confirmSignal(bool confirm);

};

#endif // CONFIRMWINDOW_H
