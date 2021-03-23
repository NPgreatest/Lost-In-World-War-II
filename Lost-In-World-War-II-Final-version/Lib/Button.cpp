#include "Button.h"

Button::Button(QWidget *parent) : QPushButton(parent)
{
    Move = false;
}
void Button::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage t1(":/Images/Images/Move.png");
    if (Move)
    {
        painter.drawImage(QRect(0, 0, this->width(), this->height()), t1);
    }

    painter.drawText(QRect(0, 0, this->width(), this->height()), Qt::AlignCenter,
                     this->text(), nullptr);
}

void Button::enterEvent(QEvent *event)
{
    Move = true;
    update();
    emit Mouse_Click();
}
void Button::leaveEvent(QEvent *event)
{
    Move = false;
    update();
}
void Button::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
}
