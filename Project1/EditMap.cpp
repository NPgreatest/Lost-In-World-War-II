#include "EditMap.h"
#include "ui_EditMap.h"
#include<QDebug>
#include <QInputDialog>
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include"mainwindow.h"
EditMap::EditMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditMap)
{
    ui->setupUi(this);


}

EditMap::~EditMap()
{
    delete ui;
}

void EditMap::mousePressEvent(QMouseEvent *ev){
    int i,x,y,x1,y1;
    if(ev->button() != Qt::LeftButton || ev->type() != QEvent::Type::MouseButtonPress)return;//只响应鼠标左键的单击操作 防止游戏结束重复弹框
    QPoint pt = ev->pos();
    qDebug()<<pt.x()<<","<<pt.y();
    if(pt.x()>=1550&&pt.x()<=1600&&pt.y()>=0&&pt.y()<=50)Ctype=1;
    if(pt.x()>=1550&&pt.x()<=1600&&pt.y()>=50&&pt.y()<=100)Ctype=2;
    if(pt.x()>=1550&&pt.x()<=1600&&pt.y()>=100&&pt.y()<=150)Ctype=3;
    if(pt.x()>=1550&&pt.x()<=1600&&pt.y()>=150&&pt.y()<=200)Ctype=4;
    if(pt.x()>=1550&&pt.x()<=1600&&pt.y()>=200&&pt.y()<=250)Ctype=5;
    if(pt.x()>=1550&&pt.x()<=1600&&pt.y()>=250&&pt.y()<=300)Ctype=6;
    if(pt.x()>=1550&&pt.x()<=1600&&pt.y()>=300&&pt.y()<=350)Ctype=7;
    if(pt.x()>=1550&&pt.x()<=1600&&pt.y()>=350&&pt.y()<=400)Ctype=8;

    if(pt.x()>=1500&&pt.x()<=1550&&pt.y()>=0&&pt.y()<=50)Ctype=0;
    if(pt.x()>=0&&pt.x()<=1500&&pt.y()>=0&&pt.y()<=1000){//有效操作

        if(Ctype==0){
        for(i=0;i<200;i++){
            if(pos[i].x<=pt.x()&&pos[i].x+area[i].x>=pt.x()&&pos[i].y<=pt.y()&&pos[i].y+area[i].x>=pt.y()){
                pos[i].x=0;pos[i].y=0;area[i].x=0;area[i].y=0;type[i]=0;update();return;
            }
        }
        return;
        }
        if(acc==true){
            x=GetPos(pt.x(),pt.y()).x;x1=50;
            y=GetPos(pt.x(),pt.y()).y;y1=50;
            for(i=0;i<200;i++){
                if(pos[i].x==x&&pos[i].y==y&&area[i].x==50&&area[i].y==50&&type[i]==Ctype)return;//重复就退出
            }
            if(Ctype==4){ppos.x=x;ppos.y=y;me=true;update();return;}
        }else{
        x=QInputDialog::getInt(this,tr("矫正数值"),tr("输入X坐标"),pt.x(),0,1500,1,nullptr,nullptr);
        y=QInputDialog::getInt(this,tr("矫正数值"),tr("输入Y坐标"),pt.y(),0,1500,1,nullptr,nullptr);
        if(Ctype==4){ppos.x=x;ppos.y=y;me=true;update();return;}
        x1=QInputDialog::getInt(this,tr("矫正数值"),tr("输入长度"),50,10,200,1,nullptr,nullptr);
        y1=QInputDialog::getInt(this,tr("矫正数值"),tr("请输入宽度"),50,10,200,1,nullptr,nullptr);
        }
    for(i=0;i<200;i++){
        if(type[i]==0){
            pos[i].x=x;pos[i].y=y;area[i].x=x1;area[i].y=y1;type[i]=Ctype;break;

        }

    }

    }
//dawoijoiio

    update();
}
XY EditMap::GetPos(int x, int y){
    int i,x1,y1;
    for(i=0;i<30;i++){
        if(x-(50*i)<50){x1=50*i;break;}
    }
    for(i=0;i<20;i++){
        if(y-(50*i)<50){y1=50*i;break;}
    }
    XY t={x1,y1};
    return t;
}
void EditMap::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    int i;
    for(i=0;i<=30;i++){
        QLine line(50*i,0,50*i,1000);
        painter.drawLine(line);
    }
    for(i=0;i<=20;i++){
        QLine line(0,50*i,1500,50*i);
        painter.drawLine(line);
    }
    QImage walls1("://images/Wall1.bmp");
    QImage walls2("://images/Wall2.bmp");
    QImage bedrock1("://images/Bedrock1.bmp");
    QImage bedrock2("://images/Bedrock2.bmp");
    QImage river1("://images/River1.bmp");
    QImage river2("://images/River2.bmp");
    QImage player1("://images/TankUp.bmp");
    QImage player2("://images/TankDown.bmp");
    QImage eraser1("://images/eraser.bmp");
    QImage eraser2("://images/eraser2.bmp");
    QImage Camp1("://images/Camp.bmp");
    QImage Camp2("://images/test300x300.bmp");
    QImage FirstAid1("://images/FirstAid.bmp");
    QImage FirstAid2("://images/test300x300.bmp");
    QImage Weapon1("://images/Weapon.bmp");
    QImage Weapon2("://images/test300x300.bmp");
    QImage Enemy1("://images/EnemyUp.bmp");
    QImage Enemy2("://images/EnemyDown.bmp");
    QRect wall(1550,0,50,50);
    QRect bedrock(1550,50,50,50);
    QRect river(1550,100,50,50);
    QRect player(1550,150,50,50);
    QRect eraser(1500,0,50,50);
    QRect camp(1550,200,50,50);
    QRect firstaid(1550,250,50,50);
    QRect weapon(1550,300,50,50);
    QRect enemy(1550,350,50,50);
    painter.drawImage(wall,walls1);
    painter.drawImage(bedrock,bedrock1);
    painter.drawImage(river,river1);
    painter.drawImage(player,player1);
    painter.drawImage(eraser,eraser1);
    painter.drawImage(camp,Camp1);
    painter.drawImage(firstaid,FirstAid1);
    painter.drawImage(weapon,Weapon1);
    painter.drawImage(enemy,Enemy1);
    switch (Ctype) {
    case 0:painter.drawImage(eraser,eraser2);break;
    case 1:painter.drawImage(wall,walls2);break;
    case 2:painter.drawImage(bedrock,bedrock2);break;
    case 3:painter.drawImage(river,river2);break;
    case 4:painter.drawImage(player,player2);break;
    case 5:painter.drawImage(camp,Camp2);break;
    case 6:painter.drawImage(firstaid,FirstAid2);break;
    case 7:painter.drawImage(weapon,Weapon2);break;
    case 8:painter.drawImage(enemy,Enemy2);break;
    }
    QRect playerpos(ppos.x,ppos.y,50,50);
    if(me==true)painter.drawImage(playerpos,player1);
    QRect *draw=new QRect[200];
    for(i=0;i<200;i++){
        new(&draw[i])QRect(pos[i].x,pos[i].y,area[i].x,area[i].y);
        switch (type[i]) {
        case 1:painter.drawImage(draw[i],walls1);break;
        case 2:painter.drawImage(draw[i],bedrock1);break;
        case 3:painter.drawImage(draw[i],river1);break;
        case 5:painter.drawImage(draw[i],Camp1);break;
        case 6:painter.drawImage(draw[i],FirstAid1);break;
        case 7:painter.drawImage(draw[i],Weapon1);break;
        case 8:painter.drawImage(draw[i],Enemy1);break;
        }
}
}

