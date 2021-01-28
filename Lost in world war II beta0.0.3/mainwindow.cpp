#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Player.h"
#include<QMessageBox>
#include<QPainter>
#include <QIcon>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowIcon(QIcon("://images/icon.bmp"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    QRect rect(0,0,1600,1000);
    QImage image(":/images/BackGround2.jpg");
    painter.drawImage(rect,image);
}


void MainWindow::on_test_clicked()
{
 //   QMessageBox::information(nullptr,tr("提示"),tr("若无地图文件\n请先编辑地图\n再选择已创建的地图"), tr("好"));
 //   QMessageBox::information(nullptr,tr("提示"),tr("上下左右空格控制坦克"), tr("好"));
    Battle=new BattleWindow;
    Battle->show();
    Battle->Load_Status(false);
    this->~MainWindow();
}

void MainWindow::on_Map_clicked()
{
    Map=new EditMap;
    Map->show();
    this->~MainWindow();
}

void MainWindow::on_AboutAuthor_clicked()
{
    Battle=new BattleWindow;
    Battle->show();
    Battle->Load_Status(true);
    this->~MainWindow();
}

void MainWindow::on_Exit_clicked()
{
      QMessageBox::information(nullptr,tr("提示"),tr("退出失败，赶紧体验"), tr("好"));
}

void MainWindow::on_button2_clicked()
{

    QMessageBox::information(nullptr,tr("抱歉"),tr("敬请期待"), tr("好"));

}

void MainWindow::on_button1_clicked()
{
    QMessageBox::information(nullptr,tr("抱歉"),tr("敬请期待"), tr("好"));
}
