#include "Email.h"
#include "ui_Email.h"
#include <QDesktopServices>
Email::Email(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Email)
{
    setWindowIcon(QIcon(":/Images/Images/icon.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    ui->setupUi(this);
}

Email::~Email()
{
    delete ui;
}

void Email::on_pushButton_clicked()
{
    this->~Email();

}

void Email::on_pushButton_3_clicked()
{

}

void Email::on_pushButton_2_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/NPgreatest/Lost-In-World-War-II")));
}
