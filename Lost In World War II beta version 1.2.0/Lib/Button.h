#ifndef BUTTON_H
#define BUTTON_H
#include<QPushButton>
#include<QPainter>
#include<QMouseEvent>
#include<QEvent>
class Button:public QPushButton
{

    Q_OBJECT

public:
    Button(QWidget *parent=0);
signals:
    void clicked();
    void Mouse_Click();
protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *ev);
private:
    bool Move;


};

#endif
