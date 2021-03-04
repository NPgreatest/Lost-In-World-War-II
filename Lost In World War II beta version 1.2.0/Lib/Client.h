#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include<QPainter>
#include<QTimer>
#include<QImage>
#include<QRect>
#include"glwidget_2.h"
#include"mainwindow.h"
#include"Sql.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE
class MainWindow;
class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();
    void paint(QPainter *painter, QPaintEvent *event) ;//OpenGl实现

private:
    Ui::Client *ui;
    QTimer Timer;


};

#endif // CLIENT_H