void EditMap::on_Finish_clicked()
{
    if(me==false){QMessageBox::information(nullptr,tr("提示"),tr("未放置玩家"), tr("好"));return;}
    int i;
    QString path=QFileDialog::getExistingDirectory(this,"选择地图目录",QCoreApplication::applicationDirPath(),QFileDialog::ShowDirsOnly);
    QString name=QInputDialog::getText(this,tr("提示"),tr("编辑地图名称"),QLineEdit::Normal,"New Map",nullptr,nullptr,nullptr);
    QString fianl=path+"/"+name+".txt";
    QFile file;

    QFile file2(fianl);
    if (!file2.open(QIODevice::WriteOnly))
    {qDebug()<<"Fail...";return;}

    QTextStream out(&file2);
    out << "CObject:\n";
    for(i=0;i<200;i++){
        if(type[i]==0)continue;
        out<<type[i]<<"\n";
        out<<pos[i].x<<"\n";
        out<<pos[i].y<<"\n";
        out<<area[i].x<<"\n";
        out<<area[i].y<<"\n";
    }
out<<"CPlayer:\n"<<ppos.x<<"\n"<<ppos.y<<"\n100\n100\n";

    file2.close();
}

void EditMap::on_Back_clicked()
{
    a=new MainWindow;
    a->show();
    this->~EditMap();
}

void EditMap::on_checkBox_stateChanged(int arg1)
{

    if(ui->checkBox->isChecked()==true){
        acc=true;return;
    }else{
        acc=false;return;
    }
}
