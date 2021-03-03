#include"Paint.h"

Widget::Widget(QWidget *parent):QWidget(parent),ui(new Ui::Widget){
ui->setupUi(this);
setPalette(QPalette(Qt::white));
setAutoFillBackground(true);
}
void Widget::paintEvent(QPaintEvent *event){
    QPainter  painter (this);


}
