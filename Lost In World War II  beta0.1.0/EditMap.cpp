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
    update();
    int i,x,y,x1,y1,thp=1,tskin=1;
    if(ev->button() != Qt::LeftButton || ev->type() != QEvent::Type::MouseButtonPress)return;//只响应鼠标左键的单击操作 防止游戏结束重复弹框
    QPoint pt = ev->pos();

    Ctype=ui->comboBox->currentIndex();
    if(ui->comboBox->currentIndex()==18)Ctype=101;//temp
    if(ui->comboBox->currentIndex()==19)Ctype=102;
    if(pt.x()>=0&&pt.x()<=1500&&pt.y()>=0&&pt.y()<=1000){//有效操作
        if(Ctype==0){
        for(i=Edit_Max-1;i>=0;i--){
            if(pos[i].x<=pt.x()&&pos[i].x+area[i].x>=pt.x()&&pos[i].y<=pt.y()&&pos[i].y+area[i].x>=pt.y()){
                pos[i].x=0;pos[i].y=0;area[i].x=0;area[i].y=0;type[i]=0;hp[i]=-1;
                update();return;
            }
            if(e_pos[i].x<=pt.x()&&e_pos[i].x+e_area[i].x>=pt.x()&&e_pos[i].y<=pt.y()&&e_pos[i].y+e_area[i].x>=pt.y()){
                e_pos[i].x=0;e_pos[i].y=0;e_area[i].x=0;e_area[i].y=0;
                update();return;
            }
        }
        return;
        }
        if(acc==true){
            x=GetPos(pt.x(),pt.y()).x;x1=ui->spinBox_1->value();
            y=GetPos(pt.x(),pt.y()).y;y1=ui->spinBox_2->value();thp=ui->spinBox_3->value();
            for(i=0;i<Edit_Max;i++){
                if(pos[i].x==x&&pos[i].y==y&&area[i].x==50&&area[i].y==50&&type[i]==Ctype)return;//重复就退出
            }
            if(Ctype==101){
                for(i=0;i<Edit_Max;i++){
                    if(e_pos[i].x==x&&e_pos[i].y==y&&e_area[i].x==50&&e_area[i].y==50)return;//重复就退出
                }}
            switch (Ctype) {
            case 101:
            for(i=0;i<Edit_Max;i++){
                 if(e_area[i].x==0&&e_area[i].y==0){
                    e_pos[i].x=x;e_pos[i].y=y;e_area[i].x=x1;e_area[i].y=y1;
                    e_hp[i]=0;e_speed[i]=5;e_bullet_speed[i]=10;e_skin[i]=ui->spinBox_7->value();update();return;}
                }break;
            case 102:ppos.x=x;ppos.y=y;me=true;update();return;
            }
            for(i=0;i<Edit_Max;i++){
                if(type[i]==0){
                     pos[i].x=x;pos[i].y=y;area[i].x=x1;area[i].y=y1;type[i]=Ctype;skin[i]=ui->spinBox->value();hp[i]=thp;break;
                }
            }
        }else{//acc==false
        x=QInputDialog::getInt(this,tr("矫正数值"),tr("输入X坐标"),pt.x(),0,1500,1,nullptr,nullptr);
        y=QInputDialog::getInt(this,tr("矫正数值"),tr("输入Y坐标"),pt.y(),0,1000,1,nullptr,nullptr);
        if(Ctype!=102){
        x1=QInputDialog::getInt(this,tr("矫正数值"),tr("输入长度"),50,10,500,1,nullptr,nullptr);
        y1=QInputDialog::getInt(this,tr("矫正数值"),tr("请输入宽度"),50,10,500,1,nullptr,nullptr);}
        switch (Ctype) {
        case 1:thp=QInputDialog::getInt(this,tr("矫正数值"),tr("请输入血量"),1,0,1000,1,nullptr,nullptr);break;
        case 5:thp=QInputDialog::getInt(this,tr("矫正数值"),tr("请输入血量"),10,0,1000,1,nullptr,nullptr);break;
        case 8:thp=QInputDialog::getInt(this,tr("矫正数值"),tr("请输入血量"),50,0,1000,1,nullptr,nullptr);break;
        case 11:thp=QInputDialog::getInt(this,tr("矫正数值"),tr("请输入血量"),100,0,1000,1,nullptr,nullptr);break;
        case 102:ppos.x=x;ppos.y=y;me=true;
            update();return;
        case 101:
            for(i=0;i<Edit_Max;i++){
                if(e_area[i].x==0&&e_area[i].y==0){
                    e_pos[i].x=x;e_pos[i].y=y;e_area[i].x=x1;e_area[i].y=y1;
                    e_hp[i]=QInputDialog::getInt(this,tr("矫正数值"),tr("敌人血量"),0,0,100,1,nullptr,nullptr);
                    e_speed[i]=QInputDialog::getInt(this,tr("矫正数值"),tr("敌人速度"),5,1,50,1,nullptr,nullptr);
                    e_bullet_speed[i]=QInputDialog::getInt(this,tr("矫正数值"),tr("敌人子弹速度"),10,1,100,1,nullptr,nullptr);
                    e_skin[i]=QInputDialog::getInt(this,tr("矫正数值"),tr("敌人皮肤编号"),1,1,100,1,nullptr,nullptr);
                    break;
                }
            }update();return;
        }
        tskin=QInputDialog::getInt(this,tr("矫正数值"),tr("请输入皮肤编号"),1,1,100,1,nullptr,nullptr);
        for(i=0;i<Edit_Max;i++){
            if(type[i]==0){
                 pos[i].x=x;pos[i].y=y;area[i].x=x1;area[i].y=y1;type[i]=Ctype;skin[i]=tskin;hp[i]=thp;break;
            }
        }
    }
    }
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

    number[1].load(":/Images/Object/Wall1.png");
    number[2].load(":/Images/Object/BedRock1.png");
    number[3].load(":/Images/Object/River1.jpg");
    number[5].load(":/Images/Object/Camp1.jpg");
    number[4].load(":/Images/Object/Portal.png");
    number[6].load(":/Images/Object/FirstAid1.png");
    number[7].load(":/Images/Object/Weapon1.png");
    number[8].load(":/Images/Object/Camp2.jpg");
    number[9].load(":/Images/Object/FirstAid2.png");
    number[10].load(":/Images/Object/Weapon2.png");
    number[11].load(":/Images/Object/Camp3.jpg");
    number[12].load(":/Images/Object/FirstAid3.png");
    number[13].load(":/Images/Object/Weapon3.png");
    number[14].load(":/Images/Object/Ruins1.png");
    number[15].load(":/Images/Object/Grass1.png");
    number[16].load(":/Images/Object/Nail1.png");
    number[17].load(":/Images/Object/ice1.png");
    number[101].load(":/Images/Tank/EnemyUp_1.png");
    number[102].load(":/Images/Tank/TankUp.png");

    for(i=0;i<200;i++)
        number[i]=Image_Cut(number[i]);

    QRect playerpos(ppos.x,ppos.y,50,50);
    if(me==true)painter.drawImage(playerpos,number[102]);
    QRect *draw_object=new QRect[Edit_Max];
    for(i=0;i<Edit_Max;i++){
        if(type[i]==0)continue;
        new(&draw_object[i])QRect(pos[i].x,pos[i].y,area[i].x,area[i].y);
        painter.drawImage(draw_object[i],number[type[i]]);
}
    QRect draw_enemy[Edit_Max];
    for(i=0;i<Edit_Max;i++){
        draw_enemy[i].setRect(e_pos[i].x,e_pos[i].y,e_area[i].x,e_area[i].y);
        painter.drawImage(draw_enemy[i],number[101]);
    }


}

void EditMap::on_Finish_clicked()
{
    int i;
    QString path=QFileDialog::getExistingDirectory(this,"选择地图目录",QCoreApplication::applicationDirPath(),QFileDialog::ShowDirsOnly);
    QString name=QInputDialog::getText(this,tr("提示"),tr("编辑地图名称"),QLineEdit::Normal,"New Map",nullptr,nullptr,nullptr);
    QString fianl=path+"/"+name+".txt";
    QFile file;

    QFile file2(fianl);
    if (!file2.open(QIODevice::WriteOnly))
    {QMessageBox::information(nullptr,tr("抱歉"),tr("未知错误"), tr("好"));return;}

    QTextStream out(&file2);
    out << "CObject:\n";
    for(i=0;i<Edit_Max;i++){
        if(type[i]==0)continue;
        out<<type[i]<<" ";
        out<<pos[i].x<<" ";
        out<<pos[i].y<<" ";
        out<<area[i].x<<" ";
        out<<area[i].y<<" ";
        out<<hp[i]<<" ";
        out<<skin[i]<<"\n";
    }
    if(me==true)//没放置玩家可视为刷怪图
out<<"CPlayer:\n"<<ppos.x<<" "<<ppos.y<<" "<<ui->spinBox_4->value()<<" "<<ui->spinBox_5->value()<<" "<<ui->spinBox_6->value()<<" "<<ui->spinBox_7->value()<<" 5\n";
out<<"CEnemy:\n";
for(i=0;i<Edit_Max;i++){
    if(e_area[i].x==0||e_area[i].y==0)continue;
    out<<e_pos[i].x<<" ";
    out<<e_pos[i].y<<" ";
    out<<e_area[i].x<<" ";
    out<<e_area[i].y<<" ";
    out<<e_hp[i]<<" ";
    out<<e_speed[i]<<" ";
    out<<e_bullet_speed[i]<<" ";
    out<<e_skin[i]<<"\n";
}
    file2.close();
}

void EditMap::on_Back_clicked(){
    a=new MainWindow;
    a->setMouseTracking(true);
    a->show();
    this->~EditMap();
}

void EditMap::on_checkBox_stateChanged(int arg1)
{

    if(ui->checkBox->isChecked()==false){
        acc=true;return;
    }else{
        acc=false;return;
    }
}


QImage EditMap::Image_Cut(QImage image)
{
        image = image.convertToFormat(QImage::Format_ARGB32);
        union myrgb
        {
            uint rgba;
            uchar rgba_bits[4];
        };
        myrgb* mybits =(myrgb*) image.bits();
        int len = image.width()*image.height();
        while(len --> 0)
        {
            mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:255;
            mybits++;
        }
        return image;
}

void EditMap::on_checkBox_2_stateChanged(int arg1)
{
    if(ui->checkBox_2->isChecked()==false){
      this->setStyleSheet("");
    }else{
      this->setStyleSheet("#EditMap{border-image:url(:/Images/Images/BattleGround.png);}");
    }
}
